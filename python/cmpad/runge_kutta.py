# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin_parent py_runge_kutta}
{xrst_spell
   dy
   int
   ns
   tf
   yf
   yi
   yt
}

Python Fourth Order Runge Kutta Method
######################################

Prototype
*********
{xrst_literal ,
   # BEGIN DEF, # END DEF
   # BEGIN RETURN, # END RETURN
}

Purpose
*******
This routine returns an approximate solution
for :math:`y( t^f )` where :math:`y(0) = y^i` and
:math:`y' (t) = f(y)` .

like_numpy
**********
This is a :ref:`like_numpy-name` class.

fun
***
This is a :ref:`py_fun_obj-name` .
The syntax *dy* = *fun* ( *yt* ) ,
were *yt* is :math:`y(t)` ,
sets *dy* equal to the derivative :math:`y'(t)`  .

yi
**
is the value of :math:`y(t)` at :math:`t = 0` .
This is a vector like object with elements of type
``float`` or *Scalar* .

tf
**
is the value of *t* at which we wish to evaluate :math:`y(t)` .
This is an object of type ``float`` or *Scalar* .

ns
**
is the number of :ref:`Runge-Kutta steps<rk4_step-name>` to use.
The more steps the smaller the step size and the more accurate
the solution.
This is an ``int`` .

yf
**
The return value *yf* has the same size as *yi* and is the approximation
for :math:`y(t)` at *t* = *tf* .
This is a vector like object with elements of type ``float`` or *Scalar* .

{xrst_toc_hidden after
   python/xam/runge_kutta.py
}

Source Code
***********
:ref:`runge_kutta.py-name`


Example
*******
:ref:`xam_runge_kutta.py-name`
contains an example and test of ``py_runge_kutta`` .

{xrst_end py_runge_kutta}
---------------------------------------------------------------------------
{xrst_begin runge_kutta.py}

Python runge_kutta Source Code
##############################

{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end runge_kutta.py}
---------------------------------------------------------------------------
'''
# BEGIN PYTHON
# BEGIN DEF
def runge_kutta(like_numpy, fun, yi, tf, ns) :
   assert type(ns) == int
   assert type(yi) == type( like_numpy.array(1.0) )
   # END DEF
   #
   # two, six
   two = like_numpy.array( 2.0 )
   six = like_numpy.array( 6.0 )
   #
   # h
   h = like_numpy.array( tf / float(ns) )
   #
   # i_step, yf
   yf = yi
   for i_step in range(ns) :
      #
      # k1
      k1 = fun(yf)
      #
      # k2
      y_tmp = yf + k1 * (h / two)
      k2    = fun(y_tmp)
      #
      # k3
      y_tmp = yf + k2 * (h / two)
      k3    = fun(y_tmp)
      #
      # k4
      y_tmp = yf + k3 * h
      k4    = fun(y_tmp)
      #
      # yf
      yf = yf + (k1 + two * k2 + two * k3 + k4) * (h / six)
   #
   # BEGIN RETURN
   return yf
   # END RETURN
# END PYTHON
