// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
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
# include <cmpad/det_by_minor.hpp>

# define BOOST_TEST_DYN_LINK
# define BOOST_TEST_MODULE example

BOOST_AUTO_TEST_CASE(det_by_minor)
{
   // size
   // dimension of the matrix
   size_t ell = 3;
   //
   // det
   cmpad::det_by_minor<double> det;
   //
   // det.setup
   cmpad::option_t option;
   option.size = ell;
   det.setup(option);
   //
   // x
   cmpad::vector<double>  x = {
      1., 2., 3.,  // x[0] x[1] x[2]
      3., 2., 1.,  // x[3] x[4] x[5]
      2., 1., 2.   // x[6] x[7] x[8]
   };
   BOOST_REQUIRE( x.size() == ell * ell );
   //
   // y
   const cmpad::vector<double>& y = det(x);
   BOOST_CHECK( y.size() == 1 );
   //
   // check
   double check;
   check = x[0]*(x[4]*x[8] - x[5]*x[7])
         - x[1]*(x[3]*x[8] - x[5]*x[6])
         + x[2]*(x[3]*x[7] - x[4]*x[6]);
   BOOST_CHECK(y[0] == check);
}

// END C++
