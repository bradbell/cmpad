# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------

import timeit
import numpy
#
def fun_speed(fun_obj, option, min_time) :
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
   return rate
