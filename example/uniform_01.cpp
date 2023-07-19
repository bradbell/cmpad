// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin uniform_01.cpp}

uniform_01: Example and Test
############################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end  uniform_01.cpp}
*/
// BEGIN C++
# include <ctime>
# include <boost/test/unit_test.hpp>
# include <cmpad/uniform_01.hpp>

BOOST_AUTO_TEST_CASE(uniform_01)
{  //
   // seed
   unsigned int seed = static_cast<unsigned int>( std::time(nullptr) );
   //
   // srand
   std::srand(seed);
   //
   // x
   size_t n = 10;
   cmpad::vector<double> x(n);
   for(size_t i = 0; i < n; ++i)
      x[i] = -1;
   //
   // x
   cmpad::uniform_01(x);
   for(size_t i = 0; i < n; ++i)
      BOOST_CHECK( 0.0 <= x[i] && x[i] <= 1.0 );
}
// END C++
