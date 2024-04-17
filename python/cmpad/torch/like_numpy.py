# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
# BEGIN LIKE_NUMPY
import torch
#
class like_numpy :
   type_list = [ torch.Tensor ]
   #
   def __init__(self, like_vec) :
      if type(like_vec) in self.type_list :
         self.vec = like_vec.reshape(-1)
      else :
         self.vec = torch.tensor(like_vec, dtype=float).reshape(-1)
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
      return like_numpy( torch.cat(vec_list) )
   #
   def concatenate(like_list) :
      vec_list = list()
      for like in like_list :
         vec_list.append(like.vec)
      return like_numpy( torch.cat(vec_list) )
   #
   def reshape(self, shape) :
      assert shape == -1
      assert self.vec.shape == ( len(self.vec), )
      return like_numpy( self.vec )
# END LIKE_NUMPY
