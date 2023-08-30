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
   // package
   std::string package = "double";
   //
   // package_, algorithm_, n_arg_, csv_file_path_
   std::string algorithm = "det_by_minor";
   size_t      n_arg     = 16;
   set_fixture(package, algorithm, n_arg);
   //
   // time_setup
   for(bool time_setup : {true, false} )
   {
      // option
      cmpad::option_t option;
      option.n_arg       = n_arg_;
      option.time_setup = time_setup;
      //
      // csv_file_path
      cmpad::det_by_minor<double> det;
      double rate = cmpad::fun_speed(det, option, min_time_);
      cmpad::csv_speed(
         csv_file_path_, rate, min_time_, package, algorithm_, option
      );
   }
   check();
}
BOOST_AUTO_TEST_SUITE_END()
