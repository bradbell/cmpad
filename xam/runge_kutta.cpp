// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin xam_runge_kutta.cpp}
{xrst_spell
   runge
   kutta
}

Example and Test of runge_kutta
###############################
{xrst_literal
   // BEGIN C++
   // END C++
}

ODE
***

.. math::

   y_i '(t) & = & 0           & \mbox(for) \; i = 0 \\
   y_i '(t) & = & y_{i-1} (t) & \mbox{for) \; i > 0

Initial Value
*************

.. math::

   y_i (0) & = & 1   & \mbox(for) \; i = 0 \\
   y_i (0) & = & 0   & \mbox{for) \; i > 0

Solution

.. math::

   y_0 (t) & = & 1
   y_1 (t) & = & t
   y_i (t) & = & t^i / i !


{xrst_end xam_runge_kutta.cpp}
*/
// BEGIN C++
# include <ctime>
# include <cmpad/algo/runge_kutta.hpp>
# include <cmpad/near_equal.hpp>
# include <limits>

namespace {

   // fun
   cmpad::vector<double> fun(const cmpad::vector<double>& y)
   {  size_t n = y.size();
      cmpad::vector<double> dy(n);
      dy[0] = 0.0;
      for(size_t i = 1; i < n; ++i)
         dy[i] = y[i-1];
      return dy;
   }
}

bool xam_runge_kutta(void)
{  //
   // ok
   bool ok = true;
   //
   // yi
   cmpad::vector<double> yi = { 1.0, 0.0, 0.0, 0.0, 0.0 };
   //
   // tf
   double tf = 1.0;
   //
   // ns
   size_t ns = 1;
   //
   // yf
   cmpad::vector<double> yf  = cmpad::runge_kutta(fun, yi, tf, ns);
   //
   // rel_error
   double rel_error = std::numeric_limits<double>::epsilon() * 100.0;
   //
   // ok
   ok &= cmpad::near_equal( yf[0], yi[0], rel_error );
   //
   // factorial
   // Note that y_i (t) = t^i / i! has no truncation error for i < 5.;
   double factorial = 1.0;
   for(size_t i = 1; i < yi.size(); ++i)
   {  factorial *= double(i);
      ok &= cmpad::near_equal( yf[i], 1.0 / factorial, rel_error );
   }
   //
   return ok;
}
// END C++
