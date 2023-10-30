# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin_parent autograd_gradient}
{xrst_spell
   obj
   numpy
}

Calculate Gradient Using autograd
#################################

Syntax
******
| |tab| *grad* ``cmpad.autograd.gradient`` ( *algo* )
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
have elements of type ``autograd.a_double`` .
The range space component *option* [ ``'n_other'`` ]
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
   python/xam/grad_autograd.py
}
Example
*******
The file :ref:`xam_grad_autograd.py-name`
contains an example and test using this class.

{xrst_end autograd_gradient}
------------------------------------------------------------------------------
{xrst_begin autograd_gradient.py}

Gradient Using autograd: Source Code
####################################

{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end autograd_gradient.py}
'''
# BEGIN PYTHON
#
# imports
import autograd
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
   def wrapper(self, x) :
      y = self.algo(x)
      return y[self.n_other]
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
      # self.n_other
      self.n_other = option['n_other']
      #
      # self.tape
      self.tape = autograd.grad(self.wrapper)
   #
   # call
   def __call__(self, x) :
      n_arg   = self.option['n_arg']
      assert len(x) == n_arg
      ax = autograd.numpy.empty(n_arg)
      for i in range(n_arg) :
         ax[i] = x[i]
      g = self.tape( ax )
      return g
# END PYTHON
