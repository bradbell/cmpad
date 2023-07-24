// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin uniform_01}
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
The file :ref:`xam_uniform_01.cpp-name` contains an example and test
of this routine.

{xrst_end uniform_01}
------------------------------------------------------------------------------
\{xrst_begin uniform_01.cpp}

uniform_10.cpp: Source Code
###########################
\{xrst_literal
   // BEGIN C++
   // END C++
}

\{xrst_end uniform_01.cpp}
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
