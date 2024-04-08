# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
# BEGIN LIKE_NUMPY
import torch
#
class like_numpy :
   def array(vec) :
      torch.tensor(vec, dtype=float)
   #
   def ones(n) :
      return torch.ones(n, dtype=float)
   #
   def linspace(start, stop, num) :
      return torch.linspace(start, stop, num, dtype=float)
   #
   def square(vec) :
      return torch.square(vec)
   #
   def sum(vec) :
      return vec.sum()
# END LIKE_NUMPY
