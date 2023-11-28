# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin_parent py_det_by_minor}

Python Determinant Using Expansion by Minors
############################################

Syntax
******
| |tab| *det* = ``cmpad.det_by_minor()``
| |tab| *det* . ``setup`` ( *option* )
| |tab| *y* = *det* ( *x* )

Prototype
*********
{xrst_literal
   # BEGIN PROTOTYPE
   # END PROTOTYPE
}

Algorithm
*********
This is a Python implementation of the
det_by_minor :ref:`det_by_minor@Algorithm` .

Scalar
******
We use *Scalar* for the type of the elements of *x* and *y*.

det
***
The :ref:`py_fun_obj-name` *det* computes the determinant of a square matrix.

ell
***
see :ref:`det_by_minor@ell` .

n_arg
*****
see :ref:`det_by_minor@option@n_arg` .

n_other
=======
see :ref:`det_by_minor@option@n_other` .

x
*
The argument *x* has size *n_arg* = :math:`\ell * \ell` .
The elements of the matrix :math:`A(x)` is defined as follows:
for :math:`i = 0 , \ldots , \ell-1` and :math:`j = 0 , \ldots , \ell-1`, by

.. math::

   A(x)_{i,j} = x[ i * \ell + j]

y
*
The return value *y* has length one and its element
is equal to the determinant of :math:`A(x)`.

{xrst_toc_hidden after
   python/xam/det_by_minor.py
   python/cmpad/det_of_minor.py
}

Example
*******
The file
:ref:`xam_det_by_minor.py-name`
contains an example and test of ``det_by_minor`` .

Source Code
***********
:ref:`det_by_minor.py-name` displays the source code for this algorithm.

{xrst_end py_det_by_minor}
---------------------------------------------------------------------------
{xrst_begin det_by_minor.py}

Python det_by_minor: Source Code
################################
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end det_by_minor.py}
---------------------------------------------------------------------------
'''
# BEGIN PYTHON
import math
import cmpad
# BEGIN PROTOTYPE
class det_by_minor :
   #
   def option(self) :
      return self.option
   #
   def domain(self) :
      return self.option['n_arg']
   #
   def range(self) :
      return 1
   #
   def setup(self, option) :
      assert type(option) == dict
      assert type( option['n_arg'] ) == int
      assert type( option['n_other'] ) == int
      assert option['n_arg'] > 0
      assert option['n_other'] == 0
      # END PROTOTYPE
      #
      # option
      self.option = option
      #
      # self.ell
      ell = int( math.sqrt( option['n_arg'] ) )
      if( ell * ell < option['n_arg'] ) :
         ell += 1
      assert ell * ell == option['n_arg']
      self.ell = ell
      #
      # r, c
      self.r = (ell + 1) * [0]
      self.c = (ell + 1) * [0]
      for i in range(ell) :
         self.r[i] = i + 1
         self.c[i] = i + 1
      self.r[ell] = 0
      self.c[ell] = 0
   #
   # call
   def __call__(self, x) :
      #
      # d
      d = cmpad.det_of_minor(x, self.ell, self.ell, self.r, self.c)
      #
      return [ d ]

# END PYTHON
