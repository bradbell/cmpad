// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# include <boost/test/unit_test.hpp>
# include <cmpad/fun_speed.hpp>
# include <cmpad/csv_speed.hpp>
# include <cmpad/algo/det_by_minor.hpp>
# include "check_speed_det.hpp"
# include "csv_fixture.hpp"

BOOST_AUTO_TEST_SUITE(fun_speed)
BOOST_AUTO_TEST_CASE(Double)
{  cmpad::det_by_minor<double> det;
   check_speed_det(det);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(csv_speed, csv_fixture)
BOOST_AUTO_TEST_CASE(Double)
{  //
   // package_, csv_fiel_path_
   set_package("double");
   //
   // file_name
   std::string file_name = csv_file_path_;
   //
   // time_setup
   for(bool time_setup : {true, false} )
   {
      // option
      cmpad::option_t option;
      option.size       = size_;
      option.time_setup = time_setup;
      //
      // det
      BOOST_REQUIRE( algorithm_ == "det_by_minor" );
      cmpad::det_by_minor<double> det;
      //
      // rate
      double rate = cmpad::fun_speed(det, option, min_time_);
      //
      // csv_speed
      cmpad::csv_speed(file_name, rate, "double", algorithm_, option);
   }
   check();
}
BOOST_AUTO_TEST_SUITE_END()
