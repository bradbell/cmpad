// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// --------------------------------------------------------------------------
# ifndef CMPAD_VEC_VEC_STR_HPP
# define CMPAD_VEC_VEC_STR_HPP
/*
{xrst_begin vec_vec_str}
{xrst_spell
   std
   vec
   str
   typedef
}

Vector of Vector of String Type
###############################
{xrst_code cpp} */
# include <string>
# include <cmpad/vector.hpp>
namespace cmpad {
   typedef cmpad::vector< cmpad::vector<std::string> > vec_vec_str;
}
/* {xrst_code}
{xrst_end vec_vec_str}
*/

# endif
