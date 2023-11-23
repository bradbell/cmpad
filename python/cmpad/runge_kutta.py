# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin_parent py_runge_kutta}
{xrst_spell
   Runge
   Kutta
   yf
   yi
   tf
   ns
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

fun
***
This is a :ref:`py_fun_obj-name` .
The syntax *dy* = *fun* ( *yt* ) ,
were *yt* is :math:`y(t)` ,
sets *dy* equal to the derivative :math:`y'(t)`  .

Scalar
******
We use *Scalar* for the scalar type corresponding to this function object;
see :ref:`py_fun_obj@Scalar Type` .
This type must support the following operations where
*a* and *b* have type *Scalar* or ``float`` .

.. csv-table::
   :widths: auto
   :header-rows: 1

   Syntax,    Description,                                     Result Type
   a + b,     value of *a* plus *b*,                           *Scalar*
   a * b,     value of *a* times *b*,                          *Scalar*
   a / b,     value of *a* divided by *b*,                     *Scalar*

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

{xrst_toc_table after
   python/xam/runge_kutta.py
}
Example
*******
:ref:`xam_runge_kutta.py-name`
contains an example and test of ``py_runge_kutta`` .

{xrst_end py_runge_kutta}
---------------------------------------------------------------------------
{xrst_begin runge_kutta.py}
{xrst_spell
   runge
   kutta
}

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
def runge_kutta(fun, yi, tf, ns) :
   assert type(ns) == int
   # END DEF
   #
   # two, six
   two = 2.0
   six = 6.0
   # n
   n = len(yi)
   #
   # h
   h = tf / float(ns)
   #
   # i_step, yf
   yf = yi
   for i_step in range(ns) :
      #
      # k1
      k1 = fun(yf)
      #
      # k2
      y_tmp = n * [0.0]
      for i in range(n) :
         y_tmp[i] = yf[i] + h * k1[i] / two
      k2 = fun(y_tmp)
      #
      # k3
      for i in range(n) :
         y_tmp[i] = yf[i] + h * k2[i] / two
      k3 = fun(y_tmp)
      #
      # k4
      for i in range(n) :
         y_tmp[i] = yf[i] + h * k3[i]
      k4 = fun(y_tmp)
      #
      # yf
      for i in range(n) :
         yf[i] = yf[i] + h * (k1[i] + two * k2[i] + two * k3[i] + k4[i]) / six
   #
   # BEGIN RETURN
   type_set = { float }
   for i in range( len(yi) ) :
      type_set.add( type(yi[i]) )
      type_set.add( type(yf[i]) )
   assert len( type_set ) <= 2
   #
   assert len(yf) == len(yi)
   return yf
   # END RETURN
# END PYTHON
