// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin csv_read}

Read a Csv File
###############

{xrst_end csv_read}
------------------------------------------------------------------------------
*/

# include <string>
# include <fstream>
# include <cmpad/csv_read.hpp>

namespace {
   // get_row
   cmpad::vector<std::string> get_row(std::ifstream& ifs)
   {  // line  
      std::string line;
      std::getline(ifs, line);
      //
      // row
      cmpad::vector<std::string> row;
      if( (ifs.rdstate() & std::ifstream::eofbit) != 0 )
         return row;
      //
      // row
      size_t previous = 0;
      size_t next     = line.find(',', previous);
      while( next != std::string::npos )
      {  row.push_back( line.substr(previous, next - previous) );
         previous = next + 1;
         next     = line.find(',', previous);
      }
      row.push_back( line.substr(previous, line.size() ) );
      //
      return row;
   }
}

namespace cmpad {
   // BEGIN PROTOTYPE
   vec_vec_str csv_read(const std::string& file_name)
   // END PROTOTYPE
   {  //
      // ifs  
      std::ifstream ifs(file_name);
      if( ( ifs.rdstate() & std::ifstream::failbit ) != 0 )
      {  std::cerr << "csv_table.read: error opening " << file_name 
            << " for reading\n";
         return false;
      }
      // csv_table
      vec_vec_str                csv_table;
      cmpad::vector<std::string> row; 
      row = get_row(ifs);
      while( row.size() > 0 )
      {  csv_table.push_back(row);
         row = get_row(ifs);
      }
      //
      // BEGIN RETURN
      // ...
      return csv_table;
      // END RETURN
   }
}
