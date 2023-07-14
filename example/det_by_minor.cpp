// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2003-22 Bradley M. Bell
// ----------------------------------------------------------------------------

/*
{xrst_begin det_by_minor.cpp}

det_by_minor: Example and Test
##############################

{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end det_by_minor.cpp}
*/
// BEGIN C++
# include <boost/test/unit_test.hpp>
# include <cppad/utility/vector.hpp>
# include <cmpad/det_by_minor.hpp>

# define BOOST_TEST_DYN_LINK
# define BOOST_TEST_MODULE example

BOOST_AUTO_TEST_CASE(det_by_minor)
{
   // m
   // dimension of the matrix
   size_t m = 3;
   //
   // det
   cmpad::det_by_minor<double> det;
   det.setup(m);
   //
   // a
   CppAD::vector<double>  a = {
      1., 2., 3.,  // a[0] a[1] a[2]
      3., 2., 1.,  // a[3] a[4] a[5]
      2., 1., 2.   // a[6] a[7] a[8]
   };
   //
   // d
   double d = det.fun(a);
   //
   // check
   double check;
   check = a[0]*(a[4]*a[8] - a[5]*a[7])
         - a[1]*(a[3]*a[8] - a[5]*a[6])
         + a[2]*(a[3]*a[7] - a[4]*a[6]);
   BOOST_CHECK(d == check);
}

// END C++
