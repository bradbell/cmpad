// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ----------------------------------------------------------------------------
# ifndef CMPAD_FUN_OBJ_HPP
# define CMPAD_FUN_OBJ_HPP
/*
{xrst_begin cpp_fun_obj}

Abstract Class for a C++ Function Object
########################################

Syntax
******
| |tab| ``# include <cmpad/fun_obj.hpp``
| |tab| ``cmpad::fun_obj`` < *Scalar* > *fun*
| |tab| *y* = *fun* ( *x* )

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

value_type
**********
A derived class must define *value_type* to be the same as *Scalar* .
This is intended for use when derived class type
is passed as a template parameter.

setup
*****
The function object is initialized using the ``setup`` syntax.
The ``setup`` can (and should) do calculations that do not depend on *x*
(to make the evaluation of the function call faster).

option
******
This interface does not place any restrictions on the content of *option* .

domain
******
The return value is the dimension of the domain space for
this function; i.e. the size of *x*.
It likely depends on the value of *option*.

range
*****
The return value is the dimension of the range space for
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

{xrst_toc_hidden
   cpp/xam/fun_obj.cpp
}
Example
*******
:ref:`xam_fun_obj.cpp-name` is an example and test that uses this function.

{xrst_end cpp_fun_obj}
---------------------------------------------------------------------------
*/
// BEGIN C++

# include <cmpad/vector.hpp>
# include <cmpad/option_t.hpp>
namespace cmpad {
   template <class Scalar> struct fun_obj {
      //
      // value_type
      typedef Scalar value_type;
      //
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
