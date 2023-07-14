# ifndef CMPAD_SPEED_DET_BY_MINOR_HPP
# define CMPAD_SPEED_DET_BY_MINOR_HPP
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2003-23 Bradley M. Bell
// ----------------------------------------------------------------------------
/*
{xrst_begin det_by_minor}
{xrst_spell
   th
}

Determinant Using Expansion by Minors
#####################################

Syntax
******

| ``# include <cmpad/det_by_minor.hpp>``
| ``cmpad::det_by_minor`` < *Scalar* > *det*
| *det* . ``setup`` ( *m* )
| *d* = *det* ( *a* )

Prototype
*********
{xrst_literal
   // BEGIN CLASS
   // END CLASS
}
{xrst_literal
   // BEGIN SETUP
   // END SETUP
}
{xrst_literal
   // BEGIN OPERATOR
   // END OPERATOR
}

Scalar
******
The type *Scalar* must satisfy the same conditions
as in the function :ref:`det_of_minor<det_of_minor@Scalar>` .

Vector
******
If *y* is a *Vector* object, it must support the syntax

   *y* [ *i* ]

where *i* has type ``size_t`` with value less than :math:`m * m`.
This must return a *Scalar* value corresponding to the *i*-th
element of the vector *y* .
This is the only requirement of the type *Vector* .

det
***
The object *det* can be used to evaluate
the determinant of *m* by *m* matrices using expansion by minors.

m
*
This is the row and column dimension for subsequent use of the *det* object.

a
*
The argument *a* is a *Vector* with length :math:`m * m` and with
elements of type *Scalar*
( *Vector* :: ``value_type`` must be *Scalar* ).
The elements of the :math:`m \times m` matrix :math:`A` are defined,
for :math:`i = 0 , \ldots , m-1` and :math:`j = 0 , \ldots , m-1`, by

.. math::

   A_{i,j} = a[ i * m + j]

d
*
The return value *d* is equal to the determinant of :math:`A`.

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
# include <cmpad/det_of_minor.hpp>
# include <cppad/utility/vector.hpp>

// BEGIN cmpad namespace
namespace cmpad {

// BEGIN CLASS
template <class Scalar>
class det_by_minor {
// END CLASS
private:
   //
   // m_
   // size of the matrix
   size_t m_;
   //
   // r_, c_
   // row and column indices so that minor is entire matrix.
   CppAD::vector<size_t> r_;
   CppAD::vector<size_t> c_;
   //
public:
   // BEGIN SETUP
   void setup(size_t m)
   // END SETUP
   {  //
      // m_, r_, c_
      m_ = m;
      r_.resize(m + 1);
      c_.resize(m + 1);
      //
      // r_, c_
      // values that correspond to entire matrix
      for(size_t i = 0; i < m; i++)
      {  r_[i] = i+1;
         c_[i] = i+1;
      }
      r_[m] = 0;
      c_[m] = 0;
   }
   //
   // BEGIN OPERATOR
   template <class Vector>
   Scalar operator()(const Vector& a)
   // END OPERATOR
   {  //
      static_assert(
         std::is_same< typename Vector::value_type , Scalar >::value ,
         "det_by_minor: elements of the vector a are not of type Scalar"
      );
      // det
      // compute determinant of entire matrix
      Scalar det = det_of_minor(a, m_, m_, r_, c_);
      //
# ifndef NDEBUG
      // r_, c_
      // values that correspond to entire matrix
      // (not const because det_of_minor uses r_, c_ for work space)
      for(size_t i = 0; i < m_; ++i)
      {  assert( r_[i] == i + 1 );
         assert( c_[i] == i + 1 );
      }
      assert( r_[m_] == 0 );
      assert( c_[m_] == 0 );
# endif
      return det;
   }

};

} // END cmpad namespace
// END C++
# endif
