// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ----------------------------------------------------------------------------

/*
{xrst_begin xam_det_by_minor.cpp}

Example and Test of det_by_minor
################################

{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end xam_det_by_minor.cpp}
*/
// BEGIN C++
# include <cmpad/algo/det_by_minor.hpp>

bool xam_det_by_minor(void)
{  // ok
   bool ok = true;
   //
   // ell
   // dimension of the matrix
   size_t ell = 3;
   //
   // det
   cmpad::det_by_minor<double> det;
   //
   // det.setup
   cmpad::option_t option;
   option.n_arg   = ell * ell;
   option.g_index = 0;
   det.setup(option);
   //
   // x
   cmpad::vector<double>  x = {
      1., 2., 3.,  // x[0] x[1] x[2]
      3., 2., 1.,  // x[3] x[4] x[5]
      2., 1., 2.   // x[6] x[7] x[8]
   };
   ok &= x.size() == ell * ell;
   //
   // y
   const cmpad::vector<double>& y = det(x);
   ok &= y.size() == 1;
   //
   // check
   double check =
      + x[0]*(x[4]*x[8] - x[5]*x[7])
      - x[1]*(x[3]*x[8] - x[5]*x[6])
      + x[2]*(x[3]*x[7] - x[4]*x[6]);
   //
   // ok
   ok &= y[0] == check;
   //
   return ok;
}

// END C++
