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

n_arg
*****
is the dimension of the :ref:`fun_obj@domain` space for the algorithm.

time_setup
**********
if true (false) the setup time is included (is not included) in the execution
speed timing.

{xrst_end option_t}
*/

# endif
