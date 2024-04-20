# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin autograd_gradient.py}

{xrst_template ,
   python/cmpad/gradient.xrst
   @Package@    , Autograd
   @#######@    , ########
   @package@    , autograd
   @algo_type@  , ``autograd.numpy.array`` with ``float`` elements
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
   def func(self, x) :
      y = self.algo(x)
      return y[-1]
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
      # self.grad
      self.grad = autograd.grad(self.func)
   #
   # call
   def __call__(self, x) :
      n_arg   = self.option['n_arg']
      assert len(x) == n_arg
      ax = autograd.numpy.array(x, dtype=float)
      g = self.grad( ax )
      return g
# END PYTHON
