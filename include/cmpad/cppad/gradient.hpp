// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_CPPAD_GRADIENT_HPP
# define CMPAD_CPPAD_GRADIENT_HPP
/*
{xrst_begin cppad_gradient.hpp}
{xrst_spell
   cppad
}

Calculate Gradient Using CppAD
##############################

Syntax
******
| ``# include <cmpad/cppad/gradient.hpp>``
|  ``cmpad::cppad::gradient`` < *Algo* > *grad*
|  *g* = *grad* ( *x* )


Purpose
*******
This implements the :ref:`gradient-name` interface using CppAD.

value_type
**********
The type *Algo*\ ::\ ``value_type`` must be ``CppAD::AD<double>`` .
The type cmpad::cppad::gradient<Algo>::value_type is ``double`` .

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

{xrst_end cppad_gradient.hpp}
*/
// BEGIN C++
# include <cmpad/gradient.hpp>
# include <cppad/cppad.hpp>

namespace cmpad { namespace cppad { // BEGIN cmpad::cppad namespace

// gradient
template <class Algo> class gradient : public ::cmpad::gradient<Algo> {
   static_assert(
      std::is_same<typename Algo::value_type, CppAD::AD<double>>::value ,
      "in cmpad::adolc<Algo>, Algo::value_type != CppAD::AD<double>"
   );
private:
   //
   // option_
   option_t option_;
   //
   // algo_
   Algo algo_;
   // w_
   cmpad::vector<double> w_;
   // tape_
   CppAD::ADFun<double>  tape_;
   // g_
   cmpad::vector<double> g_;
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
      // w_
      w_.resize(1);
      w_[0] = 1.0;
      //
      // tape_
      cmpad::vector< CppAD::AD<double> > ax(n);
      for(size_t i = 0; i < n; ++i)
         ax[i] = 0.;
      CppAD::Independent(ax);
      cmpad::vector< CppAD::AD<double> > ay(m);
      ay = algo_(ax);
      tape_.Dependent(ax, ay);
      tape_.optimize();
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
// END C++
# endif
