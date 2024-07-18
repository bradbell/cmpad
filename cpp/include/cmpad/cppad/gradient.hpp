// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_CPPAD_GRADIENT_HPP
# define CMPAD_CPPAD_GRADIENT_HPP
/*
------------------------------------------------------------------------------
{xrst_begin_parent cppad_gradient}

Gradients Using CppAD
#####################

{xrst_end cppad_gradient}
------------------------------------------------------------------------------
{xrst_begin cppad_gradient.hpp}

{xrst_template ,
   cpp/include/cmpad/gradient.xrst
   @Package@       , CppAD
   @#######@       , #####
   @package@       , cppad
   @not_cppad_jit@ , true
}
{xrst_end cppad_gradient.hpp}
------------------------------------------------------------------------------
{xrst_begin cppad_gradient_special.hpp}
{xrst_spell
   valvector
   std
   valarray
}

Special Version of Gradient Using CppAD
#######################################

valvector
*********
This version of the CppAD gradient handles the case where the base type
for differentiation is ``valvector`` instead of ``double``.
This is a CppAD example type that evaluates numerical operations on vectors
(similar to ``std::valarray`` numerical operators).
One important difference is that a scalar (one element vector) does
not allocate any memory and can operate with any sized vector.

Source Code
***********
{xrst_literal
   BEGIN SPECIAL
   END SPECIAL
}

{xrst_end cppad_gradient_special.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_CPPAD
# include <cmpad/gradient.hpp>
# include <cmpad/cppad/cppad.hpp>

namespace cmpad { namespace cppad { // BEGIN cmpad::cppad namespace

// cmpad::cppad::gradient
template < template<class ADVector> class Algo> class gradient
: public
::cmpad::gradient {
public:
   //
   // scalar_type
   typedef double scalar_type;
   //
   // vector_type
   typedef ::cmpad::vector<scalar_type> vector_type;
   //
private:
   // ADVector
   typedef typename ::cmpad::vector< CppAD::AD<scalar_type> >  ADVector;
   //
   // option_
   option_t                      option_;
   //
   // algo_
   Algo<ADVector>                algo_;
   //
   // w_
   vector_type                   w_;
   //
   // tape_
   CppAD::ADFun<scalar_type>     tape_;
   //
   // g_
   vector_type                   g_;
   //
public:
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
      ADVector ax(n);
      for(size_t i = 0; i < n; ++i)
         ax[i] = 0.;
      CppAD::Independent(ax);
      ADVector ay(1), az;
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
   const vector_type& operator()(const vector_type& x) override
   {  tape_.Forward(0, x);
      g_ =  tape_.Reverse(1, w_);
      return g_;
   }
};

} } // END cmpad::cppad namespace

# endif // CMPAD_HAS_CPPAD
// END C++
// ---------------------------------------------------------------------------
// BEGIN SPECIAL
# if CMPAD_HAS_CPPAD
# include <cmpad/gradient.hpp>
# include <cmpad/cppad/cppad.hpp>

// BEGIN cmpad::cppad::special namespace
namespace cmpad { namespace cppad { namespace special {

// cmpad::cppad::special::gradient
template < template<class ADVector> class Algo> class gradient
: public
::cmpad::gradient {
public:
   //
   // scalar_type
   typedef valvector scalar_type;
   //
   // vector_type
   typedef ::cmpad::vector<scalar_type> vector_type;
   //
private:
   // ADVector
   typedef typename ::cmpad::vector< CppAD::AD<scalar_type> >  ADVector;
   //
   // option_
   option_t                      option_;
   //
   // algo_
   Algo<ADVector>                algo_;
   //
   // x_
   vector_type                   x_;
   //
   // w_
   vector_type                   w_;
   //
   // tape_
   CppAD::ADFun<scalar_type>     tape_;
   //
   // g_
   vector_type                   g_;
   //
   // g_dbl_
   ::cmpad::vector<double>       g_dbl_;
   //
public:
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
      ADVector ax(n);
      for(size_t i = 0; i < n; ++i)
         ax[i] = 0.;
      CppAD::Independent(ax);
      ADVector ay(1), az;
      az    = algo_(ax);
      ay[0] = az[m-1];
      tape_.Dependent(ax, ay);
      if( ! option.time_setup )
         tape_.optimize(optimize_options);
      //
      // x_, g_, g_dbl_
      x_.resize(n);
      g_.resize(n);
      g_dbl_.resize(n);
   }
   // domain
   size_t domain(void) const override
   {  return algo_.domain(); };
   //
   // operator
   const ::cmpad::vector<double>&
   operator()(const ::cmpad::vector<double>& x_dbl) override
   {  // n
      size_t n = algo_.domain();
      assert( x_dbl.size() == n );
      //
      // x_
      for(size_t j = 0; j < n; ++j)
      {  assert( x_[j].size() == 1 );
         x_[j][0] = x_dbl[j];
      }
      //
      // g_
      tape_.Forward(0, x_);
      g_ =  tape_.Reverse(1, w_);
      //
      // g_dbl
      for(size_t j = 0; j < n; ++j)
      {  g_[j] = g_[j].sum();
         assert( g_[j].size() == 1 );
         g_dbl_[j] = g_[j][0];
      }
      return g_dbl_;
   }
};

} } } // END cmpad::cppad::special namespace

# endif // CMPAD_HAS_CPPAD
// END SPECIAL

# endif
