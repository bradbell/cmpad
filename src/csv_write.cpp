// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin csv_write}
{xrst_spell
   vec
   str
   newlines
   th
}

Write a Csv File
################

Prototype
*********
{xrst_literal
   // BEGIN PROTOTYPE
   // END PROTOTYPE
}

vec_vec_str
***********
see :ref:`cmpad_typedef@vec_vec_str` .

file_name
*********
is the name of the file containing the csv file.
The rows in this file are separated by newlines ``'\n'``
and the columns are separated by commas ``','`` .
There are no other special characters in this file.

csv_table
*********
#. The *j*-th column of the *i*-th row of the file contains the value
   csv_table[i][j] .
#. 0 < csv_table[i].size() for all row indices *i* .
#. The character ``','`` is added between columns.
#. The character ``'\n'`` is added at the end of every line.

{xrst_toc_hidden
   example/csv_write.cpp
}
Example
*******
The file :ref:`xam_csv_write.cpp-name` contains an example and test
of this routine.

{xrst_end csv_write}
------------------------------------------------------------------------------
*/

# include <string>
# include <fstream>
# include <cmpad/typedef.hpp>

namespace {
   // get_row
   void put_row(std::ofstream& ofs, const cmpad::vector<std::string>& row)
   {  //
      assert( 0 < row.size() );
      //
      // ofs
      ofs << row[0];
      for(size_t j = 1; j < row.size(); ++j)
         ofs << ',' << row[j];
      ofs << '\n';
      //
      return;
   }
}

namespace cmpad {
   // BEGIN PROTOTYPE
   void csv_write(
      const std::string& file_name ,
      const vec_vec_str& csv_table )
   // END PROTOTYPE
   {  //
      // ofs
      std::ofstream ofs(file_name);
      if( ( ofs.rdstate() & std::ofstream::failbit ) != 0 )
      {  std::cerr << "csv_table.write: error opening " << file_name
            << " for writing\n";
         return;
      }
      // csv_table
      for(size_t i = 0; i < csv_table.size(); ++i)
         put_row(ofs, csv_table[i]);
      //
      // ofs
      ofs.close();
   }
}
