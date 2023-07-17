// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_UNIFORM_01_HPP
# define CMPAD_UNIFORM_01_HPP
/*
{xrst_begin_parent uniform_01}
{xrst_spell
   std
   srand
   variate
}

Simulate a [0,1] Uniform Random Variate
#######################################

Syntax
******

|  ``# include <cmpad/speed/uniform_01.hpp>``
|  ``std::srand`` ( *seed* )
|  ``uniform_01`` ( *x* )

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
   example/uniform_01.cpp
}
Example
*******
The file :ref:`uniform_01.cpp-name` contains an example and test
of this routine.

Source Code
***********
The page :ref:`uniform_01.hpp-name` displays the source code for this function.

{xrst_end uniform_01}
------------------------------------------------------------------------------
{xrst_begin uniform_01.hpp}

uniform_10.hpp: Source Code
###########################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end uniform_01.hpp}
------------------------------------------------------------------------------
*/
// BEGIN C++
# include <cstdlib>
# include <cmpad/vector.hpp>

namespace cmpad {
   // BEGIN PROTOTYPE
   inline void uniform_01(cmpad::vector<double>& x)
   // END PROTOTYPE
   {  double factor = 1. / double(RAND_MAX);
      size_t n      = x.size();
      while(n--)
         x[n] = std::rand() * factor;
   }
}
// END C++
# endif
