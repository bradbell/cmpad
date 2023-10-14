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
This is the value of *option*\ .\ ``n_arg`` .

g_index
*******
This is the value of *option*\ .\ ``g_index`` .

time_setup
**********
This is the value of *option*\ .\ ``time_setup`` .

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
# include <cmpad/csv_speed.hpp>
# include <cmpad/csv_read.hpp>
# include <cmpad/csv_write.hpp>

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
         "g_index",
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
   //
   // language
   std::string language = "c++";
   //
   // n_arg
   std::string n_arg = std::to_string(option.n_arg);
   //
   // g_index
   std::string g_index = std::to_string(option.g_index);
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
      g_index,
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
