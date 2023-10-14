// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_OPTION_T_HPP
# define CMPAD_OPTION_T_HPP

# include <cstddef>
# include <limits>
/*
{xrst_begin option_t}
{xrst_spell
   struct
   std
}

The Option Type
###############

Syntax
******
| |tab| ``# include <cmpad/option_t.hpp>``

Source Code
***********
{xrst_code cpp} */
namespace cmpad {
   struct option_t {
      size_t n_arg;
      size_t r_index;
      bool   time_setup;
      option_t(void)
      {  n_arg      = std::numeric_limits<size_t>::max();
         r_index    = std::numeric_limits<size_t>::max();
         time_setup = false;
      }
   };
}
/* {xrst_code}

n_arg
*****
is the dimension of the :ref:`cpp_fun_obj@domain` space for the algorithm.

r_index
*******
is the special range index for the algorithm and must be less than its
:ref:`cpp_fun_obj@range` .
For example, if we are computing gradients or Hessians,
it is the index in the algorithm range space that the gradient or Hessian
corresponds to.

time_setup
**********
if true (false) the setup time is included (is not included) in the execution
speed timing.

{xrst_end option_t}
*/

# endif
