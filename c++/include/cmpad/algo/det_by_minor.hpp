# ifndef CMPAD_ALGO_DET_BY_MINOR_HPP
# define CMPAD_ALGO_DET_BY_MINOR_HPP
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ----------------------------------------------------------------------------
/*
{xrst_begin_parent det_by_minor}

Determinant Using Expansion by Minors
#####################################

Syntax
******
|  ``# include <cmpad/algo/det_by_minor.hpp>``
|  ``cmpad::det_by_minor`` < *Scalar* > *det*
| *det* . ``setup`` ( *option* )
|  *y* = *det* ( *x* )

Prototype
*********
{xrst_literal
   // BEGIN DET_BY_MINOR
   // END DET_BY_MINOR
}

Purpose
*******
This implements the :ref:`fun_obj-name` interface.
The function call computes
the determinant of a square matrix using expansion by minors.

Scalar
******
If *u* and *v* are *Scalar* objects,
the type *Scalar* must support the following operations:

.. csv-table::
   :widths: auto
   :header-rows: 1

   Syntax,      Description,                                      Result Type
   Scalar(0),   constructor for *Scalar* object equal to zero,    *Scalar*
   Scalar(u),   constructor for *Scalar* object equal to *u*,     *Scalar*
   *u* + *v*,   value of *u* plus *v*,                            *Scalar*
   *u* - *v*,   value of *u* minus *v*,                           *Scalar*
   *u* * *v*,   value of *u* times value of *v*,                  *Scalar*
   *u* = *v*,   set value of *u* to current value of *v*,

value_type
**********
This is the same type as *Scalar* ; see :ref:`fun_obj@value_type` .

det
***
The object *det* corresponds to :ref:`fun_obj@fun` in the function
object interface.
It computes the determinant of a square matrix.

option
******
This contains options thats that are used to setup the function object.

n_arg
=====
This is the number of elements in the matrix
(number of arguments to the algorithm).
It must be a square and we use :math:``\ell`` to denote its square root; i.e,
the number of rows and columns in the matrix.

x
*
The argument *x* has size *n_arg* = :math:`\ell * \ell` .
The elements of the matrix :math:`A(x)` is defined as follows:
for :math:`i = 0 , \ldots , \ell-1` and :math:`j = 0 , \ldots , \ell-1`, by

.. math::

   A(x)_{i,j} = x[ i * \ell + j]

y
*
The return value *y* has size :math:`m = 1` and its element
is equal to the determinant of :math:`A(x)`.

{xrst_toc_hidden after
   c++/xam/det_by_minor.cpp
   c++/include/cmpad/algo/det_of_minor.hpp
}

Example
*******
The file
:ref:`xam_det_by_minor.cpp-name`
contains an example and test of ``det_by_minor`` .

Source Code
***********
:ref:`det_by_minor.hpp-name` is the source code for this algorithm.

{xrst_end det_by_minor}
---------------------------------------------------------------------------
{xrst_begin det_by_minor.hpp}

det_by_minor: Source Code
#########################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end det_by_minor.hpp}
---------------------------------------------------------------------------
*/
// BEGIN C++
# include <cmath> // for std::sqrt
# include <cmpad/fun_obj.hpp>
# include <cmpad/algo/det_of_minor.hpp>

namespace cmpad { // BEGIN cmpad namespace

// BEGIN DET_BY_MINOR
template <class Scalar> class det_by_minor : public fun_obj<Scalar>
// END DET_BY_MINOR
{
private:
   // option_
   option_t option_;
   //
   // ell_
   size_t ell_;
   //
   // r_, c_
   // row and column indices so that minor is entire matrix.
   cmpad::vector<size_t> r_;
   cmpad::vector<size_t> c_;
   //
   // y_
   cmpad::vector<Scalar> y_;
   //
public:
   // value_type
   typedef Scalar value_type;
   //
   // option
   const option_t& option(void) const override
   {  return option_; }
   // domain
   size_t domain(void) const override
   {  return option_.n_arg; }
   // range
   size_t range(void) const override
   {  return 1; }
   // setup
   void setup(const option_t& option) override
   {  //
      // option_
      option_ = option;
      //
      // ell_
      ell_ = size_t( std::sqrt( double( option.n_arg ) ) );
      if( ell_ * ell_ != option.n_arg )
         ++ell_;
      assert( ell_ * ell_ == option.n_arg );
      //
      // r_, c_, y_
      r_.resize(ell_ + 1);
      c_.resize(ell_ + 1);
      y_.resize(1);
      //
      // r_, c_
      // values that correspond to entire matrix
      for(size_t i = 0; i < ell_; i++)
      {  r_[i] = i+1;
         c_[i] = i+1;
      }
      r_[ell_] = 0;
      c_[ell_] = 0;
   }
   // operator
   const cmpad::vector<Scalar>& operator()(
      const cmpad::vector<Scalar>& x
   ) override
   {  //
      // y_
      // compute determinant of entire matrix
      y_[0] = det_of_minor(x, ell_, ell_, r_, c_);
      //
# ifndef NDEBUG
      // r_, c_
      // values that correspond to entire matrix
      // (not const because det_of_minor uses r_, c_ for work space)
      for(size_t i = 0; i < ell_; ++i)
      {  assert( r_[i] == i + 1 );
         assert( c_[i] == i + 1 );
      }
      assert( r_[ell_] == 0 );
      assert( c_[ell_] == 0 );
# endif
      return y_;
   }

};

} // END cmpad namespace
// END C++
# endif
