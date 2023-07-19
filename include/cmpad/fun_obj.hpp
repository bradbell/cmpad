// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ----------------------------------------------------------------------------
# ifndef CMPAD_FUN_OBJ_HPP
# define CMPAD_FUN_OBJ_HPP
/*
{xrst_begin fun_obj}
{xrst_spell
   obj
}

Abstract Class for a Function Object
####################################

Syntax
******
|  ``# include <cmpad/fun_obj.hpp``
|  ``cmpad::fun_obj`` < *Scalar* > *fun*
|  *fun* . ``setup`` ( *option* )
|  *option* = *fun* . ``option`` ()
|  *n* = *fun* . ``domain`` ()
|  *m* = *fun* . ``range`` ()
|  *y* = *fun* ( *x* )

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

fun
***
This is the function object.
The corresponding function call,
*y* = *fun* ( *x* ),
computes *y* as a function of *x* .

setup
*****
The function object is initialized using the ``setup`` syntax.
The ``setup`` can (and should) do calculations that do not depend on *x*
(to make the evaluation of the function call faster).

option
******
This map must have the following key:

name
====
The corresponding value is the name of this function object.

domain
******
The return value *n* is the dimension of the domain space for
this function; i.e. the size of *x*.
It likely depends on the value of *option*.

range
*****
The return value *m* is the dimension of the range space for
this function; i.e. the size of *y*.
It likely depends on the value of *option*.

x
*
This vector has size *n* and
is the point at which the function is evaluated.

y
*
This vector has size *m* and
is the function value corresponding to *x*.

Derived Classes
***************
{xrst_toc_table
   include/cmpad/det_by_minor.hpp
}

{xrst_end fun_obj}
---------------------------------------------------------------------------
*/
// BEGIN C++
# include <cmpad/typedef.hpp>

namespace cmpad {
   template <class Scalar> struct fun_obj {
      // setup
      virtual void setup(const option_t& option) = 0;
      // option
      virtual const option_t& option(void) const = 0;
      // domain
      virtual size_t domain(void) const = 0;
      // range
      virtual size_t range(void) const = 0;
      // operator()
      virtual const cmpad::vector<Scalar>& operator()(
         const cmpad::vector<Scalar>& x
      ) = 0;
   };
}
// END C++
# endif
