// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_CPPAD_JIT_GRADIENT_HPP
# define CMPAD_CPPAD_JIT_GRADIENT_HPP
/*
{xrst_begin cppad_jit_gradient.hpp}
{xrst_spell
   cppad
   obj
   jit
}

Calculate Gradient Using CppAD Compiled Derivative Calculation
##############################################################

Under Construction
******************
The test of this routine has been commented out of
:ref:`gradient.cpp-name` because it is not yet working.

Syntax
******
| ``# include <cmpad/cppad_jit/gradient.hpp>``
|  ``cmpad::cppad_jit::gradient`` < *TemplateAlgo* > *grad*
|  *g* = *grad* ( *x* )


Purpose
*******
This implements the :ref:`gradient-name` interface using
CppAD just in time compilation.

TemplateAlgo
************
The class TemplateAlgo<Scalar> must be a derived class for
:ref:`fun_obj\<Scalar\> <fun_obj-name>` .

value_type
**********
The type cmpad::cppad_jit::gradient<TemplateAlgo>::value_type is ``double`` ;
see :ref:`gradient@value_type` .

Example
*******
The file :ref:`gradient.cpp-name`
contains an example and test using this class.

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end cppad_jit_gradient.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_CPPAD

# include <filesystem>
# include <cmpad/gradient.hpp>
# include <cppad/cppad.hpp>

# ifdef _WIN32
# define CMPAD_DLL_EXT ".dll"
# else
# define CMPAD_DLL_EXT ".so"
# endif

namespace cmpad { namespace cppad_jit { // BEGIN cmpad::cppad_jit namespace

static_assert(
   CPPAD_C_COMPILER_GNU || CPPAD_C_COMPILER_MSVC,
   "C compiler is not GNU or MCVC"
);

// cmpad::cppad_jit::gradient
template < template<class Scalar> class TemplateAlgo > class gradient
: public ::cmpad::gradient< TemplateAlgo< CppAD::AD<double> > > {
private:
   //
   // option_
   option_t                          option_;
   //
   // algo_
   TemplateAlgo< CppAD::AD<double> > algo_;
   // g_
   cmpad::vector<double>             g_;
   //
   // grad_det_cppad_jit_
   CppAD::jit_double                 grad_det_cppad_jit_;
//
public:
   // value_type
   typedef double value_type;
   // option
   const option_t& option(void) const override
   {  return option_; }
   // setup
   void setup(const option_t& option) override
   {  //
      // string
      using std::string;
      //
      // algo_
      algo_.setup(option);
      //
      // n
      size_t n = algo_.domain();
      //
      // m
      size_t m = algo_.range();
      assert( m == 1 );
      //
      // g_
      g_.resize(n);
      //
      // ax, ay, aw
      cmpad::vector< CppAD::AD<double> > ax(n), ay(m), aw(m), ag(n);
      //
      // function_name
      string function_name = "grad_det_cppad_jit";
      //
      // tapef
      CppAD::ADFun<double> tapef;
      for(size_t i = 0; i < n; ++i)
         ax[i] = 0.;
      CppAD::Independent(ax);
      ay = algo_(ax);
      tapef.Dependent(ax, ay);
      if( ! option.time_setup )
         tapef.optimize();
      //
      // atapef
      CppAD::ADFun< CppAD::AD<double> , double > atapef;
      atapef = tapef.base2ad();
      //
      // ax, aw
      CppAD::Independent(ax);
      aw[0] = CppAD::AD<double>( 1.0 );
      //
      // tapeg
      atapef.Forward(0, ax);
      ag = atapef.Reverse(1, aw);
      CppAD::ADFun<double> tapeg;
      tapeg.Dependent(ax, ag);
      tapeg.function_name_set(function_name);
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
# ifdef _MSC_VER
      dll_options["compile"] = "cl /EHs /EHc /c /LD /TC /O2";
# else
      dll_options["compile"] = "gcc -c -fPIC";
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
      // dll_linker
      CppAD::link_dll_lib dll_linker(dll_file, err_msg);
      if( err_msg != "" )
      {  std::cerr << "cppad_jit::gradient::setup: err_msg = ";
         std::cerr << err_msg << "\n";
      }
      //
      // grad_det_cppad_jit_
      void* void_ptr = dll_linker("cppad_jit_" + function_name, err_msg);
      if( err_msg != "" )
      {  std::cerr << "cppad_jit::gradient::setup: err_msg = ";
         std::cerr << err_msg << "\n";
         void_ptr = nullptr;
      }
      grad_det_cppad_jit_ = reinterpret_cast<CppAD::jit_double>(void_ptr);
      std::cout << "void_ptr = " << void_ptr << "\n";
      std::cout << "grad_det_cppad_jit_ = " << grad_det_cppad_jit_ << "\n";
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
      grad_det_cppad_jit_(n, x.data(), n, g_.data(), &compare_change);
      assert( compare_change == 0 );
      return g_;
   }
};

} } // END cmpad::cppad_jit namespace

# endif // CMPAD_HAS_CPPAD
// END C++
# endif
