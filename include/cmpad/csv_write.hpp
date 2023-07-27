// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_CSV_WRITE_HPP
# define CMPAD_CSV_WRITE_HPP

# include <cmpad/vec_vec_str.hpp>
namespace cmpad {
   void csv_write(
      const std::string& file_name  , const vec_vec_str& csv_table
   );
}

# endif
