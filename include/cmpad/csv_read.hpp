// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_CSV_READ_HPP  
# define CMPAD_CSV_READ_HPP  

# include <string>
# include <cmpad/typedef.hpp>
namespace cmpad {
   vec_vec_str csv_read(const std::string& file_name);

}

# endif
