# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin check_grad_ode.py}

PYthon Check Gradient of an_ode
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
      # i
      # component of y that gradient corresponds to
      i = n_arg - 1
      #
      # yi
      tf = 2.0
      yi = x[0] * tf
      for k in range(n_arg - 1) :
         j  = k + 1
         yi = x[j] * yi * tf / float(j+1)
      #
      # ok
      for j in range(n_arg) :
         ok &= cmpad.near_equal( g[j], yi / x[j], rel_error )
   return ok
# END PYTHON
