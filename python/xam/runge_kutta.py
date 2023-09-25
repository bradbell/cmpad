# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
import numpy
import cmpad

#
# near_equal
def near_equal(x, y, rel_error) :
   scale = max( abs(x), abs(y) )
   tiny      = numpy.finfo(float).tiny
   abs_error = max(rel_error * scale, tiny)
   return abs(x - y) <= abs_error

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
   ok &= near_equal( yf[0], yi[0], rel_error )
   #
   # factorial
   # Note that y_i (t) = t^i / i! has no truncation error for i < 5.
   factorial = 1.0
   for i in range( 1, len(yi) ) :
      factorial *= i
      ok &= near_equal( yf[i], 1.0 / factorial, rel_error )
   #
   return ok

#
# test_xam_runge_kutta
def test_xam_runge_kutta() :
   assert xam_runge_kutta() == True
