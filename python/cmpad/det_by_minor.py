# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------

import math
import cmpad

class det_by_minor :
   #
   # option
   def option(self) :
      return option_
   #
   # domain
   def domain(self) :
      return option_['n_arg']
   #
   # range
   def range(self) :
      return 1
   #
   # setup
   def setup(self, option) :
      assert type(option) == dict
      #
      # option_
      self.option_ = option
      #
      # ell
      ell = int( math.sqrt( option['n_arg'] ) )
      if( ell * ell < option['n_arg'] ) :
         ell += 1
      assert ell * ell == option['n_arg']
      #
      # ell_
      self.ell_ = ell
      #
      # r_, c_
      self.r_ = (ell + 1) * [0]
      self.c_ = (ell + 1) * [0]
      for i in range(ell) :
         self.r_[i] = i + 1
         self.c_[i] = i + 1
      self.r_[ell] = 0
      self.c_[ell] = 0
   #
   # call
   def __call__(self, x) :
      #
      # d
      d = cmpad.det_of_minor(x, self.ell_, self.ell_, self.r_, self.c_)
      #
      return [ d ]



