// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef TEST_CSV_FIXTURE_HPP
# define TEST_CSV_FIXTURE_HPP

# include <filesystem>
# include <cmpad/csv_read.hpp>
# include "to_string.hpp"

// remove csv_spe
class csv_fixture
{  //
public:
   //
   // algorithm_
   std::string algorithm_;
   //
   // size_
   const size_t n_arg_;
   //
   // min_time_
   const double min_time_;
   //
   // debug_
   const std::string debug_;
   //
   // package_
   // set by set_package
   std::string package_;
   //
   // csv_file_path_
   // set by set_package
   std::string csv_file_path_;
   //
   // ctor
   csv_fixture(void)
   : algorithm_("det_by_minor")
   , n_arg_(6)
   , min_time_(0.5)
# ifdef NDEBUG
   , debug_("false")
# else
   , debug_("true")
# endif
   { }
   // set_package
   // sets package_ and csv_file_path_
   void set_package(const std::string& package)
   {  //
      // package_
      package_ = package;
      //
      // csv_file
      std::string csv_file = package + ".csv";
      //
      // file_path
      // This assumes that CMAKE_BINARY_DIR = CMPAD_PROJECT_DIR/build.
      std::filesystem::path file_path(CMPAD_PROJECT_DIR);
      file_path /= "build";
      file_path /= "test";
      file_path /= csv_file;
      //
      // csv_file_path_
      if( std::filesystem::exists( file_path )  )
         std::remove( file_path.c_str() );
      csv_file_path_ = file_path.c_str();
   }
   //
   // check
   void check(void)
   {  //
      // csv_table
      cmpad::vec_vec_str csv_table = cmpad::csv_read(csv_file_path_);
      //
      // col_name
      cmpad::vector<std::string> col_name = {
         "rate",
         "min_time",
         "package",
         "algorithm",
         "n_arg",
         "time_setup",
         "date",
         "compiler",
         "debug"
      };
      //
      // n_row, n_time_setup
      size_t n_row     = csv_table.size();
      //
      // check row 0
      BOOST_CHECK( csv_table[0] == col_name );
      //
      // check column 1
      BOOST_CHECK( std::atof(csv_table[n_row-2][1].c_str()) == min_time_ );
      BOOST_CHECK( std::atof(csv_table[n_row-1][1].c_str()) == min_time_ );
      //
      // check column 2
      // each package outputs two rows
      BOOST_CHECK( csv_table[n_row-2][2] == package_ );
      BOOST_CHECK( csv_table[n_row-1][2] == package_ );
      //
      // check column 5
      // time_setup is true and then false
      BOOST_CHECK( csv_table[n_row-2][5] == "true"   );
      BOOST_CHECK( csv_table[n_row-1][5] == "false"  );
      //
      // check column 3, 4, 7, 8
      for(size_t i = n_row-1; i < n_row; ++i)
      {  BOOST_CHECK( csv_table[i][3] == algorithm_ );
         BOOST_CHECK( csv_table[i][4] == std::to_string(n_arg_) );
         BOOST_CHECK( csv_table[i][7] == CMPAD_CXX_COMPILER );
         BOOST_CHECK( csv_table[1][8] == debug_ );
      }
   }
};

# endif
