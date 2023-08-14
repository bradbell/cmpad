// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
// BEGIN C++
# include <ctime>
# include <boost/test/unit_test.hpp>

// xam library
bool xam_csv_read(void);
bool xam_uniform_01(void);

BOOST_AUTO_TEST_SUITE( example ) // begin example

BOOST_AUTO_TEST_CASE(csv_read)
{  BOOST_CHECK( xam_csv_read() == true ); }


BOOST_AUTO_TEST_CASE(uniform_01)
{  BOOST_CHECK( xam_uniform_01() == true ); }


BOOST_AUTO_TEST_SUITE_END() // end example
