// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin csv_read}
{xrst_spell
   vec
   str
   newlines
   th
}

Read a Csv File
###############

Prototype
*********
{xrst_literal ,
   // BEGIN PROTOTYPE, // END PROTOTYPE
   // BEGIN RETURN, // END RETURN
}

vec_vec_str
***********
see :ref:`cmpad_typedef@vec_vec_str` .

file_name
*********
is the name of the file containing the csv file.
Each row in this file ends with a newlines ``'\n'``.
The columns are separated by commas ``','`` .
A comma at the end of a line means there is an empty value
at the end of the corresponding row.
There are no other special characters in this file.

csv_table
*********
#. The *j*-th column of the *i*-th row of the file contains the value
   csv_table[i][j] . The special characters ``'\n'`` and ``','`` are
   not included in these values.
#. The row and column indices start at zero.
#. csv_table.size() is the number of rows in the table
#. csv_table[i].size() is the number of columns in the *i*-th row.

{xrst_toc_hidden
   example/csv_read.cpp
}
Example
*******
The file :ref:`xam_csv_read.cpp-name` contains an example and test
of this routine.

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
      // csv_table
      vec_vec_str csv_table;
      //
      // ifs
      std::ifstream ifs(file_name);
      if( ( ifs.rdstate() & std::ifstream::failbit ) != 0 )
      {  std::cerr << "csv_table.read: error opening " << file_name
            << " for reading\n";
         return csv_table;
      }
      // csv_table
      cmpad::vector<std::string> row;
      row = get_row(ifs);
      while( row.size() > 0 )
      {  csv_table.push_back(row);
         row = get_row(ifs);
      }
      //
      // ifs
      ifs.close();
      //
      // BEGIN RETURN
      // ...
      return csv_table;
      // END RETURN
   }
}
