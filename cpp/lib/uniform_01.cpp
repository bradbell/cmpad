// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin uniform_01}
{xrst_spell
   srand
   std
}

Simulate a [0,1] Uniform Random Variate
#######################################

Syntax
******
| |tab| ``# include <cmpad/speed/uniform_01.hpp>``
| |tab| ``std::srand`` ( *seed* )
| |tab| ``cmpad::uniform_01`` ( *x* )

Prototype
*********
{xrst_literal
   // BEGIN PROTOTYPE
   // END PROTOTYPE
}

Purpose
*******
This routine is used to create random values for speed testing.

seed
****
The argument *seed* specifies a seed
for the uniform random number generator.

x
*
The input value of the elements of *x* does not matter.
Upon return, the elements of *x* are set to values
uniformly sampled over the interval [0,1].

{xrst_toc_hidden
   cpp/xam/uniform_01.cpp
}
Example
*******
:ref:`xam_uniform_01.cpp-name` contains an example and test of this routine.

{xrst_end uniform_01}
------------------------------------------------------------------------------
*/
// BEGIN C++
# include <cstdlib>
# include <cmpad/uniform_01.hpp>

namespace cmpad {
   // BEGIN PROTOTYPE
   void uniform_01(cmpad::vector<double>& x)
   // END PROTOTYPE
   {  double factor = 1. / double(RAND_MAX);
      size_t n      = x.size();
      while(n--)
         x[n] = std::rand() * factor;
   }
}
// END C++
