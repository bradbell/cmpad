# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
def det_of_minor(a, n, m, r, c) :
   assert  len(a) == n * n
   assert  len(r) == n + 1
   assert  len(c) == n + 1
   #
   # R0 = R(0)
   R0 = r[n]
   assert  R0 < n
   #
   # Cj = C(0)
   Cj = c[n]
   assert  Cj < n
   #
   # check if this is a 1 by 1 minor
   if  m == 1  :
      return a[ R0 * n + Cj ]
   #
   # detM
   # initialize determinant of the minor M
   detM = 0
   #
   # sign
   # initialize sign of factor for next sub-minor
   sign = 1
   #
   # r
   # remove row with index 0 in M from all the sub-minors of M
   r[n] = r[R0]
   #
   # C(j-1)
   # initial index in c for previous column of the minor M
   Cj1 = n
   #
   # for each column of M
   for j in range(m) :
      #
      # M[0,j] = A[ R0, Cj ]
      # element with index (0, j) in the minor M
      assert  Cj < n
      M0j = a[ R0 * n + Cj ]
      #
      # remove column with index j in M to form next sub-minor S of M
      c[Cj1] = c[Cj]
      #
      # detS
      # compute determinant of S, the sub-minor of M with
      # row R(0) and column C(j) removed.
      detS = det_of_minor(a, n, m - 1, r, c)
      #
      # restore column with index j in represenation of M as a minor of A
      c[Cj1] = Cj
      #
      # detM
      # include this sub-minor term in the summation
      if  sign > 0  :
         detM = detM + M0j * detS
      else :
         detM = detM - M0j * detS
      #
      # advance to next column of M
      Cj1  = Cj
      Cj   = c[Cj]
      sign = - sign
   #
   # r
   # restore row zero to the minor representation for M
   r[n] = R0
   #
   # return the determinant of the minor M
   return detM
