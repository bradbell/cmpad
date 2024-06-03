// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# include <boost/test/unit_test.hpp>
# include <cmpad/fun_speed.hpp>
# include <cmpad/csv_speed.hpp>
# include <cmpad/vector.hpp>
# include "check_speed_det.hpp"
# include "csv_fixture.hpp"
//
# include <cmpad/algo/det_by_minor_vec.hpp>
# include <cmpad/algo/an_ode_vec.hpp>
# include <cmpad/algo/llsq_obj_vec.hpp>
//
// CMPAD_TEST_ONE_ALGORITHM
# define CMPAD_TEST_ONE_ALGORITHM(algorithm_value, n_arg_value, n_other_value) \
   /* \
   package_, algorithm_, n_arg_, n_other_ */ \
   set_fixture("none", #algorithm_value, n_arg_value, n_other_value); \
   /* \
   time_setup */ \
   for(bool time_setup : {true, false} ) \
   { \
      /* \
      option */ \
      cmpad::option_t option; \
      option.n_arg       = n_arg_; \
      option.n_other     = n_other_; \
      option.time_setup = time_setup; \
      /* \
      csv_file_path_ */ \
      cmpad::algorithm_value ##_vec< cmpad::vector<double> > fun; \
      double rate    = cmpad::fun_speed(fun, option, min_time_); \
      bool   special = false; \
      cmpad::csv_speed( csv_file_path_,  \
         rate, min_time_, package_, algorithm_, special, option \
      ); \
   } \
   check();

BOOST_AUTO_TEST_SUITE(fun_speed)
BOOST_AUTO_TEST_CASE(Double)
{  cmpad::det_by_minor_vec< cmpad::vector<double> > det;
   check_speed_det(det);
}
BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE(csv_speed, csv_fixture)
BOOST_AUTO_TEST_CASE(Double)
{  //
   CMPAD_TEST_ONE_ALGORITHM(det_by_minor, 16, 0)
   CMPAD_TEST_ONE_ALGORITHM(an_ode, 5, 4)
   CMPAD_TEST_ONE_ALGORITHM(llsq_obj, 3, 10)
}
BOOST_AUTO_TEST_SUITE_END()
