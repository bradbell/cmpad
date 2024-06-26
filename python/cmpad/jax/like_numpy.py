# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
import jax
import jaxlib
#
class like_numpy :
   type_list =  [
      jaxlib.xla_extension.ArrayImpl     ,
      jax._src.interpreters.ad.JVPTracer ,
   ]
   #
   def __init__(self, like_vec) :
      if type(like_vec) in self.type_list :
         self.vec = like_vec
      else :
         self.vec = jax.numpy.array(like_vec, dtype=float)
      if len( self.vec.shape ) != 1 :
         self.vec = self.vec.reshape(-1)
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
      return like_numpy( jax.numpy.concatenate(vec_list) )
   #
   def reshape(self, shape) :
      assert shape == -1
      assert self.vec.shape == ( len(self.vec), )
      return like_numpy( self.vec )
