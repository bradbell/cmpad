// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_GRADIENT_HPP
# define CMPAD_GRADIENT_HPP
/*
{xrst_begin gradient}

Abstract Class For Calculating Gradient
#######################################

Syntax
******
|  ``cmpad::gradient`` < *Algo* > *grad*
|  *algo* . ``setup`` ( *ell* )
|  *grad* . ``setup`` ( *ell* )
|  *g* = *grad* ( *x* )

Source Code
***********
{xrst_literal 
   // BEGIN C++
   // END C++
}

Algo
****
The *Algo* class is derived from the :ref:`fun_algo-name` class.
The *algo* object is initialized using its ``setup`` syntax.
The dimension of the :ref:`fun_algo@range` space for this algorithm
must be one.

grad
****
This object is initialized using its ``setup`` syntax
(which in turn will initialize *algo* with its ``setup`` syntax).
The ``setup`` should do calculations that do not depend on *x*
(to make the evaluation of the gradient faster).

x
*
The size of this vector depends on *ell* and *Algo* .
It is the point at which the gradient,
of the function represented by *algo* ,
is evaluated.

g
*
This result is an ``cmpad::vector<double>`` object with size
equal to the size of *x* .
It is the gradient evaluated at the point *x* .

Example and Derived Classes
***************************
{xrst_toc_table
   example/gradient.cpp
   include/cmpad/cppad/gradient.hpp
}

{xrst_end gradient}
-------------------------------------------------------------------------------
*/
// BEGIN C++
namespace cmpad { 
   // gradient
   template <class Algo> class gradient {
   public:
      // setup
      virtual void setup(size_t ell) = 0;
      // operator
      virtual const cmpad::vector<double>& operator()(
         const cmpad::vector<double>& x
      ) = 0;
   };

}
// END C++
# endif
