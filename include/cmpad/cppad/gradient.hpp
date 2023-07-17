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
|  ``cmpad::cppad::gradient`` < *Algo* > *grad*
|  *algo* . ``setup`` ( *ell* )
|  *grad* . ``setup`` ( *ell* )
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
template <class Algo> class gradient : ::cmpad::gradient<Algo> {
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
   // setup
   void setup(size_t ell) override
   {  //
      // algo_
      algo_.setup(ell);
      //
      // w_
      w_.resize(1);
      w_[0] = 1.0;
      //
      // tape_
      cmpad::vector< CppAD::AD<double> > ax(ell * ell);
      for(size_t i = 0; i < ell * ell; ++i)
         ax[i] = 0.;
      CppAD::Independent(ax);
      cmpad::vector< CppAD::AD<double> > ay(1);
      ay = algo_(ax);
      tape_.Dependent(ax, ay);
      //
      // g_
      g_.resize(ell * ell);
   }
   //
   // operator
   const cmpad::vector<double>& operator()(
      const cmpad::vector<double>& x
   ) override
   // END OPERATOR
   {  tape_.Forward(0, x);
      g_ =  tape_.Reverse(1, w_);
      return g_;
   }
};

} } // END cmpad::cppad namespace
// END C++
# endif
