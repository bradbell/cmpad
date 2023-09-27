# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin_parent py_an_ode}
{xrst_spell
   Runge
   Kutta
   yf
   llll
   truncation
}

Use Python Runge-Kutta Method to Solve an ODE
#############################################

Syntax
******
| |tab| *ode* = ``cmpad.an_ode()``
| |tab| *ode* . ``setup`` ( *option* )
| |tab| *yf* = *ode* ( *x* )

Prototype
*********
{xrst_literal
   # BEGIN PROTOTYPE
   # END PROTOTYPE
}

Purpose
*******
This implements the :ref:`py_fun_obj-name` interface.
The function call uses :ref:`runge_kutta-name` to
compute the solution of the ODE defined below:

The ODE
*******

.. math::

   \begin{array}{llll}
   y_i '(t) & = & x_0                          & \mbox{for} \; i = 0 \\
   y_i '(t) & = & \sum_{j=1}^i x_j y_{i-1} (t) & \mbox{for} \; i > 0  \\
   \end{array}

Initial Value
*************

.. math::

   y_i (0) = 0  \; \mbox{for all} \; i

Solution
********
This initial value problem has the following analytic solution
(which can be used to check function values and derivatives):

.. math::

   \begin{array}{llll}
   y_0 (t) & = & x_0 t \\
   y_1 (t) & = & x_0 x_1 t^2 / 2 ! \\
   y_2 (t) & = & x_0 x_1 x_2 t^3 / 3 !
   \end{array}

.. math ::

   y_i (t) = \frac{t^{i+1}}{(i+1)!} \prod_{j=0}^i x_j \; \; \mbox{for all} \; i

ode
***
The object *ode* corresponding to :ref:`py_fun_obj@fun_obj`
in the function object interface.
It computes a Runge-Kutta approximation for :math:`y(t)` at :math:`t = 2` .
Note that this approximation for :math:`y_i (t)` has no truncation error
for :math:`i < 4` (because it is a fourth order method).

option
******
This contains the options that are used to setup the function object.

n_arg
=====
This is the size of the vectors *x* and *yf* .

x
*
This is the parameter vector that appears in
:ref:`py_an_ode@The ODE` above.

yf
**
The return value *yf* is :math:`y(t)` at :math:`t = 2` .

{xrst_toc_hidden after
   python/xam/an_ode.py
   python/cmpad/runge_kutta.py
}
Example
*******
:ref:`xam_an_ode.py-name` contains an example and test of ``an_ode`` .

Source Code
***********
:ref:`an_ode.py-name` is the source code for this algorithm.

{xrst_end py_an_ode}
------------------------------------------------------------------------------
{xrst_begin an_ode.py}

an_ode: Python Source Code
##########################
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end an_ode.py}
'''
# BEGIN PYTHON
import cmpad
#
# an_ode_fun
class an_ode_fun :
   #
   # __init__
   def __init__(self, x) :
      self.x = x
      self.n = len(x)
   #
   # __call__
   def __call__ (self, y) :
      assert len(y) == self.n
      assert len(self.x) == self.n
      #
      # dy
      dy    = [ self.x[0] ]
      for i in range(1, self.n) :
         dy.append( self.x[i] * y[i-1] )
      #
      return dy
#
# BEGIN PROTOTYPE
class an_ode :
   #
   def option(self) :
      return self.option
   #
   def domain(self) :
      return self.n
   #
   def range(self) :
      return self.n
   #
   def setup(self, option) :
      assert type(option) == dict
      assert type( option['n_arg'] ) == int
      # END PROTOTYPE
      #
      # option
      self.option = option
      #
      # n
      self.n = option['n_arg']
   #
   def __call__(self, x) :
      assert len(x) == self.n
      #
      # Scalar
      Scalar = type(x[0])
      #
      # yi
      yi = self.n * [ Scalar(0.0) ]
      #
      # fun
      fun = an_ode_fun(x)
      #
      # tf
      tf = Scalar(2.0)
      #
      # ns
      ns = self.n
      #
      # yf
      yf = cmpad.runge_kutta(fun, yi, tf, ns)
      #
      assert  len(yf) == self.n
      return yf
# END PYTHON
