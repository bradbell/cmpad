# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin xam_fun_speed.py}

Example and Test of Python fun_speed
####################################
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end xam_fun_speed.py}
'''
# BEGIN PYTHON
import cmpad
#
# my_fun_obj
class my_fun_obj :
   #
   # domain
   def domain(self) :
      return self.n_arg
   #
   # range
   def range(self) :
      return 1
   #
   # setup
   def setup(self, option) :
      self.n_arg      = option['n_arg']
   #
   # __call__
   def __call__(self, x ) :
      assert len(x) == self.n_arg
      sum_xi = 0.0
      for xi in x :
         sum_xi += xi
      return [ sum_xi ]

#
# xam_fun_speed
def xam_fun_speed() :
   #
   # ok
   ok = True
   #
   # min_time
   min_time = 0.1
   #
   # my_fun
   my_fun = my_fun_obj()
   #
   # option_one
   option_one = { 'n_arg' : 10000, 'time_setup' : False }
   #
   # rate_one
   rate_one = cmpad.fun_speed(my_fun, option_one, min_time)
   #
   # option_two
   option_two = dict()
   option_two['n_arg']      = 2 * option_one['n_arg']
   option_two['time_setup'] = option_one['time_setup']
   #
   # rate_two
   rate_two = cmpad.fun_speed(my_fun, option_two, min_time)
   #
   # ok
   ratio = rate_one / rate_two
   ok   &= 1.7 < ratio and ratio < 2.3
   #
   return ok
#
# test_fun_speed
def test_fun_speed() :
   assert xam_fun_speed() == True
# END PYTHON
