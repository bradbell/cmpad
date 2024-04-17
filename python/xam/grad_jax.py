# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin xam_grad_jax.py}

Example and Test of jax Gradient
################################

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

{xrst_end xam_grad_jax.py}
'''
# BEGIN PYTHON
import cmpad
import jax
from check_grad_det  import check_grad_det
from check_grad_ode  import check_grad_ode
from check_grad_llsq import check_grad_llsq

def xam_grad_jax() :
   # ok
   ok = True
   #
   # grad_det, ok
   algo     = cmpad.det_by_minor()
   grad_det = cmpad.jax.gradient( algo )
   ok      &= check_grad_det( grad_det )
   #
   # grad_ode, ok
   algo     = cmpad.an_ode(cmpad.jax.like_numpy)
   grad_ode = cmpad.jax.gradient(algo)
   ok      &= check_grad_ode( grad_ode )
   #
   # grad_llsq, ok
   algo      = cmpad.llsq_obj(cmpad.jax.like_numpy)
   grad_llsq = cmpad.jax.gradient( algo )
   ok       &= check_grad_llsq( grad_llsq )
   #
   return ok
#
def test_xam_grad_jax() :
   assert xam_grad_jax() == True
# END PYTHON
