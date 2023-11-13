# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin pytorch_llsq_obj}

Pytorch Least Squares Linear Regression Objective
#################################################

Function
********
see :ref:`py_llsq_obj-name` .

Source Code
***********
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end pytorch_llsq_obj}
'''
# BEGIN PYTHON
import numpy
import torch
class llsq_obj :
   def domain(self) :
      return self.n_arg
   def range (self) :
      return 1
   #
   def setup(self, option) :
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
      self.t     = torch.tensor(t, dtype=float)
      self.q     = torch.tensor(q, dtype=float)
   #
   def __call__(self, ax) :
      assert len(ax) == self.n_arg
      #
      # model
      model = 0.0
      ti  = torch.ones( len(self.t) , dtype=float)
      for i in range(self.n_arg) :
         model = model + ax[i] * ti
         ti    = ti * self.t
      #
      # squared_residual
      squared_residual = torch.square(model - self.q)
      #
      # objective
      objective = 0.5 * squared_residual.sum()
      #
      return objective.view(1)
# END PYTHON
