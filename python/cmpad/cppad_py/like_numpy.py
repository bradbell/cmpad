# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
import numpy
import cppad_py
#
class like_numpy :
   vector_type_list   =  [ numpy.ndarray ]
   #
   def __init__(self, like_vec) :
      if type(like_vec) in self.vector_type_list :
         self.vec = like_vec
      else :
         try :
            element_type = type( like_vec[0] )
         except :
            element_type = type( like_vec )
         if element_type == cppad_py.a_double :
            self.vec = numpy.array(like_vec, dtype=element_type).reshape(-1)
         else :
            self.vec = numpy.array(like_vec, dtype=float).reshape(-1)
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
      return self.vec.sum()
   #
   def __len__(self) :
      return len(self.vec)
   #
   def __getitem__(self, index) :
      return self.vec[index]
   #
   def concatenate(like_list) :
      vec_list = list()
      for like in like_list :
         vec_list.append(like.vec)
      return like_numpy( numpy.concatenate(vec_list) )
   #
   def reshape(self, shape) :
      assert shape == -1
      assert self.vec.shape == ( len(self.vec), )
      return like_numpy( self.vec )
