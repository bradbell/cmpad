// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin xam_csv_read.cpp}

Example and Test of csv_read
############################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end  xam_csv_read.cpp}
*/
// BEGIN C++
# include <cmpad/csv_read.hpp>
# include <fstream>
# include <iostream>

bool xam_csv_read(void)
{  //
   // ok
   bool ok = true;
   //
   // string
   using std::string;
   //
   // ofs
   std::string file_name= "csv_read.csv";
   std::ofstream ofs(file_name);
   if( ofs.rdstate() & (std::ifstream::failbit != 0) )
   {  std::cerr << "csv_read.cpp: error opening " << file_name
         << " for writing\n";
      std::exit(1);
   }
   //
   // example_data
   const char* example_data =
      "A,B,C\n"
      "item_1_A,item_1_B,item_1_C\n"
      "item_2_A,item_2_B,item_2_C\n"
      "item_3_A,item_3_B,item_3_C\n"
   ;
   //
   // ofs
   ofs << example_data;
   ofs.close();
   //
   // example_table
   cmpad::vec_vec_str example_table = cmpad::csv_read(file_name);
   //
   // ok
   // example_table
   // check number of rows
   ok &= example_table.size() == 4;
   //
   // ok
   // example_table[0]
   ok &= example_table[0].size() == 3;
   for(int j = 0; j < 3; ++j)
   {  string c{ char('A' + j) };
      ok &= c == example_table[0][j];
   }
   //
   // ok
   // example_table[j] for 0 < j
   for(int i = 1; i < 4; ++i)
   {  ok &= example_table[i].size() == 3;
      string r{ char('0' + i) };
      for(int j = 0; j < 3; ++j)
      {  string c{ char('A' + j) };
         string item = "item_" + r + "_" + c;
         //
         ok &= item == example_table[i][j];
      }
   }
   //
   return ok;
}

// END C++
