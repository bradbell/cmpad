# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin_parent py_det_of_minor}
{xrst_spell
   factorization
}

Python Determinant of a Minor
#############################

Syntax
******
| |tab| *d* = ``cmpad::det_of_minor`` ( *a* , *n* , *m* , *r* , *c* )

Prototype
*********
{xrst_literal
   # BEGIN PROTOTYPE
   # END PROTOTYPE
}

Purpose
*******
This function computes the determinant of a minor of the matrix :math:`A`
using expansion by minors.
It is for example and testing purposes only.
Expansion by minors is chosen as an example because it uses
a lot of floating point operations yet does not require much source code.
This is not an efficient method for computing a determinant;
for example, using an LU factorization would be faster.

Minor
*****
The elements of the :math:`m \times m` minor :math:`M`
of the matrix :math:`A` are defined,
for :math:`i = 0 , \ldots , m-1` and :math:`j = 0 , \ldots , m-1`, by

.. math::

   M_{i,j} = A_{R(i), C(j)}

where the function
:math:`R(i)` is defined by the :ref:`argument r<cpp_det_of_minor@r>` and
:math:`C(j)` is defined by the :ref:`argument c<cpp_det_of_minor@c>` .


Determinant of A
****************
If the following conditions hold, the minor is the
entire matrix :math:`A` and hence ``det_of_minor``
will return the determinant of :math:`A`:

#. :math:`m = n`.
#. for :math:`i = 0 , \ldots , n-1`, :math:`r[i] = i+1`,
   and :math:`r[n] = 0`.
#. for :math:`j = 0 , \ldots , n-1`, :math:`c[j] = j+1`,
   and :math:`c[n] = 0`.

Scalar
******
We use *Scalar* for the type of the elements of *a* .
If *y* is a *Scalar* and *x* is a *Scalar* or ``float`` ,
the type *Scalar* must support the following operations:

.. csv-table::
   :widths: auto
   :header-rows: 1

   Syntax,           Description,                                   Result Type
   *x* = *y*,        set value of *x* to current value of *y*       *Scalar*
   *x* + *y*,        value of *x* plus *y*,                         *Scalar*
   *x* - *y*,        value of *x* minus *y*,                        *Scalar*
   *x* * *y*,        value of *x* times value of *y*,               *Scalar*

a
*
The elements of the :math:`n \times n` matrix :math:`A` are defined,
for :math:`i = 0 , \ldots , n-1` and :math:`j = 0 , \ldots , n-1`, by

.. math::

   A_{i,j} = a[ i * n + j]

n
*
This is the number of rows (and columns) in the square matrix :math:`A`.

m
*
This is the number of rows (and columns) in the square minor :math:`M`.

r
*
This defines the function :math:`R(i)`
which specifies the rows of the minor :math:`M`.
To be specific, the function :math:`R(i)`
for :math:`i = 1, \ldots , m-1` is defined by

.. math::

   \begin{eqnarray}
      R(0)   & = & r[n]
      \\
      R(i) & = & r[ R(i-1) ]
   \end{eqnarray}

All the elements of *r* have value less than or equal *n* ;
:math:`R(i) < n` and :math:`r[ R(m-1) ] = n` .
The elements of vector *r* are modified during the computation,
and restored to their original value before the return from ``det_of_minor`` .

c
*
This defines the function :math:`C(i)`
which specifies the columns of the minor :math:`M`.
To be specific, the function :math:`C(i)`
for :math:`j = 1, \ldots , m-1` is defined by

.. math::

   \begin{eqnarray}
      C(0)   & = & c[n]
      \\
      C(j) & = & c[ C(j-1) ]
   \end{eqnarray}

All the elements of *c* must have value less than or equal *n* ;
:math:`C(j) < n` and :math:`c[ C(m-1) ] = n` .
The elements of vector *c* are modified during the computation,
and restored to their original value before the return from ``det_of_minor`` .

d
*
The return value *d* is equal to the determinant of the minor :math:`M`.

{xrst_toc_table after
   python/xam/det_of_minor.py
}

Example
*******
:ref:`det_of_minor.py-name`
contains an example and test of ``det_of_minor`` .

{xrst_end py_det_of_minor}
---------------------------------------------------------------------------
{xrst_begin det_of_minor.py}

Python det_of_minor: Source Code
################################

{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end det_of_minor.py}
---------------------------------------------------------------------------
'''
# BEGIN PYTHON
# BEGIN PROTOTYPE
def det_of_minor(a, n, m, r, c) :
   assert  len(a) == n * n
   assert  len(r) == n + 1
   assert  len(c) == n + 1
   # END PROTOTYPE
   #
   # R0 = R(0)
   R0 = r[n]
   assert  R0 < n
   #
   # Cj = C(0)
   Cj = c[n]
   assert  Cj < n
   #
   # check if this is a 1 by 1 minor
   if  m == 1  :
      return a[ R0 * n + Cj ]
   #
   # detM
   # initialize determinant of the minor M
   detM = 0
   #
   # sign
   # initialize sign of factor for next sub-minor
   sign = 1
   #
   # r
   # remove row with index 0 in M from all the sub-minors of M
   r[n] = r[R0]
   #
   # C(j-1)
   # initial index in c for previous column of the minor M
   Cj1 = n
   #
   # for each column of M
   for j in range(m) :
      #
      # M[0,j] = A[ R0, Cj ]
      # element with index (0, j) in the minor M
      assert  Cj < n
      M0j = a[ R0 * n + Cj ]
      #
      # remove column with index j in M to form next sub-minor S of M
      c[Cj1] = c[Cj]
      #
      # detS
      # compute determinant of S, the sub-minor of M with
      # row R(0) and column C(j) removed.
      detS = det_of_minor(a, n, m - 1, r, c)
      #
      # restore column with index j in represenation of M as a minor of A
      c[Cj1] = Cj
      #
      # detM
      # include this sub-minor term in the summation
      if  sign > 0  :
         detM = detM + M0j * detS
      else :
         detM = detM - M0j * detS
      #
      # advance to next column of M
      Cj1  = Cj
      Cj   = c[Cj]
      sign = - sign
   #
   # r
   # restore row zero to the minor representation for M
   r[n] = R0
   #
   # return the determinant of the minor M
   return detM
# END PYTHON
