# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin check_grad_llsq.py}

Python Check Gradient of Linear Least Squares Objective
#######################################################

Syntax
******
| |tab| *ok* = ``check_grad_llsq`` ( *grad_llsq* )

grad_llsq
*********
This is a ``float`` :ref:`py_fun_obj-title` .

option
******
The domain and range dimensions for the function object
are equal to *option* [ ``'n_arg'`` ];
see :ref:`py_fun_obj@option` .

ok
**
is true (false) if the gradient passes (fails) the test.

Source Code
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end check_grad_llsq.py}
'''
# BEGIN PYTHON
import numpy
import cmpad
import copy

def check_grad_llsq( grad_llsq ) :
   #
   # ok
   ok = True
   #
   # rel_error
   rel_error = 500. * numpy.finfo(float).eps
   #
   # n_arg
   n_arg = 4
   #
   # n_other
   n_other = 10
   #
   # t
   if n_other == 1 :
      t = numpy.array( [0.0] )
   else :
      t = numpy.linspace(-1.0, 1.0, n_other)
   #
   # q
   q = -1.0 * (t < 0) + 1.0 * (t > 0)
   #
   # time_setup
   for time_setup in [ False, True ] :
      #
      # option
      option = {
         'n_arg'      : n_arg           ,
         'n_other'    : n_other         ,
         'time_setup' : time_setup      ,
      }
      #
      # grad_llsq
      grad_llsq.setup(option)
      #
      # x
      x = numpy.random.uniform(-1.0, 1.0, n_arg)
      #
      # g
      g = grad_llsq(x)
      #
      # model
      model = 0.0
      ti   = numpy.ones(n_other)
      for i in range(n_arg) :
         model +=  x[i] * ti
         ti    *= t
      #
      # residual
      residual = model - q
      #
      # residual_dx
      residual_dx = numpy.empty( (n_arg, n_other) )
      ti          = numpy.ones(n_other)
      for i in range(n_arg) :
         residual_dx[i,:] =  residual * ti
         ti              *= t
      #
      # check
      check = residual_dx.sum(1)
      #
      # check
      for i in range(n_arg) :
         ok &= cmpad.near_equal( g[i], check[i], rel_error )
   return ok
# END PYTHON
