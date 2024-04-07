# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin check_grad_det.py}

Check Python Gradient of Determinant
####################################

Syntax
******
| |tab| *ok* = ``check_grad_det`` ( *grad_det* )

grad_det
********
This is a ``float`` :ref:`py_fun_obj-title` .

option
******
The domain and range dimensions for the function object
are equal to *option* [ ``'n_arg'`` ];
see :ref:`py_fun_obj@option` .

ok
**
is true (false) if the gradient passes (fails) the test.

Source Code
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end check_grad_det.py}
'''
# BEGIN PYTHON
import numpy
import cmpad

def check_grad_det( grad_det ) :
   #
   # ok
   ok = True
   #
   # rel_error
   rel_error = 500. * numpy.finfo(float).eps
   #
   # ell
   for ell in [ 3, 4, 5] :
      # option
      option = {
         'n_arg'      : ell * ell       ,
         'n_other'    : 0               ,
         'time_setup' : bool( ell % 2 ) ,
      }
      #
      # grad_det
      grad_det.setup(option)
      #
      # x
      # values in the matrix in row major order
      x = numpy.random.uniform(0.0, 1.0, ell * ell)
      #
      # g
      g = grad_det(x)
      #
      # r, c
      # index values corresponding to computing determinat of entire matrix
      r = numpy.empty( ell+1, dtype=int )
      c = numpy.empty( ell+1, dtype=int )
      for i in range(ell) :
         r[i] = i+1
         c[i] = i+1
      r[ell] = 0
      c[ell] = 0
      #
      # i, j
      # for each row and column index in the matrix
      for i in range(ell) :
         for j in range(ell) :
            # r, c
            # minor with row i and column j removed
            if i == 0 :
               r[ell] = 1
            else :
               r[i-1] = i+1
            if j == 0 :
               c[ell] = 1
            else :
               c[j-1] = j+1
            #
            # det_minor
            # determinant of minor corresponding to (i, j) removed
            det_minor = cmpad.det_of_minor(x, ell, ell-1, r, c)
            #
            # check
            # derivative of determinant with respect matrix element (i, j)
            check = det_minor
            if (i + j) % 2 == 1 :
               check = - det_minor
            #
            # ok
            ok &= cmpad.near_equal(g[ i * ell + j ], check, rel_error, x)
            #
            # r, c
            # restore to computing determinant of entire matrix
            if i == 0 :
               r[ell] = 0
            else :
               r[i-1] = i
            if j == 0 :
               c[ell] = 0
            else :
               c[j-1] = j
   return ok
# END PYTHON
