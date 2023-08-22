// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_ALGO_DET_OF_MINOR_HPP
# define CMPAD_ALGO_DET_OF_MINOR_HPP
/*
{xrst_begin_parent det_of_minor}
{xrst_spell
   factorization
}

Determinant of a Minor
######################

Syntax
******

| ``# include <cmpad/algo/det_of_minor.hpp>``
| *d* = ``cmpad::det_of_minor`` ( *a* , *m* , *n* , *r* , *c* )

Prototype
*********
{xrst_literal
   // BEGIN PROTOTYPE
   // END PROTOTYPE
}

Purpose
*******
This template function
computes the determinant of a minor of the matrix :math:`A`
using expansion by minors.
It is for example and testing purposes only.
Expansion by minors is chosen as an example because it uses
a lot of floating point operations yet does not require much source code.
This is not an efficient method for computing a determinant;
for example, using an LU factorization would be faster.

Minor
*****
The elements of the :math:`n \times n` minor :math:`M`
of the matrix :math:`A` are defined,
for :math:`i = 0 , \ldots , n-1` and :math:`j = 0 , \ldots , n-1`, by

.. math::

   M_{i,j} = A_{R(i), C(j)}

where the functions
:math:`R(i)` is defined by the :ref:`argument r<det_of_minor@r>` and
:math:`C(j)` is defined by the :ref:`argument c<det_of_minor@c>` .


Determinant of A
****************
If the following conditions hold, the minor is the
entire matrix :math:`A` and hence ``det_of_minor``
will return the determinant of :math:`A`:

#. :math:`n = m`.
#. for :math:`i = 0 , \ldots , m-1`, :math:`r[i] = i+1`,
   and :math:`r[m] = 0`.
#. for :math:`j = 0 , \ldots , m-1`, :math:`c[j] = j+1`,
   and :math:`c[m] = 0`.

Scalar
******
This is the type of the elements of *a* .
If *x* and *y* are *Scalar* objects,
the type *Scalar* must support the following operations:

.. csv-table::
   :widths: auto
   :header: Syntax, Description, Result Type

   *Scalar* (0), constructor for *Scalar* object equal to zero, *Scalar*
   *Scalar* ( *x* ), constructor for *Scalar* object equal to *x* , *Scalar*
   *x* = *y*, set value of *x* to current value of *y*
   *x* + *y*, value of *x* plus *y*, *Scalar*
   *x* - *y*, value of *x* minus *y*, *Scalar*
   *x* * *y*, value of *x* times value of *y*, *Scalar*

a
*
The elements of the :math:`m \times m` matrix :math:`A` are defined,
for :math:`i = 0 , \ldots , m-1` and :math:`j = 0 , \ldots , m-1`, by

.. math::

   A_{i,j} = a[ i * m + j]

m
*
This is the number of rows (and columns) in the square matrix :math:`A`.

n
*
This is the number of rows (and columns) in the square minor :math:`M`.

r
*
This defines the function :math:`R(i)`
which specifies the rows of the minor :math:`M`.
To be specific, the function :math:`R(i)`
for :math:`i = 1, \ldots , n-1` is defined by

.. math::

   \begin{eqnarray}
      R(0)   & = & r[m]
      \\
      R(i) & = & r[ R(i-1) ]
   \end{eqnarray}

All the elements of *r* have value less than or equal *m* ;
:math:`R(i) < m` and :math:`r[ R(n-1) ] = m` .
The elements of vector *r* are modified during the computation,
and restored to their original value before the return from ``det_of_minor`` .

c
*
This defines the function :math:`C(i)`
which specifies the columns of the minor :math:`M`.
To be specific, the function :math:`C(i)`
for :math:`j = 1, \ldots , n-1` is defined by

.. math::

   \begin{eqnarray}
      C(0)   & = & c[m]
      \\
      C(j) & = & c[ C(j-1) ]
   \end{eqnarray}

All the elements of *c* must have value less than or equal *m* ;
:math:`C(j) < m` and :math:`c[ C(n-1) ] = m` .
The elements of vector *c* are modified during the computation,
and restored to their original value before the return from ``det_of_minor`` .

d
*
The return value *d* is equal to the determinant of the minor :math:`M`.

{xrst_toc_table after
   xam/det_of_minor.cpp
}

Example
*******
:ref:`xam_det_of_minor.cpp-name`
contains an example and test of ``det_of_minor`` .

{xrst_end det_of_minor}
---------------------------------------------------------------------------
{xrst_begin det_of_minor.hpp}

det_of_minor: Source Code
#########################

{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end det_of_minor.hpp}
---------------------------------------------------------------------------
*/
// BEGIN C++
# include <cassert>
# include <cstddef>
# include <cmpad/vector.hpp>

namespace cmpad { // BEGIN cmpad namespace

// BEGIN PROTOTYPE
template <class Scalar>
Scalar det_of_minor(
   const cmpad::vector<Scalar>&    a  ,
   size_t                          m  ,
   size_t                          n  ,
   cmpad::vector<size_t>&          r  ,
   cmpad::vector<size_t>&          c  )
{  assert( a.size() == m * m );
   assert( r.size() == m + 1 );
   assert( c.size() == m + 1 );
   // END PROTOTYPE
   //
   // R0 = R(0)
   size_t R0 = r[m];
   assert( R0 < m );
   //
   // Cj = C(0)
   size_t Cj = c[m];
   assert( Cj < m );
   //
   //
   // check if this is a 1 by 1 minor
   if( n == 1 ) return a[ R0 * m + Cj ];
   //
   // detM
   // initialize determinant of the minor M
   Scalar detM(0);
   //
   // sign
   // initialize sign of factor for next sub-minor
   int sign = 1;
   //
   // r
   // remove row with index 0 in M from all the sub-minors of M
   r[m] = r[R0];
   //
   // C(j-1)
   // initial index in c for previous column of the minor M
   size_t Cj1 = m;
   //
   // for each column of M
   for(size_t j = 0; j < n; j++)
   {
      // M[0,j] = A[ R0, Cj ]
      // element with index (0, j) in the minor M
      assert( Cj < m );
      Scalar M0j = a[ R0 * m + Cj ];
      //
      // remove column with index j in M to form next sub-minor S of M
      c[Cj1] = c[Cj];
      //
      // detS
      // compute determinant of S, the sub-minor of M with
      // row R(0) and column C(j) removed.
      Scalar detS = det_of_minor(a, m, n - 1, r, c);
      //
      // restore column with index j in represenation of M as a minor of A
      c[Cj1] = Cj;
      //
      // detM
      // include this sub-minor term in the summation
      if( sign > 0 )
         detM = detM + M0j * detS;
      else
         detM = detM - M0j * detS;
      //
      // advance to next column of M
      Cj1  = Cj;
      Cj   = c[Cj];
      sign = - sign;
   }
   //
   // r
   // restore row zero to the minor representation for M
   r[m] = R0;
   //
   // return the determinant of the minor M
   return detM;
}

} // END cmpad namespace
// END C++
# endif
