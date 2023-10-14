# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin xam_det_by_minor.py}

Python Example and Test of det_by_of_minor
##########################################

{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end xam_det_by_minor.py}
'''
# BEGIN PYTHON
import cmpad
#
# xam_det_by_minor
def xam_det_by_minor() :
   #
   # ok
   ok = True
   #
   # ell
   # dimension of the matrix
   ell = 3;
   #
   # det
   det = cmpad.det_by_minor()
   #
   # det.setup
   option = { 'n_arg' : ell * ell , 'r_index' : 0 }
   det.setup(option)
   #
   # x
   x = [
      1., 2., 3., # x[0] x[1] x[2]
      3., 2., 1., # x[3] x[4] x[5]
      2., 1., 2.  # x[6] x[7] x[8]
   ]
   ok &= len(x) == ell * ell
   #
   # y
   y = det(x)
   #
   # check
   check = \
      + x[0]*(x[4]*x[8] - x[5]*x[7]) \
      - x[1]*(x[3]*x[8] - x[5]*x[6]) \
      + x[2]*(x[3]*x[7] - x[4]*x[6])
   #
   # ok
   ok &= y[0] == check
   #
   return ok
#
# test_det_by_minor
def test_det_by_minor() :
   assert xam_det_by_minor() == True
# END PYTHON
