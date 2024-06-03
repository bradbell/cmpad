// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_CPPAD_GRADIENT_HPP
# define CMPAD_CPPAD_GRADIENT_HPP
/*
{xrst_begin cppad_gradient.hpp}

{xrst_template ,
   cpp/include/cmpad/gradient.xrst
   @Package@       , CppAD
   @#######@       , #####
   @package@       , cppad
   @not_cppad_jit@ , true
}

{xrst_end cppad_gradient.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_CPPAD
# if CMPAD_HAS_CPPADCG
# include <cppad/cg/cppadcg.hpp>
# endif
# include <cppad/cppad.hpp>
# include <cmpad/gradient.hpp>

namespace cmpad { namespace cppad { // BEGIN cmpad::cppad namespace

// cmpad::cppad::gradient
template < template<class Vector> class TemplateAlgo> class gradient
: public
::cmpad::gradient< TemplateAlgo< cmpad::vector< CppAD::AD<double> > > > {
private:
   // Vector
   typedef typename cmpad::vector< CppAD::AD<double> >   Vector;
   //
   // option_
   option_t              option_;
   //
   // algo_
   TemplateAlgo<Vector>  algo_;
   //
   // w_
   cmpad::vector<double> w_;
   //
   // tape_
   CppAD::ADFun<double>  tape_;
   //
   // g_
   cmpad::vector<double> g_;
//
public:
   //
   // scalar_type
   typedef double scalar_type;
   //
   // vector_type
   typedef cmpad::vector<double> vector_type;
   //
   // option
   const option_t& option(void) const override
   {  return option_; }
   //
   // setup
   void setup(const option_t& option) override
   {  //
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
      // w_
      w_.resize(1);
      w_[0] = 1.0;
      //
      // optimize_options
      std::string optimize_options =
      "no_conditional_skip no_compare_op no_print_for_op no_cumulative_sum_op";
      //
      // tape_
      Vector ax(n);
      for(size_t i = 0; i < n; ++i)
         ax[i] = 0.;
      CppAD::Independent(ax);
      Vector ay(1), az;
      az    = algo_(ax);
      ay[0] = az[m-1];
      tape_.Dependent(ax, ay);
      if( ! option.time_setup )
         tape_.optimize(optimize_options);
      //
      // g_
      g_.resize(n);
   }
   // domain
   size_t domain(void) const override
   {  return algo_.domain(); };
   //
   // operator
   const cmpad::vector<double>& operator()(
      const cmpad::vector<double>& x
   ) override
   {  tape_.Forward(0, x);
      g_ =  tape_.Reverse(1, w_);
      return g_;
   }
};

} } // END cmpad::cppad namespace

# endif // CMPAD_HAS_CPPAD
// END C++
# endif
