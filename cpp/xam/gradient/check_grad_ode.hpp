// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef XAM_GRADIENT_CHECK_GRAD_ODE_HPP
# define XAM_GRADIENT_CHECK_GRAD_ODE_HPP
/*
{xrst_begin check_grad_ode.hpp}

C++ Check Gradient of an_ode
############################

Syntax
******
| |tab| ``# include "check_grad_ode.hpp"``
| |tab| *ok* = check_grad_ode( *grad_ode* )


Prototype
*********
{xrst_literal
   // BEGIN PROTOTYPE
   // END PROTOTYPE
}

grad_ode
********
Is a :ref:`cpp_gradient-name` object for an :ref:`cpp_an_ode-name` algorithm.

ok
**
is true (false) if the gradient passes (fails) the test.

Gradient
********
We use :math:`r` to denote :ref:`option_t@n_other` ; i.e.,
the range space component of the an_ode algorithm that we are
computing the gradient for.

.. math::

   y_r (t) = \frac{ t^{r+1} }{ (r+1)! }  \prod{j=0}^r x_j

.. math::

   \frac{ \partial y_r (t) }{  \partial x_j } = \begin{cases}
      y_r (t) / x_j   & \text{if} \; j \leq r  \\
      0               & \text{otherwise}
   \end{cases}


Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end  check_grad_ode.hpp}
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
   // time_setup
   for(bool time_setup : { true, false } )
   {  //
      // option
      cmpad::option_t option;
      option.n_arg      = n_arg;
      option.n_other    = 0;
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
      // r
      size_t r = n_arg - 1;
      //
      // y_r
      double tf  = 2.0;
      double y_r = x[0] * tf;
      for(size_t j = 1; j <= r; ++j)
      {  y_r = y_r * x[j] * tf / double(j+1);
      }
      //
      // ok
      for(size_t j = 0; j <= r; ++j)
         ok &= cmpad::near_equal( g[j], y_r / x[j], rel_error );
      for(size_t j = r+1; j < n_arg; ++j)
         ok &= g[j] == 0.0;
   }
   return ok;
}
// END C++

# endif
