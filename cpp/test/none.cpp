// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# include <boost/test/unit_test.hpp>
# include <cmpad/fun_speed.hpp>
# include <cmpad/csv_speed.hpp>
# include <cmpad/algo/det_by_minor.hpp>
# include <cmpad/algo/an_ode.hpp>
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
   std::string package = "none";
   //
   // algorithm, n_arg, n_other
   std::string algorithm;
   size_t      n_arg;
   size_t      n_other;
   //
   // ------------------------------------------------------------------------
   // package_, algorithm_, n_arg_, n_other_, csv_file_path_
   algorithm = "det_by_minor";
   n_arg     = 16;
   n_other   = 0;
   set_fixture(package, algorithm, n_arg, n_other);
   //
   // time_setup
   for(bool time_setup : {true, false} )
   {
      // option
      cmpad::option_t option;
      option.n_arg       = n_arg_;
      option.n_other     = n_other_;
      option.time_setup = time_setup;
      //
      // csv_file_path
      cmpad::det_by_minor<double> det;
      double rate    = cmpad::fun_speed(det, option, min_time_);
      bool   special = false;
      cmpad::csv_speed(
         csv_file_path_, rate, min_time_, package, algorithm_, special, option
      );
   }
   check();
   // ------------------------------------------------------------------------
   // package_, algorithm_, n_arg_, n_other_, csv_file_path_
   algorithm = "an_ode";
   n_arg     = 5;
   n_other   = n_arg - 1;
   set_fixture(package, algorithm, n_other, n_arg);
   //
   // time_setup
   for(bool time_setup : {true, false} )
   {
      // option
      cmpad::option_t option;
      option.n_arg       = n_arg_;
      option.n_other     = n_other_;
      option.time_setup = time_setup;
      //
      // csv_file_path
      cmpad::an_ode<double> ode;
      double rate    = cmpad::fun_speed(ode, option, min_time_);
      bool   special = false;
      cmpad::csv_speed(
         csv_file_path_, rate, min_time_, package, algorithm_, special, option
      );
   }
   check();
}
BOOST_AUTO_TEST_SUITE_END()
