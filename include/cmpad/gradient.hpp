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
|  ``# include <cmpad/gradient.hpp``
|  ``cmpad::gradient`` < *Algo* > *grad*
|  *algo* . ``setup`` ( *option* )
|  *grad* . ``setup`` ( *option* )
|  *option* = *grad* . ``option`` ()
|  *n* = *grad* . ``domain`` ()
|  *m* = *grad* . ``range`` ()
|  *g* = *grad* ( *x* )

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

Algo
****
The *Algo* class is derived from the :ref:`fun_obj-name` class.
The *algo* object is initialized using its ``setup`` syntax.
The dimension of the :ref:`fun_obj@range` space for this algorithm
must be one.

grad
****
This object is initialized using its ``setup`` syntax
(which in turn will initialize *algo* with its ``setup`` syntax).
The ``setup`` should do calculations that do not depend on *x*
(to make the evaluation of the gradient faster).

domain
******
This returns the dimension of the
:ref:`fun_obj@domain` space dimension for the function and gradient.
This likely depends on *option* and *Algo* .

range
*****
This returns the dimension of the
:ref:`fun_obj@range` space dimension for the gradient.
This likely depends on *option* and *Algo* .
The dimension of the range space for the gradient is equal
to the dimension of the domain space for the gradient and function.
Hence ``range`` is implemented by this interface and not virtual.

x
*
This vector has size equal to the dimension of the domain space.
It is the point at which the gradient,
of the function represented by *algo* , is evaluated.

g
*
This result is has equal to the dimension of the range space for the gradient,
which is equal to the size of *x* .
It is the gradient evaluated at the point *x* .

Example and Derived Classes
***************************
{xrst_toc_table
   example/gradient.cpp
   include/cmpad/adolc/gradient.hpp
   include/cmpad/cppad/gradient.hpp
}

{xrst_end gradient}
-------------------------------------------------------------------------------
*/
// BEGIN C++
# include <cmpad/fun_obj.hpp>

namespace cmpad {
   // gradient
   template <class Algo> class gradient : public fun_obj<double> {
   public:
      // setup
      virtual void setup(const str2str_map& option) override = 0;
      // option
      virtual const str2str_map& option(void) const override = 0;
      // domain
      virtual size_t domain(void) const override  = 0;
      // range
      size_t range(void) const override
      {  return domain(); }
      // operator
      virtual const cmpad::vector<double>& operator()(
         const cmpad::vector<double>& x
      ) override = 0;
   };

}
// END C++
# endif
