// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin xam_csv_speed.cpp}

Example and Test of csv_speed
#############################

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end  xam_csv_speed.cpp}
*/

// BEGIN C++
# include <filesystem>
# include <cmpad/configure.hpp>
# include <cmpad/algo/det_by_minor.hpp>
# include <cmpad/fun_speed.hpp>
# include <cmpad/csv_read.hpp>
# include <cmpad/csv_speed.hpp>

namespace {
   std::string to_string(bool flag)
   {  if( flag )
         return "true";
      else
         return "false";
   }
}
bool xam_csv_speed(void)
{  //
   // ok
   bool ok = true;
   //
   // filesystem
   namespace filesystem =  std::filesystem;
   //
   // min_time
   double min_time = 0.1;
   //
   // file_name
   std::string file_name = "csv_speed.csv";
   filesystem::path file_path(CMPAD_PROJECT_DIR);
   file_path /= "build";
   file_path /= file_name;
   file_name = file_path.c_str();
   if( filesystem::exists( file_path )  )
      std::remove( file_name.c_str() );
   //
   // package
   std::string package = "double";
   //
   // algorithm
   std::string algorithm = "det_by_minor";
   //
   // option
   cmpad::option_t option;
   option.n_arg       = 4;
   option.time_setup = false;
   //
   // det_double
   cmpad::det_by_minor<double>        det_double;
   //
   // rate
   double rate = cmpad::fun_speed(det_double, option, min_time);
   //
   // csv_speed
   cmpad::csv_speed(
      file_name, rate, min_time, package, algorithm, option
   );
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
   // language
   std::string language = "c++";
   //
   // col_name, n_col
   cmpad::vector<std::string> col_name = {
      "rate",
      "min_time",
      "package",
      "algorithm",
      "n_arg",
      "time_setup",
      "date",
      "compiler",
      "debug",
      "language"
   };
   size_t n_col = col_name.size();
   //
   // ok
   // check sizes
   ok &= csv_table.size() == 2;
   for(size_t i = 0; i < 2; ++i)
      ok &= csv_table[i].size() == n_col;
   //
   // ok
   // check row 0
   ok &=( csv_table[0] == col_name );
   //
   // ok
   // check column 1-5, 7-9
   //
   ok &= std::atof( csv_table[1][1].c_str() ) == min_time;
   ok &= csv_table[1][2] == package;
   ok &= csv_table[1][3] == "det_by_minor";
   ok &= csv_table[1][4] == std::to_string(option.n_arg);
   ok &= csv_table[1][5] == to_string(option.time_setup);
   ok &= csv_table[1][7] == CMPAD_CXX_COMPILER;
   ok &= csv_table[1][8] == debug;
   ok &= csv_table[1][9] == language;
   //
   return ok;
}
// END C++
