// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin xam_csv_write.cpp}

Example and Test of csv_write
#############################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end  xam_csv_write.cpp}
*/
// BEGIN C++
# include <boost/test/unit_test.hpp>
# include <cmpad/csv_write.hpp>
# include <fstream>

namespace {
   std::string get_file(const std::string& file_name)
   {  // ifs
      std::ifstream ifs(file_name);
      if( ifs.rdstate() & (std::ifstream::failbit != 0) )
      {  std::cerr << "csv_write.cpp: error opening " << file_name << "\n";
         std::exit(1);
      }
      //
      // length
      ifs.seekg (0, ifs.end);
      int length =  ifs.tellg();
      ifs.seekg (0, ifs.beg);
      //
      // buffer
      cmpad::vector<char> buffer(length + 1);
      ifs.read(buffer.data(), length);
      buffer[length] = '\0';
      //
      // file_data
      std::string file_data = buffer.data();
      return file_data;
   }
}

bool xam_csv_write(void)
{  //
   // ok
   bool ok = true;
   //
   // string
   using std::string;
   //
   // example_table
   cmpad::vec_vec_str example_table = {
      { "A", "B", "C"},
      { "item_1_A", "item_1_B", "item_1_C"},
      { "item_2_A", "item_2_B", "item_2_C"},
      { "item_3_A", "item_3_B", "item_3_C"}
   };
   //
   // file_name
   std::string file_name = "csv_write.csv";
   //
   // csv_write
   cmpad::csv_write(file_name, example_table);
   //
   // example_data
   string example_data = get_file(file_name);
   //
   // check
   const char* check =
      "A,B,C\n"
      "item_1_A,item_1_B,item_1_C\n"
      "item_2_A,item_2_B,item_2_C\n"
      "item_3_A,item_3_B,item_3_C\n"
   ;
   //
   // ok
   ok &= check == example_data;
   //
   return ok;
}

// END C++
