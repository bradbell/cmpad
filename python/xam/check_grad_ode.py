# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin check_grad_ode.py}

Python Check Gradient of an_ode
###############################

Syntax
******
| |tab| *ok* = ``check_grad_ode`` ( *grad_ode* )

grad_ode
********
This is a ``float`` :ref:`py_fun_obj-title` .

option
******
The domain and range dimensions for the function object
are equal to *option* [ ``'n_arg'`` ];
see :ref:`py_fun_obj@option` .

ok
**
is true (false) if the gradient passes (fails) the test.

Gradient
********
see the corresponding C++ :ref:`check_grad_ode.hpp@Gradient` .

Source Code
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end check_grad_ode.py}
'''
# BEGIN PYTHON
import numpy
import cmpad

def check_grad_ode( grad_ode ) :
   #
   # ok
   ok = True
   #
   # rel_error
   rel_error = 100. * numpy.finfo(float).eps
   #
   # n_arg
   n_arg = 4
   #
   # time_setup
   for time_setup in [ True, False ] :
      #
      # option
      option = {
         'n_arg'      : n_arg           ,
         'r_index'    : n_arg - 2       ,
         'time_setup' : time_setup      ,
      }
      #
      # grad_ode
      grad_ode.setup(option)
      #
      # x
      # note that x[i] != 0 so can divide by it
      x = numpy.random.uniform(0.0, 1.0, n_arg)
      x = x + 1.0
      #
      # g
      g = grad_ode(x)
      #
      # r
      r = option['r_index']
      #
      # y_r
      tf  = 2.0
      y_r = x[0] * tf
      for k in range(r) :
         j   = k + 1
         y_r = y_r * x[j] * tf / float(j+1)
      #
      # ok
      for j in range(r+1) :
         ok &= cmpad.near_equal( g[j], y_r / x[j], rel_error )
      for j in range(r+1, n_arg) :
         ok &= g[j] == 0.0
   return ok
# END PYTHON
