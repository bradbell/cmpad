# ifndef CMPAD_DET_BY_MINOR_HPP
# define CMPAD_DET_BY_MINOR_HPP
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ----------------------------------------------------------------------------
/*
{xrst_begin det_by_minor}
{xrst_spell
   std
   stoi
}

Determinant Using Expansion by Minors
#####################################

Syntax
******
|  ``# include <cmpad/det_by_minor.hpp``
|  ``cmpad::det_by_minor`` < *Scalar* > *det*
|  *det* . ``setup`` ( *option* )
|  *option* = *det* . ``option`` ()
|  *n* = *det* . ``domain`` ()
|  *m* = *det* . ``range`` ()
|  *y* = *det* ( *x* )

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

det
***
The object *det* corresponds to :ref:`fun_obj@fun` in the function
object interface.

option
******
This map has the following key:

size
====
The corresponding value can be converted to an integer using

|  std::stoi ( *option* [ ``"size"`` ] )

This is the row and column dimension for subsequent use of the *det* object.
We use the notation :math:`\ell` for this value.

x
*
The argument *x* has size :math:`n = \ell * \ell` .
The elements of the matrix :math:`A(x)` is defined as follows:
for :math:`i = 0 , \ldots , \ell-1` and :math:`j = 0 , \ldots , \ell-1`, by

.. math::

   A(x)_{i,j} = x[ i * \ell + j]

y
*
The return value *y* has size :math:`m = 1` and its element
is equal to the determinant of :math:`A(x)`.

{xrst_toc_hidden
   example/det_by_minor.cpp
}

Example
*******
The file
:ref:`det_by_minor.cpp-name`
contains an example and test of ``det_by_minor`` .

{xrst_end det_by_minor}
---------------------------------------------------------------------------
\{xrst_begin det_by_minor.hpp}

det_by_minor: Source Code
#########################
\{xrst_literal
   // BEGIN C++
   // END C++
}

\{xrst_end det_by_minor.hpp}
---------------------------------------------------------------------------
*/
// BEGIN C++
# include <cmpad/fun_obj.hpp>
# include <cmpad/det_of_minor.hpp>

// BEGIN cmpad namespace
namespace cmpad {

// det_by_minor
template <class Scalar> class det_by_minor : public fun_obj<Scalar>
{
private:
   // option_
   str2str_map option_;
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
   // option
   const str2str_map& option(void) const override
   {  return option_; }
   // domain
   size_t domain(void) const override
   {  return ell_ * ell_; }
   // range
   size_t range(void) const override
   {  return 1; }
   // setup
   void setup(const str2str_map& option) override
   {  //
      // option_
      option_ = option;
      //
      // ell_
      int ell = std::stoi( option.at("size") );
      assert( 0 < ell );
      ell_ = size_t(ell);
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
