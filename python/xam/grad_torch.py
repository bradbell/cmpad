# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin xam_grad_torch.py}

Example and Test of Torch Gradient
##################################

check_grad_det
**************
see :ref:`check_grad_det.py-name` .

check_grad_ode
**************
see :ref:`check_grad_ode.py-name` .

Source Code
***********
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end xam_grad_torch.py}
'''
# BEGIN PYTHON
import cmpad
from check_grad_det  import check_grad_det
from check_grad_ode  import check_grad_ode
from check_grad_llsq import check_grad_llsq

def xam_grad_torch() :
   # ok
   ok = True
   #
   # grad_det, ok
   algo     = cmpad.det_by_minor()
   grad_det = cmpad.torch.gradient( algo )
   ok      &= check_grad_det( grad_det )
   #
   # grad_ode, ok
   algo     = cmpad.an_ode(cmpad.torch.like_numpy)
   grad_ode = cmpad.torch.gradient(algo)
   ok      &= check_grad_ode( grad_ode )
   #
   # grad_llsq, ok
   algo      = cmpad.llsq_obj(cmpad.torch.like_numpy)
   grad_llsq = cmpad.torch.gradient( algo )
   ok       &= check_grad_llsq( grad_llsq )
   #
   return ok
#
def test_xam_grad_torch() :
   assert xam_grad_torch() == True
# END PYTHON
