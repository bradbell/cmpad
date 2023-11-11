# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin pytorch_llsq_obj}

Least Squares Linear Regression Objective
#########################################

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

{xrst_end pytorch_llsq_obj}
'''
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
      # s
      s = -1.0 * (t < 0) + 1.0 * (t > 0)
      #
      # self
      self.n_arg = n_arg
      self.t     = torch.tensor(t)
      self.s     = torch.tensor(s)
   #
   def __call__(self, ax) :
      assert len(ax) == self.n_arg
      #
      # as_
      as_ = 0.0
      ti  = torch.tensor( len(self.t) * [1.0] )
      for j in range(self.n_arg) :
         as_ = as_ + ax[j] * ti
         ti  = ti * self.t
      #
      # ay
      ay = 0.5 * torch.square(self.s - as_).sum()
      ay = ay.view(1)
      #
      return ay
