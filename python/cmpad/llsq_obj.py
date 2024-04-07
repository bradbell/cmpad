# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin py_llsq_obj}

Python Linear Least Squares Objective
#####################################

Syntax
******
| |tab| *llsq* = ``cmpad.llsq_obj()``
| |tab| *llsq* . ``setup`` ( *option* )
| |tab| *obj* = *llsq* ( *x* )

Prototype
*********
{xrst_literal
   # BEGIN PROTOTYPE
   # END PROTOTYPE
}

Algorithm
*********
This is a python implementation of the :ref:`llsq_obj-name` algorithm .

n_arg
*****
see :ref:`llsq_obj@option@n_arg` .

n_other
*******
see :ref:`llsq_obj@option@n_other` .

Vector Operations
*****************
This algorithm cannot be vectorized using numpy
because pytorch would not be able to use it to compute derivatives.
The autograd and cppad_py packages can compute derivatives using
a numpy vectorized version of this algorithm

Source Code
***********
The code below is the implementation of this function:
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end py_llsq_obj}
'''
# BEGIN PYTHON
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
      # t, q
      if n_other == 1 :
         t = [ 0.0 ]
         q = [ 0.0 ]
      else :
         t = list()
         q = list()
         for j in range(n_other) :
            #
            t_j = -1.0 + 2.0 * j / (n_other - 1)
            if t_j == 0.0 :
               q_j = 0.0
            elif t_j < 0.0 :
               q_j = -1.0
            else :
               q_j = +1.0
            #
            t.append(t_j)
            q.append(q_j)
      #
      # self
      self.n_arg   = n_arg
      self.n_other = n_other
      self.t       = t
      self.q       = q
   #
   def __call__(self, x) :
      assert len(x) == self.n_arg
      #
      #  n_arg, n_other
      n_arg   = self.n_arg
      n_other = self.n_other
      #
      # sumsq
      sumsq = 0.0
      for j in range(n_other) :
         #
         # model
         model = 0.0
         ti_j  = 1.0
         for i in range(n_arg) :
            model += x[i] * ti_j
            ti_j  *= self.t[j]
         #
         # sumsq
         residual = model - self.q[j]
         sumsq   += residual * residual
      #
      # objective
      objective = 0.5 * sumsq
      #
      return [ objective ]
# END PYTHON
