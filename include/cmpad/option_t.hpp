// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_OPTION_T_HPP
# define CMPAD_OPTION_T_HPP

# include <cstddef>
/*
{xrst_begin option_t}
o{xrst_spell
   struct
}

The Option Type
###############

Syntax
******
| ``# include <cmpad/option_t.hpp>``

Source Code
***********
{xrst_code cpp} */
namespace cmpad {
   struct option_t {
      size_t n_arg;
      bool   time_setup;
   };
}
/* {xrst_code}
{xrst_end option_t}
*/

# endif
