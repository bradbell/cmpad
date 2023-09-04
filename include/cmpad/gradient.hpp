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
|  *Algo* *algo*
|  ``cmpad::gradient`` < *Algo* > *grad*
|  *g* = *grad* ( *x* )

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}


algo
****
The *Algo* class is derived from the :ref:`fun_obj-name` class.
The *algo* object is initialized using its
:ref:`fun_obj@setup` member function.
The gradient is for the last component of the range space of the algorithm.
Hence, *algo*.range() can be greater than one.

value_type
**********
There are two value function objects,
and hence two :ref:`fun_obj@value_type` ,
associated with a gradient class.

1. Algo::value_type is the scalar type used when evaluating the algorithm.
2. cmpad::gradient<Algo>::value_type is the scalar type
   of the arguments and return value for the gradient object; i.e., double;
   see :ref:`fun_obj@value_type` .

grad
****
This object is initialized using its ``setup`` member function
(which in turn will initialize *algo* with its ``setup`` syntax).
The ``setup`` should do calculations that do not depend on *x*
(to make the evaluation of the gradient faster).
It calculates the gradient of the last component of the values
compute by *algo*.

domain
******
This returns the dimension of the
:ref:`fun_obj@domain` space dimension for the function and gradient.

range
*****
This returns the dimension of the
:ref:`fun_obj@range` space dimension for the gradient.
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
   xam/gradient/gradient.xrst
   include/cmpad/adept/gradient.hpp
   include/cmpad/adolc/gradient.hpp
   include/cmpad/autodiff/gradient.hpp
   include/cmpad/cppad/gradient.hpp
   include/cmpad/cppad_jit/gradient.hpp
   include/cmpad/cppadcg/gradient.hpp
   include/cmpad/sacado/gradient.hpp
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
      // value_type
      typedef double value_type;
      // setup
      virtual void setup(const option_t& option) override = 0;
      // option
      virtual const option_t& option(void) const override = 0;
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
