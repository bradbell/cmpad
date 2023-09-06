// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ----------------------------------------------------------------------------

/*
{xrst_begin xam_det_of_minor.cpp}

Example and Test of det_of_minor
################################

{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end xam_det_of_minor.cpp}
*/
// BEGIN C++
# include <cstddef>
# include <cmpad/algo/det_of_minor.hpp>

bool xam_det_of_minor(void)
{  //
   // ok
   bool ok = true;
   //
   // a
   // values in the matrix A in row major order
   cmpad::vector<double> a = {
      1., 2., 3.,
      4., 5., 6.,
      7., 8., 10.
   };
   //
   // m
   // dimension of the matrix A
   size_t n = 3;
   ok &= n * n ==  a.size();
   //
   // r, c
   // index vectors set so minor is the entire matrix A
   cmpad::vector<size_t> r(n + 1);
   cmpad::vector<size_t> c(n + 1);
   for(size_t i= 0; i < n; i++)
   {  r[i] = i+1;
      c[i] = i+1;
   }
   r[n] = 0;
   c[n] = 0;
   //
   // n
   // size of minor that is the entire matrix A
   size_t m = n;
   //
   // det
   // evaluate the determinant of A
   double det = cmpad::det_of_minor(a, n, m, r, c);
   //
   // ok
   // check the value of the determinant of A
   ok &= det == (double) (1*(5*10-6*8) - 2*(4*10-6*7) + 3*(4*8-5*7));
   //
   // M
   // minor where row 0 and column 1 are removed
   r[m] = 1;     // skip row index 0 by starting at row index 1
   c[0] = 2;     // skip column index 1 by pointing from index 0 to index 2
   m    = n - 1; // dimension of the minor M
   //
   // det
   // evaluate determinant of the minor
   det = cmpad::det_of_minor(a, n, m, r, c);
   //
   // ok
   // check the value of the determinant of the minor
   ok &= det ==  (double) (4*10-6*7);
   //
   return ok;
}
// END C++
