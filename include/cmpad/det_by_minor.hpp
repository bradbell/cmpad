# ifndef CMPAD_SPEED_DET_BY_MINOR_HPP
# define CMPAD_SPEED_DET_BY_MINOR_HPP
// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2003-23 Bradley M. Bell
// ----------------------------------------------------------------------------
/*
{xrst_begin det_by_minor}

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

det
***
The object *det* can be used to evaluate
the determinant of *m* by *m* matrices using expansion by minors.

m
*
This is the row and column dimension for subsequent use of the *det* object.

a
*
The argument *a* has size :math:`m * m` and elements of type *Scalar* .
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
# include <cmpad/vector.hpp>

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
   cmpad::vector<size_t> r_;
   cmpad::vector<size_t> c_;
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
   Scalar operator()(const cmpad::vector<Scalar>& a)
   // END OPERATOR
   {  //
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
