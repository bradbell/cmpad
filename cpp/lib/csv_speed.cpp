// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin cpp_csv_speed}

Record a C++ Speed Result in a Csv File
#######################################

Prototype
*********
{xrst_literal
   // BEGIN PROTOTYPE
   // END PROTOTYPE
}


file_name
*********
This is the name of the file were the results will be recorded.
This file uses the :ref:`csv_column-name` format.

#. If the file is empty on input, the following csv header line
   is written as the first line of the file; i.e.,
   {xrst_literal
      xrst/csv_column.xrst
      BEGIN HEADER_LINE
      END HEADER_LINE
   }

#. A line is added to this file corresponding to
   this call to csv_speed.

rate
****
see :ref:`csv_column@rate`

min_time
********
see :ref:`csv_column@min_time`

package
*******
see :ref:`csv_column@package`

algorithm
*********
see :ref:`csv_column@algorithm`

special
*******
see :ref:`csv_column@special`

option
******

n_arg
=====
see :ref:`csv_column@n_arg`

n_other
=======
see :ref:`csv_column@n_other`

time_setup
==========
see :ref:`csv_column@time_setup`

{xrst_toc_hidden
   cpp/xam/csv_speed.cpp
}
Example
*******
:ref:`xam_csv_speed.cpp-name` contains an example and test of this routine.

{xrst_end cpp_csv_speed}
*/
# include <ctime>
# include <filesystem>
# include <sstream>
# include <iostream>
# include <cmpad/csv_speed.hpp>
# include <cmpad/csv_read.hpp>
# include <cmpad/csv_write.hpp>

namespace {
   //
   // bool2string
   std::string bool2string(bool value)
   {  if( value )
         return "true";
      return "false";
   }
   //
   // check_build_type
   void check_build_type(const std::string& package, const std::string& debug)
   {  // path
      using std::filesystem::path;
      //
      // none
      if( package == "none" )
         return;
      //
      // top_srcdir
      path current_dir = std::filesystem::current_path();
      path top_srcdir  = current_dir;
      path git_dir     = current_dir;
      git_dir         /= ".git";
      while ( ! std::filesystem::exists( git_dir  )  )
      {  path parent = top_srcdir.parent_path();
         if( parent == top_srcdir )
         {  std::cerr
            << "csv_speed: Can't find .git above current working directory:\n"
            << current_dir << "\n";
            std::exit(1);
         }
         top_srcdir = parent;
         git_dir    = top_srcdir;
         git_dir   /= ".git";
      }
      //
      // build_type
      std::string build_type;
      if( debug == "true" )
         build_type = "debug";
      else
         build_type = "release";
      //
      // build_dir
      path build_dir = top_srcdir;
      build_dir     /= "build";
      build_dir     /= build_type;
      //
      if ( ! std::filesystem::exists( build_dir ) )
      {  std::cerr
         << "csv_speed: Cannot find " << build_dir << "\n"
         << "and for this cmpad compile NDEBUG ";
         if( debug == "true" )
            std::cerr << "is not defined\n";
         else
            std::cerr << "is defined\n";
         std::exit(1);
      }
   }
}

namespace cmpad { // BEGIN_CMPAD_NAMESPACE

// BEGIN PROTOTYPE
void csv_speed(
   const std::string& file_name ,
   double             rate      ,
   double             min_time  ,
   const std::string& package   ,
   const std::string& algorithm ,
   bool               special   ,
   const option_t&    option    )
// END PROTOTYPE
{  //
   // file_system
   namespace filesystem = std::filesystem;
   //
   // csv_table
   vec_vec_str csv_table;
   //
   // csv_table
   filesystem::path path(file_name);
   if( filesystem::exists( filesystem::path(file_name) ) )
      csv_table = csv_read(file_name);
   else
   {  cmpad::vector<std::string> row = {
         "rate",
         "min_time",
         "package",
         "algorithm",
         "n_arg",
         "n_other",
         "time_setup",
         "date",
         "compiler",
         "debug",
         "language",
         "special"
      };
      csv_table.push_back(row);
   }
   // ss
   std::stringstream ss;
   //
   // rate_str
   ss.str("");
   ss << std::setprecision(1) << std::scientific << rate;
   std::string rate_str = ss.str();
   //
   // time_min_str
   ss.str("");
   ss << std::setprecision(3) << std::fixed << min_time;
   std::string min_time_str = ss.str();
   //
   // date
   std::time_t rawtime;
   std::time ( &rawtime );
   struct tm*  ptm = std::localtime( &rawtime );
   int year  = ptm->tm_year + 1900;
   int month = ptm->tm_mon + 1;
   int day   = ptm->tm_mday;
   ss.str("");
   ss << year << '-' << month << '-' << day;
   std::string date = ss.str();
   //
   // compiler
   std::string compiler = CMPAD_CXX_COMPILER;
   //
   // debug
# ifndef NDEBUG
   std::string debug = "true";
# else
   std::string debug = "false";
# endif
   check_build_type(package, debug);
   //
   // language
   std::string language = "c++";
   //
   // n_arg
   std::string n_arg = std::to_string(option.n_arg);
   //
   // n_other
   std::string n_other = std::to_string(option.n_other);
   //
   // time_setup
   std::string time_setup;
   if( option.time_setup )
      time_setup = "true";
   else
      time_setup = "false";
   //
   // csv_table
   cmpad::vector<std::string> row = {
      rate_str,
      min_time_str,
      package,
      algorithm,
      n_arg,
      n_other,
      time_setup,
      date,
      compiler,
      debug,
      language,
      bool2string(special)
   };
   csv_table.push_back(row);
   //
   // file_name
   csv_write(file_name, csv_table);
}

} // END_CMPAD_NAMESPACE
