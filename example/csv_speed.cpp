// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin csv_speed.cpp}

csv_speed: Example and Test
###########################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end  csv_speed.cpp}
*/
// BEGIN C++
# include <filesystem>
# include <boost/test/unit_test.hpp>
# include <cmpad/det_by_minor.hpp>
# include <cmpad/adolc/gradient.hpp>
# include <cmpad/cppad/gradient.hpp>
# include <cmpad/fun_speed.hpp>
# include <cmpad/csv_speed.hpp>
# include <cmpad/csv_read.hpp>

BOOST_AUTO_TEST_CASE(csv_speed)
{  //
   // filesystem
   namespace filesystem =  std::filesystem;
   //
   // time_min
   double time_min = 0.2;
   //
   // file_name
   std::string file_name = "csv_speed.csv";
   filesystem::path path(file_name);
   if( filesystem::exists( filesystem::path(file_name)  ) )
      std::remove( file_name.c_str() );
   //
   // option
   cmpad::str2str_map option;
   option["size"] = "6";
   //
   // rate
   double rate;
   //
   // double
   cmpad::det_by_minor<double>        det_double;
   det_double.setup(option);
   rate = cmpad::fun_speed(det_double, time_min);
   cmpad::csv_speed(file_name, "double", "det_by_minor", rate);
   //
   // adolc
   typedef cmpad::det_by_minor<adouble>       det_adolc;
   cmpad::adolc::gradient<det_adolc>          grad_det_adolc;
   grad_det_adolc.setup(option);
   rate = cmpad::fun_speed(grad_det_adolc, time_min);
   cmpad::csv_speed(file_name, "adolc", "det_by_minor", rate);
   //
   // cppad
   typedef cmpad::det_by_minor< CppAD::AD<double> > det_cppad;
   cmpad::cppad::gradient<det_cppad>                grad_det_cppad;
   grad_det_cppad.setup(option);
   rate = cmpad::fun_speed(grad_det_cppad, time_min);
   cmpad::csv_speed(file_name, "cppad", "det_by_minor", rate);
   //
   // csv_table
   cmpad::vec_vec_str csv_table = cmpad::csv_read(file_name);
   //
   // csv_table: check
   BOOST_CHECK( csv_table.size() == 4 );
   for(size_t i = 0; i < csv_table.size(); ++i)
      BOOST_CHECK( csv_table[i].size() == 4 );
   //
   BOOST_CHECK( csv_table[0][0] == "date" );
   BOOST_CHECK( csv_table[0][1] == "package" );
   BOOST_CHECK( csv_table[0][2] == "algorithm" );
   BOOST_CHECK( csv_table[0][3] == "rate" );
   //
   BOOST_CHECK( csv_table[1][1] == "double" );
   BOOST_CHECK( csv_table[2][1] == "adolc" );
   BOOST_CHECK( csv_table[3][1] == "cppad" );
   //
   BOOST_CHECK( csv_table[1][2] == "det_by_minor" );
   BOOST_CHECK( csv_table[2][2] == "det_by_minor" );
   BOOST_CHECK( csv_table[3][2] == "det_by_minor" );
}
// END C++
