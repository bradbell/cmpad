// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_CPPADCG_GRADIENT_HPP
# define CMPAD_CPPADCG_GRADIENT_HPP
/*
{xrst_begin cppadcg_gradient.hpp}
{xrst_spell
   gen
}

{xrst_template ,
   cpp/include/cmpad/gradient.xrst
   @Package@ , CppAD CodeGen
   @#######@ , #############
   @package@ , cppadcg
}

{xrst_end cppadcg_gradient.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_CPPADCG

# include <filesystem>
# include <cppad/cg/cppadcg.hpp>
# include <cmpad/gradient.hpp>

namespace cmpad { namespace cppadcg { // BEGIN cmpad::cppadcg namespace
//
// cmpad::cppadcg::gradient
template < template<class Scalar> class TemplateAlgo> class gradient
: public ::cmpad::gradient< TemplateAlgo< CppAD::AD<double> > > {
private:
   //
   // cg_double
   typedef CppAD::cg::CG<double>                      cg_double;
   //
   // option_
   option_t                                           option_;
   //
   // algo_
   TemplateAlgo< CppAD::AD<cg_double> >               algo_;
   //
   // w_
   cmpad::vector<double>                              w_;
   //
   // dynamic_lib_
   std::unique_ptr< CppAD::cg::DynamicLib<double> >   dynamic_lib_;
   //
   // model_
   std::unique_ptr< CppAD::cg::GenericModel<double> > model_;
   //
   // g_
   cmpad::vector<double>                              g_;
//
public:
   // value_type
   typedef double value_type;
   // option
   const option_t& option(void) const override
   {  return option_; }
   // setup
   void setup(const option_t& option) override
   {  // see https://github.com/joaoleal/CppADCodeGen/wiki/LibGeneration
      //
      // compiler
# if CMPAD_COMPILER_IS_GNU
      CppAD::cg::GccCompiler<double> compiler;
# endif
# if CMPAD_COMPILER_IS_CLANG
      CppAD::cg::ClangCompiler<double> compiler;
# endif
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
      // optimize_options
      std::string optimize_options =
      "no_conditional_skip no_compare_op no_print_for_op no_cumulative_sum_op";
      //
      // tape
      CppAD::ADFun<cg_double>  tape;
      cmpad::vector< CppAD::AD<cg_double> > ax(n);
      for(size_t i = 0; i < n; ++i)
         ax[i] = 0.;
      CppAD::Independent(ax);
      cmpad::vector< CppAD::AD<cg_double> > ay(1), az;
      az    = algo_(ax);
      ay[0] = az[m-1];
      tape.Dependent(ax, ay);
      if( ! option.time_setup )
         tape.optimize(optimize_options);
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
      // cgen
      CppAD::cg::ModelCSourceGen<double> cgen(tape, "model");
      cgen.setCreateJacobian(true);
      //
      // libcgen
      CppAD::cg::ModelLibraryCSourceGen<double> libcgen(cgen);
      //
      // dynamic_lib_
      CppAD::cg::DynamicModelLibraryProcessor<double> proc(libcgen);
      dynamic_lib_ = nullptr;
      dynamic_lib_ = proc.createDynamicLibrary(compiler);
      //
      // model_
      model_ = nullptr;
      model_ = dynamic_lib_->model("model");
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
   {  g_ = model_->Jacobian(x);
      return g_;
   }
};

} } // END cmpad::cppadcg namespace

# endif // CMPAD_HAS_CPPADCG
// END C++
# endif
