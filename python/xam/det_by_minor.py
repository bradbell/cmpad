# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------

import cmpad

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
   option = { 'n_arg' : ell * ell }
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

def test_det_by_minor() :
   assert xam_det_by_minor() == True
