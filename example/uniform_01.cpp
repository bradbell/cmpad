// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin xam_uniform_01.cpp}

Example and Test of uniform_01
##############################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end xam_uniform_01.cpp}
*/
// BEGIN C++
# include <ctime>
# include <cmpad/uniform_01.hpp>

bool xam_uniform_01(void)
{  //
   // ok
   bool ok = true;
   //
   // seed
   unsigned int seed = static_cast<unsigned int>( std::time(nullptr) );
   //
   // srand
   std::srand(seed);
   //
   // n, x
   size_t n = 10;
   cmpad::vector<double> x(n);
   for(size_t i = 0; i < n; ++i)
      x[i] = -1;
   //
   // x
   cmpad::uniform_01(x);
   //
   // ok
   for(size_t i = 0; i < n; ++i)
      ok &= 0.0 <= x[i] && x[i] <= 1.0;
   //
   return ok;
}
// END C++
