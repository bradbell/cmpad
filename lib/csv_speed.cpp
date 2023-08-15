// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin csv_speed}
{xrst_spell
   newlines
}

Record Speed of an AD Package for an Algorithm
##############################################

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

      rate,package,algorithm,size,date,compiler,debug

#. If the file is not empty on input, it is assumed that the header line
   for this file is as above.

rate
****
This is the number of times per second that the algorithm,
or a derivative of the algorithm, was calculated.

package
*******
This is the name of the AD package that *rate* corresponds to.
If *package* is ``double`` , this is not a derivative calculation
but rather an evaluations of the algorithm using the C++ type double.

algorithm
*********
This is the name of the algorithm; e.g., :ref:`det_by_minor-name` .

size
****
This is the value of *option*\ .\ ``size`` .

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
   test/csv_speed.cpp
}
Example
*******
The file :ref:`csv_speed.cpp-name` contains an example and test
of this routine.

{xrst_end csv_speed}
*/
# include <ctime>
# include <filesystem>
# include <sstream>
# include <cmpad/csv_speed.hpp>
# include <cmpad/csv_read.hpp>
# include <cmpad/csv_write.hpp>

namespace cmpad { // BEGIN_CMPAD_NAMESPACE

void csv_speed(
   const std::string& file_name ,
   double             rate      ,
   const std::string& package   ,
   const std::string& algorithm ,
   const option_t&    option    )
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
         "package",
         "algorithm",
         "size",
         "time_setup",
         "date",
         "compiler",
         "debug"
      };
      csv_table.push_back(row);
   }
   //
   // ss, rate_str
   std::stringstream ss;
   ss << std::setprecision(1) << std::scientific << rate;
   std::string rate_str = ss.str();
   ss.str("");
   //
   // date
   std::time_t rawtime;
   std::time ( &rawtime );
   struct tm*  ptm = std::localtime( &rawtime );
   int year  = ptm->tm_year + 1900;
   int month = ptm->tm_mon + 1;
   int day   = ptm->tm_mday;
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
   // size
   std::string size = std::to_string(option.size);
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
      package,
      algorithm,
      size,
      time_setup,
      date,
      compiler,
      debug
   };
   csv_table.push_back(row);
   //
   // file_name
   csv_write(file_name, csv_table);
}

} // END_CMPAD_NAMESPACE
