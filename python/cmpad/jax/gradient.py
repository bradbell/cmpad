# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin jax_gradient.py}
{xrst_spell
   numpy
}

{xrst_template ,
   python/cmpad/gradient.xrst
   @Package@    , JAX
   @#######@    , ###
   @package@    , jax
   @algo_type@  , ``jax.numpy.array`` with ``float`` elements
}

{xrst_end jax_gradient.py}
'''
# BEGIN PYTHON
#
# imports
import numpy
import jax
jax.config.update('jax_enable_x64', True)
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
   def func(self, x) :
      v = self.algo(x)
      return v[-1]
   #
   # call
   def __call__(self, x) :
      grad = jax.grad(self.func)
      x    = jax.numpy.array(x, dtype=float)
      z    = grad(x)
      return z
# END PYTHON
