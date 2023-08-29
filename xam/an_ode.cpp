// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin xam_an_ode.cpp}

Example and Test of an_ode
##########################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end xam_an_ode.cpp}
*/
// BEGIN C++
# include <ctime>
# include <cmpad/algo/an_ode.hpp>
# include <cmpad/near_equal.hpp>
# include <limits>

bool xam_an_ode(void)
{  //
   // ok
   bool ok = true;
   //
   // n
   size_t n = 5;
   //
   // ode
   cmpad::an_ode<double> ode;
   //
   // ode.setup
   cmpad::option_t option;
   option.n_arg = n;
   ode.setup(option);
   //
   // x
   cmpad::vector<double> x = { 1.0, 2.0, 3.0, 4.0, 5.0 };
   ok &= x.size() == n;
   //
   // yf
   cmpad::vector<double> yf = ode(x);
   //
   // rel_error
   double rel_error = std::numeric_limits<double>::epsilon() * 100.0;
   //
   // ok
   for(size_t i = 0; i < n; ++i)
   {  double yi        = 0.0;
      double t         = 2.0;
      double tj        = 1.0;
      size_t factorial = 1;
      for(size_t j = 0; j <= i; ++j)
      {  yi        += x[i-j] * tj / double(factorial);
         tj        *= t;
         factorial *= (j+1);
      }
      ok &= cmpad::near_equal( yf[i], yi, rel_error );
   }
   //
   return ok;
}
// END C++
