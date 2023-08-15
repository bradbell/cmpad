// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin xam_near_equal.cpp}

Example and Test of near_equal
##############################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end xam_near_equal.cpp}
*/
// BEGIN C++
# include <ctime>
# include <cmpad/configure.hpp>
# include <cmpad/near_equal.hpp>
# include <sstream>

bool xam_near_equal(void)
{  //
   // ok
   bool ok = true;
   //
   // rel_error
   double rel_error = 1e-4;
   // 
   // x, y
   double x = 3.000;
   double y = x * (1.0 + rel_error / 2 ); 
   //
   // ok
   ok &= cmpad::near_equal(x, y, rel_error);
   //
   // rel_error, vec, os
   rel_error  = rel_error / 10.0;
   std::stringstream os;
   cmpad::vector<double> vec;
   //
   // ok
   ok &= ! cmpad::near_equal(x, y, rel_error, vec, os);
   //
   // vec
   vec.resize(1);
   vec[0]     = x * 10; 
   //
   // ok
   ok &=   cmpad::near_equal(x, y, rel_error, vec);
   //
   return ok;
}
// END C++
