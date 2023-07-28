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
# include <cmpad/sacado/gradient.hpp>
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
   // package
   std::string package;
   //
   // algorithm
   std::string algorithm = "det_by_minor";
   //
   // option
   cmpad::option_t option;
   option.size = 6;
   //
   // rate
   double rate;
   //
   // det_by_minor
   using cmpad::det_by_minor;
   //
   // double
   package   = "double";
   cmpad::det_by_minor<double>        det_double;
   det_double.setup(option);
   rate = cmpad::fun_speed(det_double, time_min);
   cmpad::csv_speed(file_name, rate, package, algorithm, option);
   //
   // adolc
   package   = "adolc";
   cmpad::adolc::gradient<det_by_minor>          grad_det_adolc;
   grad_det_adolc.setup(option);
   rate = cmpad::fun_speed(grad_det_adolc, time_min);
   cmpad::csv_speed(file_name, rate, package, algorithm, option);
   //
   // cppad
   package   = "cppad";
   cmpad::cppad::gradient<det_by_minor>           grad_det_cppad;
   grad_det_cppad.setup(option);
   rate = cmpad::fun_speed(grad_det_cppad, time_min);
   cmpad::csv_speed(file_name, rate, package, algorithm, option);
   //
   // sacado
   package   = "sacado";
   cmpad::sacado::gradient<det_by_minor>          grad_det_sacado;
   grad_det_sacado.setup(option);
   rate = cmpad::fun_speed(grad_det_sacado, time_min);
   cmpad::csv_speed(file_name, rate, package, algorithm, option);
   //
   // csv_table
   cmpad::vec_vec_str csv_table = cmpad::csv_read(file_name);
   //
   // debug
# ifndef NDEBUG
   std::string debug = "true";
# else
   std::string debug = "false";
# endif
   //
   // col_name, n_col
   const char* col_name[] = {
      "rate", "package", "algorithm", "size", "date", "compiler", "debug"
   };
   size_t n_col = sizeof(col_name) / sizeof( col_name[0] );
   //
   // csv_table: check
   BOOST_CHECK( csv_table.size() == 5 );
   for(size_t i = 0; i < csv_table.size(); ++i)
      BOOST_CHECK( csv_table[i].size() == n_col );
   //
   for(size_t j = 0; j < n_col; ++j)
      BOOST_CHECK( csv_table[0][j] == col_name[j] );
   //
   BOOST_CHECK( csv_table[1][1] == "double" );
   BOOST_CHECK( csv_table[2][1] == "adolc" );
   BOOST_CHECK( csv_table[3][1] == "cppad" );
   BOOST_CHECK( csv_table[4][1] == "sacado" );
   //
   for(size_t i = 1; i < csv_table.size(); ++i)
   {  BOOST_CHECK( csv_table[i][2] == "det_by_minor" );
      BOOST_CHECK( csv_table[i][3] == std::to_string(option.size) );
      BOOST_CHECK( csv_table[i][5] == CMPAD_CXX_COMPILER );
      BOOST_CHECK( csv_table[1][6] == debug );
   }
}
// END C++
