# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin xam_an_ode.py}

Example and Test of an_ode
##########################
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end xam_an_ode.py}
'''
# BEGIN PYTHON
import numpy
import cmpad
#
# xam_an_ode
def xam_an_ode() :
   #
   # ok
   ok = True
   #
   # n
   n = 4
   #
   # ode
   ode = cmpad.an_ode()
   #
   # ode.setup
   option = { 'n_arg' : n, 'n_other' : n-1 }
   ode.setup(option)
   #
   # x
   x   = [ 1.0, 2.0, 3.0, 4.0 ]
   ok &= len(x) == n
   #
   # yf
   yf = ode(x)
   #
   # rel_error
   rel_error = numpy.finfo(float).eps * 100.0
   #
   # ok
   tf  = 2.0
   yi  = x[0] * tf
   ok &= cmpad.near_equal( yf[0], yi, rel_error )
   for i in range(1, n) :
      yi  = x[i] * yi * tf / float(i+1)
      ok &= cmpad.near_equal( yf[i], yi, rel_error )
   #
   return ok
#
# test_xam_an_ode
def test_xam_an_ode() :
   assert xam_an_ode() == True
# END PYTHON
