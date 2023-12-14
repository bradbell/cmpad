// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin cpp_csv_speed}
{xrst_spell
   newlines
}

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
is the name of the file were the results will be recorded.

#. This is a csv file. To be specific commas separate columns
   and newlines terminate rows; see :ref:`csv_read-name` and
   :ref:`csv_write-name` .

#. A line is added to this file corresponding to
   rate in this call to csv_speed.

#. If the file is empty on input, the following csv header line
   is written to the file before the result for this call::

      rate,min_time,package,algorithm,n_arg,date,compiler,debug,language

#. If the file is not empty on input, it is assumed that the header line
   for this file is as above.

rate
****
This is the number of times per second that the algorithm,
or a derivative of the algorithm, was calculated.

min_time
********
This is the :ref:`cpp_fun_speed@min_time` used
by fun_speed when it computed *rate*.

package
*******
This is the name of the AD package that *rate* corresponds to.
If *package* is ``double`` , this is not a derivative calculation
but rather an evaluations of the algorithm using the C++ type double.

algorithm
*********
This is the name of the algorithm; e.g., :ref:`cpp_det_by_minor-name` .

n_arg
*****
This is the value of :ref:`option_t@n_arg` in *option* .

n_other
*******
This is the value of :ref:`option_t@n_other` in *option* .

time_setup
**********
This is the value of :ref:`option_t@time_setup` in *option* .

date
****
This is the date when csv_speed is called.
The *date* value is automatically determined and not an argument to csv_speed.

compiler
********
This is the compiler used for this test.
The *compiler* value
is automatically determined and not an argument to csv_speed.

debug
*****
This is true (false) if  csv_speed eas compiled with (without) debugging.
The assumption here is that all the cmpad routines get compiled
with debugging (for speed) when this is true (false).
The *debug* value is automatically determined and not an argument to csv_speed.

{xrst_toc_hidden
   cpp/xam/csv_speed.cpp
}

language
********
This is always ``c++`` because this routine is for timing C++ functions.


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
      // configure_flag
      path configure_flag = top_srcdir;
      configure_flag     /= "external";
      if( package == "cppad_jit" )
         configure_flag /= "cppad." + build_type;
      else 
         configure_flag /= package + "." + build_type;
      //
      if ( ! std::filesystem::exists( configure_flag ) )
      {  std::cerr 
         << "csv_speed: Cannot find " << configure_flag << "\n"
         << "and for this cmpad compile NDEBUG ";
         if( debug == "true" )
            std::cerr << "is not defined\n";
         else
            std::cerr << "is defined\n";
         std::cerr 
         << "Perhaps you should run the following commands:\n";
         std::cerr 
         << "   bin/get_package.sh " + build_type + " " + package + "\n"
         << "   cd cpp/build; make; cd ../..\n\n";
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
         "language"
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
      language
   };
   csv_table.push_back(row);
   //
   // file_name
   csv_write(file_name, csv_table);
}

} // END_CMPAD_NAMESPACE
