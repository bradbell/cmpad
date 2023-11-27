# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin py_llsq_obj}
{xrst_spell
   llsq
   obj
}

Python Least Squares Linear Regression Objective
################################################

Syntax
******
| |tab| *llsq* = ``cmpad.llsq_obj()``
| |tab| *llsq* . ``setup`` ( *option* )
| |tab| *obj* = *llsq* ( *x* )

Prototype
*********
{xrst_literal
   # BEGIN PROTOTYPE
   # END PROTOTYPE
}

Algorithm
*********
This is a python implementation of the an_ode :ref:`an_ode@Algorithm` .

Derivatives
***********
The pages below contain the implementation of this function
that is used when computing derivatives; i.e.,
when :ref:`run_cmpad@package` is not ``none`` .
{xrst_toc_table
   python/cmpad/pytorch/llsq_obj.py
}

n_arg
*****
see :ref:`llsq_obj@option@n_arg` .

n_other
*******
see :ref:`llsq_obj@option@n_other` .

Source Code
***********
The code below is the implementation of this function
that is used when compute the function value; i.e.,
when :ref:`run_cmpad@package` is ``none`` .
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end py_llsq_obj}
'''
# BEGIN PYTHON
import numpy

# BEGIN PROTOTYPE
class llsq_obj :
   def domain(self) :
      return self.n_arg
   def range (self) :
      return 1
   #
   def setup(self, option) :
      assert type(option) == dict
      assert type(option['n_arg']) == int
      assert type(option['n_other']) == int
      # END PROTOTYPE
      #
      # n_arg, n_other
      n_arg   = option['n_arg']
      n_other = option['n_other']
      #
      # t
      if n_other == 1 :
         t = numpy.array( [0.0 ] )
      else :
         t = numpy.linspace(-1.0, 1.0, n_other)
      #
      # q
      q = -1.0 * (t < 0) + 1.0 * (t > 0)
      #
      # self
      self.n_arg = n_arg
      self.t     = t
      self.q     = q
   #
   def __call__(self, x) :
      assert len(x) == self.n_arg
      #
      # model
      model = 0.0
      ti  = numpy.ones( len(self.t) )
      for i in range(self.n_arg) :
         model = model + x[i] * ti
         ti    = ti * self.t
      #
      # squared_residual
      squared_residual = numpy.square(model - self.q)
      #
      # objective
      objective = 0.5 * squared_residual.sum()
      #
      return numpy.asarray(objective).reshape(1)
# END PYTHON
