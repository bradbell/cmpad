// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef XAM_GRADIENT_CHECK_GRAD_ODE_HPP
# define XAM_GRADIENT_CHECK_GRAD_ODE_HPP
/*
{xrst_begin check_grad_ode}

Check Gradient of Determinant
#############################

Syntax
******

| ``# include "check_grad_ode.hpp"``
| *ok* = check_grad_ode( *grad_ode* )


Prototype
*********
{xrst_literal
   // BEGIN PROTOTYPE
   // END PROTOTYPE
}

grad_ode
********
Is a :ref:`gradient-name` object for an :ref:`an_ode-name` algorithm.

ok
**
is true (false) if the gradient passes (fails) the test.

Gradient
********

.. math::

   y_i (t) = \frac{t^{i+1}}{(i+1)!}  \prod{j=0}^i x_j \; \; \mbox{for all} \; i

.. math::

   \partial y_i (t) \partial x_j = \begin{cases}
      0               & \text{if} \; i < j \\
      y_i (t) / x_j   & \text{otherwise}
   \end{cases}


Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end  check_grad_ode}
*/
// BEGIN C++
# include <cmpad/uniform_01.hpp>
# include <cmpad/near_equal.hpp>
# include <cmpad/gradient.hpp>

// BEGIN PROTOTYPE
template <class Algo>
bool check_grad_ode( cmpad::gradient<Algo>& grad_ode )
// END PROTOTYPE
{  //
   // ok
   bool ok = true;
   //
   // rel_error
   double rel_error = 100. * std::numeric_limits<double>::epsilon();
   //
   // near_equal
   using cmpad::near_equal;
   //
   // n_arg
   size_t n_arg = 4;
   //
   // i
   // component of y that gradient corresponds to
   size_t i = n_arg - 1;
   //
   // time_setup
   for(bool time_setup : { true, false } )
   {  //
      // option
      cmpad::option_t option;
      option.n_arg      = n_arg;
      option.time_setup = time_setup;
      //
      // grad_ode
      grad_ode.setup(option);
      //
      // x
      // note that x[i] != 0.0 so can divide by it
      cmpad::vector<double> x(n_arg);
      cmpad::uniform_01(x);
      for(size_t i = 0; i < n_arg; ++i)
         x[i] += 1.0;
      //
      // g
      cmpad::vector<double> g = grad_ode(x);
      //
      // i
      size_t i = n_arg - 1;
      //
      // ok
      double tf  = 2.0;
      double yi  = x[0] * tf;
      for(size_t i = 1; i < n_arg; ++i)
      {  yi = x[i] * yi * tf / double(i+1);
      }
      for(size_t j = 0; j < n_arg; ++j)
         ok &= cmpad::near_equal( g[j], yi / x[j], rel_error );
   }
   return ok;
}
// END C++

# endif
