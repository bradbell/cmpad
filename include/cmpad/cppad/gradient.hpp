// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_CPPAD_GRADIENT_HPP
# define CMPAD_CPPAD_GRADIENT_HPP
/*
{xrst_begin cppad_gradient}

Calculate Gradient Using CppAD
##############################

Syntax
******
|  ``cmpad::gradient`` < *Algo* > *grad*
|  *algo* . ``setup`` ( *n* )
|  *ay* = *algo* ( *ax* )
|  *grad* . ``setup`` ( *n* )
|  *g* = *grad* ( *x* )

Prototype
*********
{xrst_literal
   // BEGIN CLASS
   // END CLASS
}
{xrst_literal
   // BEGIN SETUP
   // END SETUP
}
{xrst_literal
   // BEGIN OPERATOR
   // END OPERATOR
}

algo
****
This is an *Algo* object that has been initialized using its ``setup`` syntax.

ax
**
This is an ``cmpad::vector< CppAD::AD<double> >`` object with size *n*.
It is the point at which to evaluate the algorithm in *algo* .

ay
**
This result is a ``CppAD::AD<double>`` object.
It is the result of the algorithm.

grad
****
The  this object has been initialized using its ``setup`` syntax.
This can do any calculations that do not depend on *x*.

x
*
This is an ``cmpad::vector<double>`` object with size *n*.
It is the point at which to evaluate the gradient of the
function corresponding to *algo* .

g
*
This result is an ``cmpad::vector<double>`` object with size *n*.
This is the gradient of the function corresponding to the argument
evaluated at the point *x* .

Example
*******
The file :ref:`gradient.cpp-name`
contains an example and test of this class.

Source Code
***********
The page :ref:`cppad_gradient.hpp-name`
displays the source code for this class.

{xrst_end cppad_gradient}
-------------------------------------------------------------------------------
{xrst_begin cppad_gradient.hpp}

CppAD gradient: Source Code
###########################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end cppad_gradient.hpp}
*/
// BEGIN C++
# include <boost/test/unit_test.hpp>
# include <cppad/cppad.hpp>

namespace cmpad { namespace cppad { // BEGIN cmpad::cppad namespace

// BEGIN CLASS
template <class Algo> class gradient {
// END CLASS
//
private:
   // algo_
   Algo algo_;
   // w_
   cmpad::vector<double> w_;
   // tape_
   CppAD::ADFun<double>  tape_;
//
public:
   //
   // BEGIN SETUP
   void setup(size_t n)
   // END SETUP
   {  //
      // algo_
      algo_.setup(n);
      //
      // w_
      w_.resize(1);
      w_[0] = 1.0;
      //
      // tape_
      cmpad::vector< CppAD::AD<double> > ax(n * n);
      for(size_t i = 0; i < n * n; ++i)
         ax[i] = 0.;
      CppAD::Independent(ax);
      cmpad::vector< CppAD::AD<double> > ay(1);
      ay = algo_(ax);
      tape_.Dependent(ax, ay);
   }
   //
   // BEGIN OPERATOR
   cmpad::vector<double> operator()(const cmpad::vector<double>& x)
   // END OPERATOR
   {  tape_.Forward(0, x);
      return tape_.Reverse(1, w_);
   }
};

} } // END cmpad::cppad namespace
// END C++
# endif
