# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin_parent py_an_ode}
{xrst_spell
   kutta
   runge
   yf
}

Use Python Runge-Kutta Method to Solve an ODE
#############################################

Syntax
******
| |tab| *ode* = ``cmpad.an_ode( *like_numpy* )``
| |tab| *ode* . ``setup`` ( *option* )
| |tab| *yf* = *ode* ( *x* )

Prototype
*********
{xrst_literal
   # BEGIN PROTOTYPE
   # END PROTOTYPE
}

Algorithm
*********
This is a python implementation of the an_ode :ref:`an_ode@Algorithm` .

like_numpy
**********
This is a :ref:`like_numpy-name` class.

ode
***
The object *ode* corresponding to :ref:`py_fun_obj@fun_obj`
in the function object interface.

n_arg
*****
see :ref:`an_ode@option@n_arg` .

n_other
=======
see :ref:`an_ode@option@n_other` .

x
*
This is the :ref:`an_ode@ODE@Parameter Vector` that appears in the ODE.

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
:ref:`an_ode.py-name` displays the source code for this algorithm.

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
import numpy
#
# an_ode_fun
class an_ode_fun :
   #
   # __init__
   # self.x, self.n
   def __init__(self, like_numpy, x) :
      self.like_numpy = like_numpy
      self.x          = x
      self.n          = len(x)
   #
   # __call__
   def __call__ (self, y) :
      assert len(y) == self.n
      assert len(self.x) == self.n
      #
      # like_numpy
      like_numpy  = self.like_numpy
      #
      # dy
      dy    = [ like_numpy.array( self.x[0] ).reshape(-1) ]
      for i in range(1, self.n) :
         dy.append( like_numpy.array( self.x[i] * y[i-1] ).reshape(-1) )
      dy = like_numpy.concatenate( dy )
      #
      return dy
#
# BEGIN PROTOTYPE
class an_ode :
   def __init__(self, like_numpy) :
      self.like_numpy = like_numpy
   #
   def option(self) :
      return self.option
   #
   def domain(self) :
      return self.n_arg
   #
   def range(self) :
      return self.n_arg
   #
   def setup(self, option) :
      assert type(option) == dict
      assert type( option['n_arg'] ) == int
      assert type( option['n_other'] ) == int
      assert option['n_arg'] > 0
      assert option['n_other'] > 0
      # END PROTOTYPE
      #
      # option
      self.option = option
      #
      # self.n_arg
      self.n_arg = option['n_arg']
      #
      # self.n_other
      self.n_other = option['n_other']
   #
   def __call__(self, x) :
      assert len(x) == self.n_arg
      #
      # like_numpy
      like_numpy = self.like_numpy
      #
      # yi
      yi = like_numpy.array( self.n_arg * [ 0.0 ] )
      #
      # fun
      fun = an_ode_fun(like_numpy, x)
      #
      # tf
      tf = 2.0
      #
      # ns
      ns = self.n_other
      #
      # yf
      yf = cmpad.runge_kutta(like_numpy, fun, yi, tf, ns)
      #
      assert  len(yf) == self.n_arg
      if like_numpy == numpy :
         return yf
      return yf.vec
# END PYTHON
