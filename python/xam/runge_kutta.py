# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin xam_runge_kutta.py}
{xrst_spell
   runge
   kutta
}

Example and Test of Python runge_kutta
######################################

ODE
***

.. math::

   y_i '(t) & = 0           \; & \mbox{for} \; i = 0 \\
   y_i '(t) & = y_{i-1} (t) \; & \mbox{for} \; i > 0

Initial Value
*************

.. math::

   y_i (0) & = 1   \; & \mbox{for} \; i = 0 \\
   y_i (0) & = 0   \; & \mbox{for} \; i > 0 \\

Solution
********

.. math::

   y_0 (t) & = 1               \\
   y_1 (t) & = t               \\
   y_i (t) & = t^i / i !       \\

Source Code
***********
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end xam_runge_kutta.py}
'''
# BEGIN PYTHON
import numpy
import cmpad
#
# fun
def fun(y) :
   # n
   n = len(y)
   #
   # dy
   dy    = n * [0.0]
   dy[0] = 0.0
   for i in range(1, n) :
      dy[i] = y[i-1]
   #
   return dy

#
# xam_runge_kutta
def xam_runge_kutta() :
   #
   # ok
   ok = True
   #
   # yi
   yi = [ 1.0, 0.0, 0.0, 0.0, 0.0 ]
   #
   # tf
   tf = 1.0
   #
   # ns
   ns = 1
   #
   # yf
   yf = cmpad.runge_kutta(fun, yi, tf, ns)
   #
   # rel_error
   rel_error = numpy.finfo(float).eps * 100.0
   #
   # ok
   ok &= cmpad.near_equal( yf[0], yi[0], rel_error )
   #
   # factorial
   # Note that y_i (t) = t^i / i! has no truncation error for i < 5.
   factorial = 1.0
   for i in range( 1, len(yi) ) :
      factorial *= i
      ok &= cmpad.near_equal( yf[i], 1.0 / factorial, rel_error )
   #
   return ok

#
# test_xam_runge_kutta
def test_xam_runge_kutta() :
   assert xam_runge_kutta() == True
# END PYTHON
