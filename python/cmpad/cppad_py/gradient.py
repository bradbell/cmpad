# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin cppad_py_gradient}
{xrst_spell
   obj
}

Calculate Gradient Using cppad_py
#################################

Syntax
******
| |tab| *grad* ``cmpad.cppad_py.gradient`` ( *algo* )
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
have elements of type ``cppad_py.a_double`` . 

grad
****
This is a py_fun_obj where the input and output vectors
have elements of type ``float`` . 

g
*
This is a :ref:`py_fun_obj-name` object.

x
*
This is a numpy vector of ``float`` with length *option* [ ``'n_arg'`` ] .
It is the argument value at which to ocmpute the gradient.

g
*
This is a numpy vector of ``float`` with length *option* [ ``'n_arg'`` ] .
It is the value of the gradient ad *x* .

{xrst_toc_hidden
   python/xam/xam_grad_cppad_py.py
}
Example
*******
The file :ref:`xam_grad_cppad_py.py-name`
contains an example and test using this class.

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end cppad_py_gradient}
'''
# BEGIN PYTHON

class gradient :
   #
   def __init__(self, algo) :
      self.algo   = algo
      self.option = None
   #
   def option(self) :
      return self.optiion
   #
   def domain() :
      return self.option['n_arg']
   #
   def range() :
      return self.option['n_arg']
   #
   #
   def setup(self, option) :
      assert type(option) == dict
      assert 'n_arg' in option
      #
      # imports
      import numpy
      import cppad_py
      #
      # self.option
      self.option = option
      # 
      # self.algo
      self.algo.setup(option)
      #
      # self.n
      n = self.algo.domain()
      #
      # self.m
      m = self.algo.range()
      #
      # self.w
      self.w       = numpy.empty( (1, 1), dtype=float )
      self.w[0, 0] = 1.0
      #
      # self.tape
      x  = numpy.empty(n, dtype=float)
      ay = numpy.empty(1, dtype=cppad_py.a_double)
      for i in range(n) :
         x[i] = 0.
      ax    = cppad_py.independent(x)
      az    = self.algo(ax)
      ay[0] = az[m-1]
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
