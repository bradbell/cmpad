// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_CPPADCG_GRADIENT_HPP
# define CMPAD_CPPADCG_GRADIENT_HPP
/*
{xrst_begin cppadcg_gradient.hpp}
{xrst_spell
   obj
}

Calculate Gradient Using CppAD
##############################

Syntax
******
|  ``# include <cmpad/cppadcg/gradient.hpp>``
|  ``cmpad::cppadcg::gradient`` < *TemplateAlgo* > *grad*
|  *g* = *grad* ( *x* )


Purpose
*******
This implements the :ref:`gradient-name` interface using CppAD.

TemplateAlgo
************
The class TemplateAlgo<Scalar> must be a derived class for
:ref:`fun_obj\<Scalar\> <fun_obj-name>` .

value_type
**********
The type cmpad::cppadcg::gradient<TemplateAlgo>::value_type is ``double`` ;
see :ref:`gradient@value_type` .

Example
*******
The file :ref:`xam_gradient_cppadcg.cpp-name`
contains an example and test using this class.

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end cppadcg_gradient.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_CPPADCG

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
      cmpad::vector< CppAD::AD<cg_double> > ay(m);
      ay = algo_(ax);
      tape.Dependent(ax, ay);
      if( ! option.time_setup )
         tape.optimize(optimize_options);
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
