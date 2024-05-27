# ifndef CMPAD_ALGO_DET_BY_MINOR_VEC_HPP
# define CMPAD_ALGO_DET_BY_MINOR_VEC_HPP
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ----------------------------------------------------------------------------
/*
{xrst_begin_parent cpp_det_by_minor_vec}

C++ Determinant Using Expansion by Minors
#########################################

Syntax
******
| |tab| ``# include <cmpad/algo/det_by_minor_vec`.hpp>``
| |tab| ``cmpad::det_by_minor_vec``` < *Vector* > *det*
| |tab| *det* . ``setup`` ( *option* )
| |tab| *y* = *det* ( *x* )

Prototype
*********
{xrst_literal
   // BEGIN DET_BY_MINOR
   // END DET_BY_MINOR
}

Algorithm
*********
This is an  :ref:`cpp_fun_obj_vec-name` interface
to the det_by_minor :ref:`det_by_minor@Algorithm` .

Vector
******
This is a fun_obj_vec :ref:`cpp_fun_obj_vec@Vector` type.

det
***
The object *det* corresponds to :ref:`cpp_fun_obj@fun` in the function
object interface.
It computes the determinant of a square matrix.

ell
***
see :ref:`det_by_minor@ell` .

n_arg
*****
see :ref:`det_by_minor@option@n_arg` .

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
   cpp/xam/det_by_minor_vec.cpp
}

Example
*******
The file
:ref:`xam_det_by_minor_vec.cpp-name`
contains an example and test of ``det_by_minor_vec`` .

Source Code
***********
:ref:`det_by_minor_vec.hpp-name` displays the source code for this algorithm.

{xrst_end cpp_det_by_minor_vec}
---------------------------------------------------------------------------
{xrst_begin det_by_minor_vec.hpp}

C++ det_by_minor_vec: Source Code
#################################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end det_by_minor_vec.hpp}
---------------------------------------------------------------------------
*/
// BEGIN C++
# include <cmath> // for std::sqrt
# include <cmpad/fun_obj_vec.hpp>
# include <cmpad/algo/det_of_minor.hpp>

namespace cmpad { // BEGIN cmpad namespace

// BEGIN DET_BY_MINOR
template <class Vector> class det_by_minor_vec : public fun_obj_vec<Vector>
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
   Vector y_;
   //
public:
   // value_type
   typedef typename Vector::value_type value_type;
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
      // n_arg, n_other
      assert( option.n_arg > 0 );
      assert( option.n_other == 0 );
      //
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
   const Vector& operator()(const Vector& x) override
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
