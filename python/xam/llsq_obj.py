# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin xam_llsq_obj.py}

Python Example and Test of llsq_obj
###################################

{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end xam_llsq_obj.py}
'''
# BEGIN PYTHON
import cmpad
import numpy
#
# xam_llsq_obj
def xam_llsq_obj() :
   #
   # ok
   ok = True
   #
   # like_numpy
   like_numpy = numpy
   #
   # llsq
   llsq = cmpad.llsq_obj(like_numpy)
   #
   # llsq.setup
   option = { 'n_arg' : 3, 'n_other' : 4 }
   llsq.setup(option)
   #
   # x
   x = [ 1., 2., 3. ]
   #
   # y
   y = llsq(x)
   #
   # sumsq
   sumsq = 0.0;
   #
   for j in range( option['n_other'] ) :
      #
      # t_j
      t_j = -1.0 + 2.0 * j / (option['n_other'] - 1)
      #
      # q_j
      if t_j < 0.0 :
         q_j = -1.0
      elif t_j == 0.0 :
         q_j = 0.0
      else :
         q_j = 1.0
      #
      # r_j
      m_j = x[0] + x[1] * t_j + x[2] * t_j * t_j
      r_j = m_j - q_j
      #
      # sumsq
      sumsq += r_j * r_j
   #
   # check
   check = 0.5 * sumsq
   #
   # rel_error
   rel_error = numpy.finfo(float).eps * 100.0
   #
   # ok
   ok &= cmpad.near_equal( y[0], check, rel_error )
   #
   return ok
#
# test_llsq_obj
def test_llsq_obj() :
   assert xam_llsq_obj() == True
xam_llsq_obj()
# END PYTHON
