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

   y_i (t) = \sum_{j=0}^i x_{i-j} \frac{t^j}{j!}  \; \; \mbox{for all} \; i

.. math::

   \partial y_i (t) \partial x_{i-j} = \frac{t^j}{j!}


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
   size_t n_arg = 5;
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
      cmpad::vector<double> x(n_arg);
      cmpad::uniform_01(x);
      //
      // g
      cmpad::vector<double> g = grad_ode(x);
      //
      // i
      size_t i = n_arg - 1;
      //
      // t
      double t = 2.0;
      //
      // ok
      double check = 1.0;
      ok &= cmpad::near_equal( g[i], check, rel_error );
      //
      // ok
      for(size_t j = 1; j < n_arg; ++j)
      {  check *= t / double(j);
         ok &= cmpad::near_equal( g[i-j], check, rel_error );
      }
   }
   return ok;
}
// END C++

# endif
