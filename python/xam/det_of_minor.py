# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ----------------------------------------------------------------------------
r'''
{xrst_begin xam_det_of_minor.py}

Python Example and Test of det_of_minor
#######################################

{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end xam_det_of_minor.py}
'''
# BEGIN PYTHON
import cmpad
#
# xam_det_of_minor
def xam_det_of_minor () :
   #
   # ok
   ok = True
   #
   # a
   # values in the matrix A in row major order
   a = [
      1., 2., 3.,
      4., 5., 6.,
      7., 8., 10.
   ]
   #
   # m
   # dimension of the matrix A
   n = 3
   ok &= n * n ==  len(a)
   #
   # r, c
   # index vectors set so minor is the entire matrix A
   r = (n + 1) * [0]
   c = (n + 1) * [0]
   for i in range(n) :
      r[i] = i+1
      c[i] = i+1

   r[n] = 0
   c[n] = 0
   #
   # n
   # size of minor that is the entire matrix A
   m = n
   #
   # det
   # evaluate the determinant of A
   det = cmpad.det_of_minor(a, n, m, r, c)
   #
   # ok
   # check the value of the determinant of A
   ok &= det == (1*(5*10-6*8) - 2*(4*10-6*7) + 3*(4*8-5*7))
   #
   # M
   # minor where row 0 and column 1 are removed
   r[n] = 1     # skip row index 0 by starting at row index 1
   c[0] = 2     # skip column index 1 by pointing from index 0 to index 2
   m    = n - 1 # dimension of the minor M
   #
   # det
   # evaluate determinant of the minor
   det = cmpad.det_of_minor(a, n, m, r, c)
   #
   # ok
   # check the value of the determinant of the minor
   ok &= det ==  (4*10-6*7)
   #
   return ok
#
# test_det_of_minor
def test_det_of_minor () :
   assert xam_det_of_minor() == True
# END PYTHON
