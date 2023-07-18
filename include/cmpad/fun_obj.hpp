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
|  ``cmpad::fun_obj`` *fun*
|  *name* = *fun* . ``name`` ()
|  *n* = *fun* . ``domain`` ()
|  *m* = *fun* . ``range`` ()
|  *fun* . ``setup`` ( *ell* )
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
The corresponding function call computes *y* as a function of *x* .

name
****
is the name used to distinguish different function objects.

domain
******
This returns *n* the dimension of the domain space for this function object;
i.e. the size of *x*. It likely depends on the value of *ell*.

range
*****
This returns *m* the dimension of the range space for this function object;
i.e. the size of *y*. It likely depends on the value of *ell*.

setup
*****
The function object is initialized using its ``setup`` syntax.
The ``setup`` can (and should) do calculations that do not depend on *x*
(to make the evaluation of the function).

*ell*
*****
This parameter is used to scale the function object to different size
calculations. For example, it could be the row and or column dimension
of a matrix that the function object will operate on.

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
# include <cmpad/vector.hpp>

namespace cmpad {
   template <class Scalar> struct fun_obj {
      // name
      virtual std::string name(void) = 0;
      // n
      virtual size_t domain(void) = 0;
      // m
      virtual size_t range(void) = 0;
      // setup
      virtual void setup(size_t ell) = 0;
      // operator()
      virtual const cmpad::vector<Scalar>& operator()(
         const cmpad::vector<Scalar>& x
      ) = 0;
   };
}
// END C++
# endif
