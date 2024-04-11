# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin py_llsq_obj}
{xrst_spell
   linspace
   num
   vec
   int
}

Python Linear Least Squares Objective
#####################################

Syntax
******
| |tab| *llsq* = ``cmpad.llsq_obj`` ( *like_numpy* )
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
It is vectorized using arrays that act like numpy arrays.
Different array types are used by the different AD packages.

like_numpy
**********
The llsq_obj algorithm is vectorized using this type which must support
the following operations (similar to how numpy supports them):

Syntax
======

| |tab| *vec*  = *like_numpy* . ``array`` ( *list* )
| |tab| *ones* = *like_numpy* . ``ones`` ( *n* )
| |tab| *linspace* = *like_numpy* . ``linspace`` ( *start* , *stop* , *num* )
| |tab| *square* = *like_numpy* . ``square`` ( *vec* )
| |tab| *sum* = *like_numpy* . ``sum`` ( *vec* )

#. The argument *list* is a list with ``float`` elements.
#. The arguments *n* and *num* are positive ``int`` .
#. The arguments *start* and *stop* are ``float`` .
#. The argument *vec* is a 1-d numpy like array.
#. The results *vec* , *ones* , *linspace*  and *square*
   are numpy like 1-d arrays.
#. if *like_numpy* is ``cmpad.torch.like_numpy`` , *sum* . ``flatten()``
   is a 1-d numpy like array with one element.
   Otherwise *like_numpy* . ``array`` ( [ *sum* ] )
   is a 1-d numpy like array with one element.
#. All the result vectors have the same precision as ``float`` .

Example
=======
{xrst_literal
   python/cmpad/torch/like_numpy.py
   # BEGIN LIKE_NUMPY
   # END LIKE_NUMPY
}

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


{xrst_end py_llsq_obj}
'''
# BEGIN PYTHON
import cmpad
#
# BEGIN PROTOTYPE
class llsq_obj :
   def __init__(self, like_numpy) :
      self.like_numpy = like_numpy
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
         t = self.like_numpy.array( [0.0 ] )
      else :
         t = self.like_numpy.linspace(-1.0, 1.0, n_other)
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
      ti  = self.like_numpy.ones( len(self.t) )
      for i in range(self.n_arg) :
         model = model + ax[i] * ti
         ti    = ti * self.t
      #
      # squared_residual
      squared_residual = self.like_numpy.square(model - self.q)
      #
      # objective
      objective = 0.5 * self.like_numpy.sum(squared_residual)
      #
      done = False
      if cmpad.has_package['torch'] :
         if self.like_numpy == cmpad.torch.like_numpy :
            objective = objective.flatten()
            done = True
      if not done :
         objective = self.like_numpy.array( [ objective ] )
      return objective
# END PYTHON
