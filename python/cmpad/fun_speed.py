# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin py_fun_speed}
{xrst_spell
   obj
}

Determine Python Execution Speed
################################

Syntax
******
| |tab| *y* = *fun_obj* ( *x* )
| |tab| *rate* = ``cmpad::fun_speed`` ( *fun_obj*, *option*, *min_time* )

Prototype
*********
{xrst_literal ,
   # BEGIN PROTOTYPE, # END PROTOTYPE
   # BEGIN RETURN, # END RETURN
}

fun_obj
*******
We are testing the speed of the evaluation of this
:ref:`cpp_fun_obj-name` .

x
*
This is a vector like  object :ref:`cpp_fun_obj@x` for the function object.

y
*
This is the vector like object :ref:`cpp_fun_obj@y` for the function object.

option
******
This python dictionary is used to :ref:`cpp_fun_obj@setup` the function object.

time_setup
==========
If *option*\ ``['time_setup']`` is true (false)
the setup function is (is not)
included in the time for each function evaluation.
If the setup time is not included, the only thing that changes
between function evaluations is the argument vector *x* .

min_time
********
This is the minimum time in seconds for the timing of the computation.
The computation of the function object will be repeated enough times
so that this minimum time is reached.

rate
****
This is the speed of one computation of the function object; i.e.,
the number of times per second that the function object gets computed.

{xrst_toc_hidden
   python/xam/fun_speed.py
}
Example
*******
:ref:`xam_fun_speed.py-name` is an example and test that uses this function.

{xrst_end py_fun_speed}
-------------------------------------------------------------------------------
'''
import timeit
import numpy
#
# BEGIN PROTOTYPE
def fun_speed(fun_obj, option, min_time) :
   assert type(option) == dict
   assert type(option['time_setup'] ) == bool
   assert type(min_time) == float
   # END PROTOTYPE
   #
   # rng
   rng = numpy.random.default_rng()
   #
   # fun_obj.setup
   fun_obj.setup(option)
   #
   # n
   n = fun_obj.domain()
   #
   # repeat, t_start, t_end, t_diff
   repeat  = 0
   t_start = timeit.default_timer()
   t_end   = timeit.default_timer()
   t_diff  = t_end - t_start
   #
   # while t_diff < min_time
   while t_diff < min_time  :
      #
      # repeat
      if  repeat == 0  :
         repeat = 1
      else :
         if  2 * repeat <= repeat  :
            msg = "cmpad.fun_speed: 2 * repeat <= repeat"
            sys.exit(msg)
         repeat = 2 * repeat
      #
      # t_start
      t_start = timeit.default_timer()
      #
      # computation
      for i in range(repeat) :
         x = rng.random(n)
         if  option['time_setup']  :
            fun_obj.setup(option)
         fun_obj(x)
      #
      # t_diff
      t_end   = timeit.default_timer()
      t_diff  = t_end - t_start
   rate = repeat / t_diff
   # BEGIN RETURN
   assert type(rate) == float
   return rate
   # END RETURN
