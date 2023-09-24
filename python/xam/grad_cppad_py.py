# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin xam_grad_cppad_py.py}

Example and Test of cppad_py Gradient
#####################################

check_grad_det
**************
{xrst_toc_table
   python/xam/check_grad_det.py
}

Source Code
***********
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end xam_grad_cppad_py.py}
'''
# BEGIN PYTHON
import cmpad
from check_grad_det import check_grad_det

def xam_grad_cppad_py() :
   # ok
   ok = True
   #
   # algo
   algo = cmpad.det_by_minor()
   #
   # grad_det
   grad_det = cmpad.cppad_py.gradient( algo )
   #
   # ok
   ok &= check_grad_det( grad_det )
   #
   return ok
#
def test_xam_grad_cppad_py() :
   assert xam_grad_cppad_py() == True
# END PYTHON
