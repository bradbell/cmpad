# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin xam_grad_pytorch.py}

Example and Test of pytorch Gradient
####################################

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

{xrst_end xam_grad_pytorch.py}
'''
# BEGIN PYTHON
import cmpad
from check_grad_det import check_grad_det
from check_grad_ode import check_grad_ode

def xam_grad_pytorch() :
   # ok
   ok = True
   #
   # grad_det
   algo     = cmpad.det_by_minor()
   grad_det = cmpad.pytorch.gradient( algo )
   #
   # ok
   ok &= check_grad_det( grad_det )
   #
   if False :
      # grad_ode
      algo     = cmpad.an_ode()
      grad_ode = cmpad.pytorch.gradient(algo)
      #
      # ok
      ok &= check_grad_ode( grad_ode )
   #
   return ok
#
def test_xam_grad_pytorch() :
   assert xam_grad_pytorch() == True
# END PYTHON
