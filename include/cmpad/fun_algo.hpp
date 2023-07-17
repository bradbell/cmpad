// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ----------------------------------------------------------------------------
# ifndef CMPAD_FUN_ALGO_HPP
# define CMPAD_FUN_ALGO_HPP
/*
{xrst_begin fun_algo}

Abstract Class fo An Algorithm as a Function Object
###################################################

Syntax
******

| ``# include <cmpad/fun_algo.hpp>``
| ``cmpad::fun_algo`` < *Scalar* > *algo*
| *algo* . ``setup`` ( *ell* )
| *y* = *algo* ( *x* )

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

Scalar
******
If *x* and *y* are *Scalar* objects,
the type *Scalar* must support the following operations:

.. csv-table::
   :widths: auto
   :header-rows: 1

   Syntax,      Description,                                      Result Type
   Scalar(0),   constructor for *Scalar* object equal to zero,    *Scalar*
   Scalar(x),   constructor for *Scalar* object equal to *x*,     *Scalar*
   *x* + *y*,   value of *x* plus *y*,                            *Scalar*
   *x* - *y*,   value of *x* minus *y*,                           *Scalar*
   *x* * *y*,   value of *x* times value of *y*,                  *Scalar*
   *x* = *y*,   set value of *x* to current value of *y*,

algo
****
The object *algo* can be used to evaluate
a function :math:`f : \textbf{R}^n \rightarrow \textbf{R}^m` .

ell
***
This determines *n* and *m* for the particular derived class object.

setup
*****
This is a pure virtual function; i.e., it must be defined by the derived class.
It is used to initialize the function object.

domain
******
This pure virtual function returns the dimension of the domain space for
the function; i.e., *n*

range
*****
This pure virtual function returns the dimension of the range space for
the function; i.e., *m*

x
*
The argument *x* has size *n* and elements of type *Scalar* .

y
*
The return value *y* has size *n* and is equal to :math:`f(x)` .

Derived Classes
***************
{xrst_toc_table
   include/cmpad/det_by_minor.hpp
}

{xrst_end fun_algo}
---------------------------------------------------------------------------
*/
// BEGIN C++
# include <cmpad/vector.hpp>

namespace cmpad {
   template <class Scalar> struct fun_algo {
      // setup
      virtual void setup(size_t ell) = 0;
      // n
      virtual size_t domain(void) = 0;
      // m
      virtual size_t range(void) = 0;
      //
      // operator()
      virtual const cmpad::vector<Scalar>& operator()(
         const cmpad::vector<Scalar>& x
      ) = 0;
   };
}
// END C++
# endif
