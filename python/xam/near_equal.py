# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin xam_near_equal.py}

Example and Test of Python near_equal
#####################################
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end xam_near_equal.py}
'''
# BEGIN PYTHON
import sys
import io
import numpy
import cmpad
#
# xam_near_equal
def xam_near_equal() :
   #
   # ok
   ok = True
   #
   # rel_error
   rel_error = 1e-4
   #
   # x, y
   x = 3.000
   y = x * (1.0 + rel_error / 2 )
   #
   # ok
   ok &= cmpad.near_equal(x, y, rel_error)
   #
   # rel_error, vec, os
   rel_error  = rel_error / 10.0
   vec = []
   os  = io.StringIO("")
   #
   # ok
   ok &= not cmpad.near_equal(x, y, rel_error, vec, os)
   #
   # vec
   vec = [x * 10]
   #
   # ok
   ok &=   cmpad.near_equal(x, y, rel_error, vec)
   #
   return ok
#
# test_xam_near_equal
def test_xam_near_equal() :
   assert xam_near_equal() == True
# END PYTHON
