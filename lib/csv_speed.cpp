// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# include <ctime>
# include <filesystem>
# include <cmpad/csv_speed.hpp>
# include <cmpad/csv_read.hpp>
# include <cmpad/csv_write.hpp>

namespace cmpad { // BEGIN_CMPAD_NAMESPACE

void csv_speed(
   const std::string& file_name ,
   const std::string& package   ,
   const std::string& algorithm ,
   double             rate      )
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
   {  cmpad::vector<std::string> row =
         { "date", "package"   , "algorithm" , "rate" };
      csv_table.push_back(row);
   }
   //
   // rate_str
   char buffer[100];
   snprintf(buffer, sizeof(buffer), "%g.5", rate);
   std::string rate_str = buffer;
   //
   // date_str
   std::time_t rawtime;
   std::time ( &rawtime );
   struct tm*  ptm = std::gmtime( &rawtime );
   int year  = ptm->tm_year + 1990;
   int month = ptm->tm_mon + 1;
   int day   = ptm->tm_mday;
   snprintf(buffer, sizeof(buffer), "%d-%d-%d", year, month, day);
   std::string date = buffer;
   //
   // csv_table
   cmpad::vector<std::string> row = { date, package, algorithm, rate_str };
   csv_table.push_back(row);
   //
   // file_name
   csv_write(file_name, csv_table);
}

} // END_CMPAD_NAMESPACE
