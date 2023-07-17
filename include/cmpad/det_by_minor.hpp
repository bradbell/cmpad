# ifndef CMPAD_DET_BY_MINOR_HPP
# define CMPAD_DET_BY_MINOR_HPP
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2003-23 Bradley M. Bell
// ----------------------------------------------------------------------------
/*
{xrst_begin_parent det_by_minor}

Determinant Using Expansion by Minors
#####################################

Syntax
******

| ``# include <cmpad/det_by_minor.hpp>``
| ``cmpad::det_by_minor`` < *Scalar* > *det*
| *det* . ``setup`` ( *ell* )
| *det* . ``domain`` ()
| *det* . ``range`` ()
| *y* = *det* ( *x* )

Prototype
*********
{xrst_literal ,
   // BEGIN CLASS,    // END CLASS
   // BEGIN SETUP,    // END SETUP
   // BEGIN DOMAIN,   // END DOMAIN
   // BEGIN RANGE,    // END RANGE
   // BEGIN OPERATOR, // END OPERATOR
}

Scalar
******
The type *Scalar* must satisfy the same conditions
as in the function :ref:`det_of_minor<det_of_minor@Scalar>` .

det
***
The object *det* can be used to evaluate
the determinant of *ell* by *ell* matrices using expansion by minors.

ell
***
This is the row and column dimension for subsequent use of the *det* object.
We also use the notation :math:`\ell` for this value.

x
*
The argument *x* has size :math:`\ell * \ell` .
The elements of the matrix :math:`A(x)` is defined as follows:
for :math:`i = 0 , \ldots , \ell-1` and :math:`j = 0 , \ldots , \ell-1`, by

.. math::

   A(x)_{i,j} = x[ i * \ell + j]

y
*
The return value *y* has size one and its element
is equal to the determinant of :math:`A(x)`.

{xrst_toc_hidden
   example/det_by_minor.cpp
}

Example
*******
The file
:ref:`det_by_minor.cpp-name`
contains an example and test of ``det_by_minor`` .

Source Code
***********
The page :ref:`det_by_minor.hpp-name`
displays the source code for this function

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
# include <cmpad/fun_algo.hpp>
# include <cmpad/det_of_minor.hpp>

// BEGIN cmpad namespace
namespace cmpad {

// BEGIN CLASS
// det_by_minor
template <class Scalar> class det_by_minor : public fun_algo<Scalar>
// END CLASS
{
private:
   // ell_
   // size of the matrix
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
   // BEGIN DOMAIN
   // domain
   size_t domain(void) override
   {  return ell_ * ell_; }
   // END DOMAIN
   // BEGIN RANGE
   // range
   size_t range(void) override
   {  return 1; }
   // END RANGE
   // BEGIN SETUP
   // setup
   void setup(size_t ell) override
   // END SETUP
   {  //
      // ell_, r_, c_, y_
      ell_ = ell;
      r_.resize(ell + 1);
      c_.resize(ell + 1);
      y_.resize(1);
      //
      // r_, c_
      // values that correspond to entire matrix
      for(size_t i = 0; i < ell; i++)
      {  r_[i] = i+1;
         c_[i] = i+1;
      }
      r_[ell] = 0;
      c_[ell] = 0;
   }
   // BEGIN OPERATOR
   // operator
   const cmpad::vector<Scalar>& operator()(
      const cmpad::vector<Scalar>& x
   ) override
   // END OPERATOR
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
