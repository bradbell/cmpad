# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin py_llsq_obj}

Python Least Squares Linear Regression Objective
################################################

Function
********

.. math:

   y(x) = \frac{1}{2} \sum_i^n \left(
      s_i - x_0 - x_1 t_i - x_2 t_i^2 - \cdots
   \right)^2

where *s* and *t* in :math:`{\bf R}^n` are given by:

.. math:

   t_j & = -1 + i * 2 / (n - 1)
   \\
   s_j & = \sign ( t_j )
.. math:

   \frac{ \partial y} { \partial x(i) } = \sum_j^n \left(
      s_j - x_0 - x_1 t_j - x_2 t_j^2 - \cdots
   \right) t_j^{i-1}

Packages
********
The pages below contain the implementation of this function
that is used when :ref:`run_cmpad@package` is not ``none`` .
{xrst_toc_table
   python/cmpad/pytorch/llsq_obj.py
}

Source Code
***********
The code below is the implementation of this function
that is used when :ref:`run_cmpad@package` is ``none`` .
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}


{xrst_end py_llsq_obj}
'''
# BEGIN PYTHON
import numpy
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
      self.t     = t
      self.q     = q
   #
   def __call__(self, ax) :
      assert len(ax) == self.n_arg
      #
      # model
      model = 0.0
      ti  = numpy.ones( len(self.t) )
      for i in range(self.n_arg) :
         model = model + ax[i] * ti
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
