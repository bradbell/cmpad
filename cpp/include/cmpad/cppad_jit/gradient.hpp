// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_CPPAD_JIT_GRADIENT_HPP
# define CMPAD_CPPAD_JIT_GRADIENT_HPP
/*
{xrst_begin cppad_jit_gradient.hpp}
{xrst_spell
   dll
   ext
}

{xrst_template ,
   cpp/include/cmpad/gradient.xrst
   @Package@       , CppAD Jit
   @#######@       , #########
   @package@       , cppad_jit
   @not_cppad_jit@ , false
   @not_codi@      , true
}

{xrst_end cppad_jit_gradient.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_CPPAD

# include <filesystem>
# include <cmpad/gradient.hpp>
# include <cmpad/cppad/cppad.hpp>

# ifdef _WIN32
# define CMPAD_DLL_EXT ".dll"
# else
# define CMPAD_DLL_EXT ".so"
# endif

namespace cmpad { namespace cppad_jit { // BEGIN cmpad::cppad_jit namespace

static_assert(
   CPPAD_C_COMPILER_GNU_FLAGS || CPPAD_C_COMPILER_MSVC_FLAGS,
   "C compiler does not use same flags as GNU or MCVC"
);

// cmpad::cppad_jit::gradient
template < template<class ADVector> class Algo > class gradient
: public
cmpad::gradient {
private:
   //
   // ADScalar, ADVector
   typedef CppAD::AD<double>       ADScalar;
   typedef cmpad::vector<ADScalar> ADVector;
   //
   // option_
   option_t                          option_;
   //
   // algo_
   Algo<ADVector>                    algo_;
   //
   // g_
   cmpad::vector<double>             g_;
   //
   // dll_linker_
   // grad_cppad_jit_ is only valid for life of dll_linker_.
   CppAD::link_dll_lib*              dll_linker_;
   //
   // grad_cppad_jit_
   CppAD::jit_double                 grad_cppad_jit_;
//
public:
   // ctor, dtor
   gradient(void)
   {  dll_linker_ = nullptr; }
   ~gradient(void)
   {  if( dll_linker_ != nullptr )
         delete dll_linker_;
   }
   // scalar_type
   typedef double scalar_type;
   //
   // vector_type
   typedef cmpad::vector<double> vector_type;
   //
   // option
   const option_t& option(void) const override
   {  return option_; }
   // setup
   void setup(const option_t& option) override
   {  //
      // string
      using std::string;
      //
      // option_
      option_ = option;
      //
      // algo_
      algo_.setup(option);
      //
      // n
      size_t n = algo_.domain();
      //
      // m
      size_t m = algo_.range();
      //
      // g_
      g_.resize(n);
      //
      // ax, ay, az, aw
      ADVector ax(n), ay(1), az, aw(1), ag(n);
      //
      // function_name
      string function_name = "grad_cppad_jit";
      //
      // optimize_options
      std::string optimize_options =
      "no_conditional_skip no_compare_op no_print_for_op no_cumulative_sum_op";
      //
      // tapef
      CppAD::ADFun<double> tapef;
      for(size_t i = 0; i < n; ++i)
         ax[i] = 0.;
      CppAD::Independent(ax);
      az    = algo_(ax);
      ay[0] = az[m-1];
      tapef.Dependent(ax, ay);
      if( ! option.time_setup )
         tapef.optimize(optimize_options);
      //
      // atapef
      CppAD::ADFun< ADScalar, double > atapef;
      atapef = tapef.base2ad();
      //
      // ax, aw
      CppAD::Independent(ax);
      aw[0] = ADScalar( 1.0 );
      //
      // tapeg
      atapef.Forward(0, ax);
      ag = atapef.Reverse(1, aw);
      CppAD::ADFun<double> tapeg;
      tapeg.Dependent(ax, ag);
      tapeg.function_name_set(function_name);
      if( ! option.time_setup )
         tapeg.optimize(optimize_options);
      //
      // path
      using std::filesystem::path;
      //
      // original_path
      path original_path = std::filesystem::current_path();
      //
      // current_path
      path temp_path = std::filesystem::temp_directory_path();
      std::filesystem::current_path(temp_path);
      //
      // csrc_file
      string type = "double";
      string csrc_file = function_name + ".c";
      std::ofstream ofs;
      ofs.open(csrc_file, std::ofstream::out);
      tapeg.to_csrc(ofs, type);
      ofs.close();
      //
      // dll_file
      string  dll_file = function_name + CMPAD_DLL_EXT;
      cmpad::vector<string> csrc_files = {csrc_file};
      std::map< string, string > dll_options;
# if CMPAD_COMPILER_IS_MSVC
      dll_options["compile"] = "cl /EHs /EHc /c /LD /TC /O2";
# endif
# if CMPAD_COMPILER_IS_GNU
# ifndef NDEBUG
      dll_options["compile"] = "gcc -c -g -fPIC";
# else
      dll_options["compile"] = "gcc -c -O2 -fPIC";
# endif
# endif
# if CMPAD_COMPILER_IS_CLANG
# ifndef NDEBUG
      dll_options["compile"] = "clang -c -g -fPIC";
# else
      dll_options["compile"] = "clang -c -O2 -fPIC";
# endif
# endif
      string err_msg =
         CppAD::create_dll_lib(dll_file, csrc_files, dll_options);
      if( err_msg != "" )
      {  std::cerr << "cppad_jit::gradient::setup: err_msg = ";
         std::cerr << err_msg << "\n";
         dll_file = "";
      }
      //
      if( dll_file != "" )
      {  std::filesystem::path path = std::filesystem::current_path();
         path /= dll_file;
         dll_file = path.string();
      }
      //
      // dll_linker_
      if( dll_linker_ != nullptr )
         delete dll_linker_;
      if( dll_file != "" )
      {  dll_linker_ = new CppAD::link_dll_lib(dll_file, err_msg);
         if( err_msg != "" )
         {  std::cerr << "cppad_jit::gradient::setup: err_msg = ";
            std::cerr << err_msg << "\n";
            if( dll_linker_ != nullptr )
               delete dll_linker_;
            dll_linker_ = nullptr;
         }
      }
      //
      // grad_cppad_jit_
      void* void_ptr = nullptr;
      if( dll_linker_ != nullptr )
      {  void_ptr = (*dll_linker_)("cppad_jit_" + function_name, err_msg);
         if( err_msg != "" )
         {  std::cerr << "cppad_jit::gradient::setup: err_msg = ";
            std::cerr << err_msg << "\n";
            void_ptr = nullptr;
         }
      }
      grad_cppad_jit_ = reinterpret_cast<CppAD::jit_double>(void_ptr);
      //
      // current_path
      std::filesystem::current_path(original_path);
   }
   // domain
   size_t domain(void) const override
   {  return algo_.domain(); };
   //
   // operator
   const cmpad::vector<double>& operator()(
      const cmpad::vector<double>& x
   ) override
   {  size_t n              = domain();
      size_t compare_change = 0;
      assert( x.size() == n );
      assert( g_.size() == n );
      //
      grad_cppad_jit_(n, x.data(), n, g_.data(), &compare_change);
      assert( compare_change == 0 );
      return g_;
   }
};

} } // END cmpad::cppad_jit namespace

# endif // CMPAD_HAS_CPPAD
// END C++
# endif
