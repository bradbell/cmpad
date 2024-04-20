# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin cppad_py_gradient.py}
{xrst_template ,
   python/cmpad/gradient.xrst
   @Package@    , cppad_py
   @#######@    , ########
   @package@    , cppad_py
   @algo_type@  , ``numpy.array`` with ``cppad_py.a_double`` elements
}

{xrst_end cppad_py_gradient.py}
'''
# BEGIN PYTHON
#
# imports
import numpy
import cppad_py
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
      # n
      n = self.algo.domain()
      #
      # self.w
      self.w       = numpy.empty( (1, 1), dtype=float )
      self.w[0, 0] = 1.0
      #
      # self.tape
      x     = numpy.zeros(n, dtype=float)
      ay    = numpy.empty(1, dtype=cppad_py.a_double)
      ax    = cppad_py.independent(x)
      az    = self.algo(ax)
      ay[0] = az[-1]
      self.tape = cppad_py.d_fun(ax, ay)
      if not option['time_setup'] :
         self.tape.optimize()
   #
   # call
   def __call__(self, x) :
      self.tape.forward(0, x)
      g = self.tape.reverse(1, self.w)
      return g
# END PYTHON
