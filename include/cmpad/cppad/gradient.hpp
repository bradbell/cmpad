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
|  ``# include <cmpad/cppad/gradient.hpp``
|  ``cmpad::cppad::gradient`` < *Algo* > *grad*
|  *algo* . ``setup`` ( *ell* )
|  *grad* . ``setup`` ( *ell* )
|  *grad* . ``domain`` ( )
|  *package* = *grad* . ``package`` ()
|  *g* = *grad* ( *x* )


Purpose
*******
This implements the :ref:`gradient-name` interface using CppAD.

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
private:
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
   // package
   std::string package(void)
   {  return "cppad"; }
   // setup
   void setup(size_t ell) override
   {  //
      // algo_
      algo_.setup(ell);
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
   size_t domain(void) override
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
