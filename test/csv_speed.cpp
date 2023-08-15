// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin csv_speed.cpp}

csv_speed: Example and Test
###########################

Example Results
***************

.. csv-table::
   :file: {xrst_dir test/csv_speed.csv}

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}


{xrst_end  csv_speed.cpp}
*/
// BEGIN C++
# include <filesystem>
# include <boost/test/unit_test.hpp>
# include <cmpad/configure.hpp>
# include <cmpad/det_by_minor.hpp>
# include <cmpad/adolc/gradient.hpp>
# include <cmpad/cppad/gradient.hpp>
# include <cmpad/cppad_jit/gradient.hpp>
# include <cmpad/sacado/gradient.hpp>
# include <cmpad/autodiff/gradient.hpp>
# include <cmpad/fun_speed.hpp>
# include <cmpad/csv_speed.hpp>
# include <cmpad/csv_read.hpp>

namespace {
   std::string to_string(bool flag)
   {  if( flag )
         return "true";
      else
         return "false";
   }
}
BOOST_AUTO_TEST_CASE(csv_speed)
{  //
   // filesystem
   namespace filesystem =  std::filesystem;
   //
   // time_min
   double time_min = 0.5;
   //
   // file_name
   std::string file_name = "csv_speed.csv";
   filesystem::path file_path(CMPAD_PROJECT_DIR);
   file_path /= "test";
   file_path /= file_name;
   BOOST_REQUIRE( filesystem::exists( file_path )  );
   file_name = file_path.c_str();
   std::remove( file_name.c_str() );
   //
   // package
   cmpad::vector<std::string> package;
   //
   // algorithm
   std::string algorithm = "det_by_minor";
   //
   // size
   size_t size = 6;
   //
   // time_setup
   for(bool time_setup : {true, false} )
   {
      // option
      cmpad::option_t option;
      option.size       = size;
      option.time_setup = time_setup;
      //
      // rate
      double rate;
      //
      // det_by_minor
      using cmpad::det_by_minor;
      //
      // double
      package.push_back("double");
      cmpad::det_by_minor<double>        det_double;
      rate = cmpad::fun_speed(det_double, option, time_min);
      cmpad::csv_speed(file_name, rate, "double", algorithm, option);
      //
# if CMPAD_HAS_ADOLC
      package.push_back("adolc");
      cmpad::adolc::gradient<det_by_minor>          grad_det_adolc;
      rate = cmpad::fun_speed(grad_det_adolc, option, time_min);
      cmpad::csv_speed(file_name, rate, "adolc", algorithm, option);
# endif
      //
# if CMPAD_HAS_CPPAD
      //
      // cppad
      package.push_back("cppad");
      cmpad::cppad::gradient<det_by_minor>           grad_det_cppad;
      rate = cmpad::fun_speed(grad_det_cppad, option, time_min);
      cmpad::csv_speed(file_name, rate, "cppad", algorithm, option);
      //
      // cppad_jit
      package.push_back("cppad_jit");
      cmpad::cppad_jit::gradient<det_by_minor>       grad_det_cppad_jit;
      rate = cmpad::fun_speed(grad_det_cppad_jit, option, time_min);
      cmpad::csv_speed(file_name, rate, "cppad_jit", algorithm, option);
# endif
      //
# if CMPAD_HAS_SACADO
      package.push_back("sacado");
      cmpad::sacado::gradient<det_by_minor>          grad_det_sacado;
      rate = cmpad::fun_speed(grad_det_sacado, option, time_min);
      cmpad::csv_speed(file_name, rate, "sacado", algorithm, option);
# endif
      //
# if CMPAD_HAS_AUTODIFF
      package.push_back("autodiff");
      cmpad::autodiff::gradient<det_by_minor>        grad_det_autodiff;
      rate = cmpad::fun_speed(grad_det_autodiff, option, time_min);
      cmpad::csv_speed(file_name, rate, "autodiff", algorithm, option);
# endif
   }
   assert( package.size() % 2 == 0 );
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
   // col_name
   cmpad::vector<std::string> col_name = {
      "rate",
      "package",
      "algorithm",
      "size",
      "time_setup",
      "date",
      "compiler",
      "debug"
   };
   //
   // n_row, n_col, n_time_setup
   size_t n_row        = package.size() + 1; // header row is not in package
   size_t n_col        = col_name.size();
   size_t n_time_setup = package.size() / 2;
   //
   // check sizes
   BOOST_CHECK( csv_table.size() == n_row );
   for(size_t i = 0; i < csv_table.size(); ++i)
      BOOST_CHECK( csv_table[i].size() == n_col );
   //
   // check row 0
   BOOST_CHECK( csv_table[0] == col_name );
   //
   // check column 1
   for(size_t i = 1; i < n_row; ++i)
      BOOST_CHECK( csv_table[i][1] == package[i-1] );
   //
   // check column 2, 3, 4, 6, 7
   for(size_t i = 1; i < n_row; ++i)
   {  bool time_setup = i <= n_time_setup;
      //
      BOOST_CHECK( csv_table[i][2] == "det_by_minor" );
      BOOST_CHECK( csv_table[i][3] == std::to_string(size) );
      BOOST_CHECK( csv_table[i][4] == to_string(time_setup) );
      BOOST_CHECK( csv_table[i][6] == CMPAD_CXX_COMPILER );
      BOOST_CHECK( csv_table[1][7] == debug );
   }
}
// END C++
