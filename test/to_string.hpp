// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef TEST_TO_STIRNG_HPP
# define TEST_TO_STIRNG_HPP

inline std::string to_string(bool flag)
{  if( flag )
      return "true";
   else
      return "false";
}

# endif
