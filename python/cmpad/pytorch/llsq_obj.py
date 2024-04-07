# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin pytorch_llsq_obj}

Pytorch Linear Least Squares Objective
######################################

Syntax
******
| |tab| *llsq* = ``cmpad.pytorch.llsq_obj()``
| |tab| *llsq* . ``setup`` ( *option* )
| |tab| *obj* = *llsq* ( *x* )

Prototype
*********
{xrst_literal
   # BEGIN PROTOTYPE
   # END PROTOTYPE
}

Special
*******
This is a python implementation of the :ref:`llsq_obj-name` algorithm
that is specialized for the pytorch package.

n_arg
*****
see :ref:`llsq_obj@option@n_arg` .

n_other
*******
see :ref:`llsq_obj@option@n_other` .

Source Code
***********
The code below is the implementation of this function:
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}


{xrst_end pytorch_llsq_obj}
'''
# BEGIN PYTHON
import numpy
import torch
#
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
      assert option['n_arg'] > 0
      assert option['n_other'] > 0
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
