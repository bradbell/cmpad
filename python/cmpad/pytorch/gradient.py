# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin_parent pytorch_gradient}
{xrst_spell
   numpy
}

Calculate Gradient Using pytorch
################################

Syntax
******
| |tab| *grad* ``cmpad.pytorch.gradient`` ( *algo* )
| |tab| *grad* . ``setup`` ( *option* )
| |tab| *g* = *grad* ( *x* )


Purpose
*******
This implements a :ref:`py_fun_obj-name`
that computes the gradient of the last component of values
computed by *algo* .


algo
****
This is a py_fun_obj where the input and output vectors
have elements of type ``pytorch.a_double`` .
The last range space component
is used to define the scalar function that the gradient is for.

grad
****
This is a py_fun_obj where the input and output vectors
have elements of type ``float`` .

x
*
This is a numpy vector of ``float`` with length *option* [ ``'n_arg'`` ] .
It is the argument value at which to compute the gradient.

g
*
This is a numpy vector of ``float`` with length *option* [ ``'n_arg'`` ] .
It is the value of the gradient ad *x* .

{xrst_toc_hidden before
   python/xam/grad_pytorch.py
}
Example
*******
The file :ref:`xam_grad_pytorch.py-name`
contains an example and test using this class.

{xrst_end pytorch_gradient}
------------------------------------------------------------------------------
{xrst_begin pytorch_gradient.py}

Gradient Using pytorch: Source Code
###################################

{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end pytorch_gradient.py}
'''
# BEGIN PYTHON
#
# imports
import numpy
import torch
#
# gradient
class gradient :
   #
   def __init__(self, algo) :
      self.algo   = algo
      self.option = None
   #
   def option(self) :
      return self.optiion
   #
   def domain(self) :
      return self.option['n_arg']
   #
   def range(self) :
      return self.option['n_arg']
   #
   #
   def setup(self, option) :
      assert type(option) == dict
      assert 'n_arg' in option
      #
      # self.option
      self.option = option
      #
      # self.algo
      self.algo.setup(option)
      #
      # self.n_arg
      self.n_arg = self.algo.domain()
      assert self.n_arg == option['n_arg']
      #
   #
   # call
   def __call__(self, x) :
      # See https://discuss.pytorch.org/t/
      #     how-does-one-reuse-the-autograd-computational-graph/190447/2
      assert len(x) == self.n_arg
      ax = torch.tensor(x, requires_grad = True)
      az = self.algo(ax)
      az[-1].backward()
      return ax.grad
# END PYTHON
