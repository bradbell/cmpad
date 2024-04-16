# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
import numpy
import cppad_py
#
class like_numpy :
   type_list =  [ numpy.ndarray ]
   #
   def __init__(self, like_vec) :
      if type(like_vec) in self.type_list :
         self.vec = like_vec
      elif type(like_vec) == cppad_py.a_double :
         self.vec = numpy.array(like_vec, dtype=cppad_py.a_double)
      else :
         assert len(like_vec) != 0
         if type(like_vec) != list :
            breakpoint()
         self.vec = numpy.array(like_vec, dtype=float)
   #
   def __add__(self, other) :
      return like_numpy( self.vec + other.vec )
   #
   def __sub__(self, other) :
      return like_numpy( self.vec - other.vec )
   #
   def __mul__(self, other) :
      return like_numpy( self.vec * other.vec )
   #
   def __truediv__(self, other) :
      return like_numpy( self.vec / other.vec )
   #
   def array(vec) :
      return like_numpy(vec)
   #
   def sum(self) :
      return numpy.array( self.vec.sum() ).reshape(1)
   #
