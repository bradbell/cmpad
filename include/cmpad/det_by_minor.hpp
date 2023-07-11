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
| ``cmpad::det_by_minor`` < *Scalar* > *det* ( *m* )
| *d* = *det* ( *a* )

Prototype
*********
{xrst_literal
   // BEGIN CLASS
   // END CLASS
}
{xrst_literal
   // BEGIN CONSTRUCTOR
   // END CONSTRUCTOR
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
This is the row and column dimension for the matrices.

a
*
The argument *a* is a *Vector* with length :math:`m * m` and with
elements of type *Scalar* .
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
# include <vector>

// BEGIN cmpad namespace
namespace cmpad {

// BEGIN CLASS
template <class Scalar>
class det_by_minor {
// END CLASS
private:
   //
   // m_
   // size for the matrix
   const size_t        m_;
   //
   // r_, c_
   // row and column indices so that minor is entire matrix.
   std::vector<size_t> r_;
   std::vector<size_t> c_;
   //
   // a_
   // temporary vector declared here to avoid reallocation for each use
   std::vector<Scalar> a_;
public:
   // BEGIN CONSTRUCTOR
   det_by_minor(size_t m) 
   // END CONSTRUCTOR
   : m_(m) , r_(m + 1) , c_(m + 1), a_(m * m)
   {  //
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
   // BEGIN OPERATOR()
   template <class Vector>
   Scalar operator()(const Vector &x)
   // END OPERATOR()
   {  //
      // a_
      // copy from type Vector to std::vector<Scalar>
      for(size_t i = 0; i < m_ * m_; ++i)
         a_[i] = x[i];
      //
      // det
      // compute determinant of entire matrix
      Scalar det = det_of_minor(a_, m_, m_, r_, c_);
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
