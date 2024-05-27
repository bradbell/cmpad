// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ----------------------------------------------------------------------------
# ifndef CMPAD_FUN_OBJ_VEC_HPP
# define CMPAD_FUN_OBJ_VEC_HPP
/*
{xrst_begin cpp_fun_obj_vec}
{xrst_spell
   resize
   th
   typedef
   typename
}

The New Abstract Class for a C++ Function Object
################################################

Syntax
******
| |tab| ``# include <cmpad/fun_obj_vec.hpp``
| |tab| ``cmpad::fun_obj_vec`` < *Vector* > *fun*
| |tab| *fun* . ``setup`` ( *option* )
| |tab| *fun* . ``domain`` ( )
| |tab| *fun* . ``range`` ( )
| |tab| *y* = *fun* ( *x* )

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

Vector
******
The fun_obj_vec *Vector* class must support the following
where *vec* is a *Vector* object:

scalar_type
==========*
We use *scalar_type* to denote the type of the elements of *vec* :
{xrst_code cpp}
   typedef typename Vector::value_type scalar_type
{xrst_code}
If *i* is a positive integer constant and
*s*, *t* are *scalar_type* objects,
the following operations must be defined:

#. The constructors: *scalar_type* (i),  *scalar_type* (s) .
#. This binary operations:
   *s* + *t* ,
   *s* - *t* ,
   *s* * *t* ,
   *s* / *t* .


vec.resize(n)
=============
resize the vector to have size *n* where *n* is a ``size_t`` object.

vec.size()
==========
returns a ``size_t`` that is the current size of the vector.

vec[i]
======
returns a reference, or constant reference, to the i-th element of *vec*
where *i* is an ``size_t`` .

fun
***
This is the function object.
The corresponding function call,
*y* = *fun* ( *x* ),
computes *y* as a function of *x* .

vector_type
***********
A derived class must define *vector_type* to be the same as *Vector* .
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
This *Vector* has size *n* and
is the point at which the function is evaluated.

y
*
This *Vector* has size *m* and
is the function value corresponding to *x*.

{xrst_toc_hidden
   cpp/xam/fun_obj_vec.cpp
}
Example
*******
:ref:`xam_fun_obj_vec.cpp-name` is an example and test that uses this function.

{xrst_end cpp_fun_obj_vec}
---------------------------------------------------------------------------
*/
// BEGIN C++

# include <cmpad/option_t.hpp>
namespace cmpad {
   template <class Vector> struct fun_obj_vec {
      //
      // scalar_type
      typedef typename Vector::value_type scalar_type;
      //
      // setup
      virtual void setup(const option_t& option) = 0;
      //
      // option
      virtual const option_t& option(void) const = 0;
      //
      // domain
      virtual size_t domain(void) const = 0;
      //
      // range
      //
      virtual size_t range(void) const = 0;
      //
      // operator()
      virtual const Vector& operator()(const Vector& x) = 0;
   };
}
// END C++
# endif
