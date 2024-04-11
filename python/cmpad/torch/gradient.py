# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin torch_gradient.py}

{xrst_template ,
   python/cmpad/gradient.xrst
   @Package@    , PyTorch
   @#######@    , #######
   @package@    , torch
   @algo_type@  , ``torch.tensor`` with ``float`` elements
}

{xrst_end torch_gradient.py}
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
      # See https://discuss.torch.org/t/
      #     how-does-one-reuse-the-autograd-computational-graph/190447/2
      assert len(x) == self.n_arg
      ax = torch.tensor(x, requires_grad = True)
      az = self.algo(ax)
      az[-1].backward()
      return ax.grad
# END PYTHON
