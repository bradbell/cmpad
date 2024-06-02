// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_GRADIENT_VEC_HPP
# define CMPAD_GRADIENT_VEC_HPP
/*
{xrst_begin cpp_gradient_vec}
{xrst_spell
   typedef
}

C++ Abstract Class For Calculating Gradient
###########################################

Syntax
******
| |tab| ``# include <cmpad/gradient_vec.hpp``
| |tab| *Algo* *algo*
| |tab| ``cmpad::gradient_vec`` < *Algo* > *grad*
| |tab| *g* = *grad* ( *x* )

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}


Algo
****
The *Algo* class is derived from the :ref:`cpp_fun_obj_vec-name` class.
The *algo* object is initialized using its
:ref:`cpp_fun_obj_vec@setup` member function.
The gradient is for the last component of the range space of the algorithm.
Hence, *algo*.range() can be greater than one.

grad
****
This is a :ref:`cpp_fun_obj_vec-name` interface to the
gradient of the function corresponding to *algo* .
It calculates the gradient of the last component of the vector
returned by *algo*.
It is initialized using its ``setup`` member function
(which in turn will initialize *algo* with its ``setup`` syntax).
The ``setup`` should do calculations that do not depend on *x*
(to make the evaluation of the gradient faster).
We use *Grad* to denote the type of *grad* ; i.e.,

| |tab| ``typedef cmpad::gradient_vec`` < *Algo* > *Grad*


vector_type
***********
The type of the vectors *x* and *g* is

| |tab| ``typedef cmpad::vector<double>`` *Grad* :: ``vector_type``

(This is different from *Algo* :: ``vector_type`` .)

scalar_type
***********
The type of the elements of *x* and *g* is

| |tab| ``typedef double`` *Grad* :: ``scalar_type``

(This is different from *Algo* :: ``scalar_type`` .)


domain
******
This returns the dimension of the
:ref:`cpp_fun_obj_vec@domain` space dimension for the function and gradient.

range
*****
This returns the dimension of the
:ref:`cpp_fun_obj_vec@range` space dimension for the gradient.
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
   cpp/include/cmpad/autodiff/gradient_vec.hpp
   cpp/include/cmpad/adolc/gradient_vec.hpp
   cpp/include/cmpad/adept/gradient_vec.hpp
   cpp/include/cmpad/cppad/gradient_vec.hpp
}

{xrst_end cpp_gradient_vec}
-------------------------------------------------------------------------------
*/
// BEGIN C++
# include <cmpad/fun_obj.hpp>
# include <cmpad/fun_obj_vec.hpp>

namespace cmpad {
   // gradient_vec
   template <class Algo> class gradient_vec : public fun_obj<double> {
   public:
      // scalar_type
      typedef double scalar_type;
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
