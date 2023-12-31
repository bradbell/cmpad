// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_CSV_SPEED_HPP
# define CMPAD_CSV_SPEED_HPP

# include <string>
# include <cmpad/option_t.hpp>

namespace cmpad {
   void csv_speed(
      const std::string& file_name ,
      double             rate      ,
      double             min_time  ,
      const std::string& package   ,
      const std::string& algorithm ,
      bool               special   ,
      const option_t&    option
   );
}

# endif
