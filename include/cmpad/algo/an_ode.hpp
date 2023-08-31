// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_ALGO_AN_ODE_HPP
# define CMPAD_ALGO_AN_ODE_HPP
/*
{xrst_begin_parent an_ode}
{xrst_spell
   Runge
   Kutta
   yf
   llll
   truncation
}

Use Runge-Kutta Method to Solve an ODE
######################################

Syntax
******
| ``# include <cmpad/algo/an_ode.hpp>``
| ``cmpad::an_ode`` < *Scalar* > *ode*
| *ode* . ``setup`` ( *option* )
| *yf* = *ode* ( *x* )

Prototype
*********
{xrst_literal
   // BEGIN PROTOTYPE
   // END PROTOTYPE
}

Purpose
*******
This implements the :ref:`fun_obj-name` interface.
The function call uses :ref:`runge_kutta-name` to
compute the solution of the ODE defined below:

The ODE
*******

.. math::

   \begin{array}{llll}
   y_i '(t) & = & x_0                          & \mbox{for} \; i = 0 \\
   y_i '(t) & = & \sum_{j=1}^i x_j y_{i-1} (t) & \mbox{for} \; i > 0  \\
   \end{array}

Initial Value
*************

.. math::

   y_i (0) = 0  \; \mbox{for all} \; i

Solution
********
This initial value problem has the following analytic solution
(which can be used to check function values and derivatives):

.. math::

   \begin{array}{llll}
   y_0 (t) & = & x_0 t \\
   y_1 (t) & = & x_0 x_1 t^2 / 2 ! \\
   y_2 (t) & = & x_0 x_1 x_2 t^3 / 3 !
   \end{array}

.. math ::

   y_i (t) = \frac{t^{i+1}{(i+1)!} \prod_{j=0}^i x_j \; \; \mbox{for all} \; i

ode
***
The object *ode* corresponding to :ref:`fun_obj@fun`
in the function object interface.
It computes a Runge-Kutta approximation for :math:`y(t)` at :math:`t = 2` .
Note that this approximation for :math:`y_i (t)` has no truncation error
for :math:`i < 4` (because it is a fourth order method).

option
******
This contains the options that are used to setup the function object.

n_arg
=====
This is the size of the vectors *x* and *yf* .

x
*
This is the initial value for the vector :math:`y(0)` .

yf
**
The return value *yf* is :math:`y(t)` at :math:`t = 2` .

{xrst_toc_hidden after
   xam/an_ode.cpp
   include/cmpad/algo/runge_kutta.hpp
}
Example
*******
:ref:`xam_an_ode.cpp-name` contains an example and test of ``an_ode`` .

Source Code
***********
:ref:`an_ode.hpp-name` is the source code for this algorithm.

{xrst_end an_ode}
------------------------------------------------------------------------------
{xrst_begin an_ode.hpp}

an_ode: Source Code
###################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end an_ode.hpp}
*/
// BEGIN C++
# include <cassert>
# include <cmpad/fun_obj.hpp>
# include <cmpad/algo/runge_kutta.hpp>

namespace cmpad { // BEGIN cmpad namespace

// an_ode_fun
template <class Scalar> class an_ode_fun
{
private:
   // x_
   cmpad::vector<Scalar> x_;
public:
   //
   // operator
   cmpad::vector<Scalar> operator()(const cmpad::vector<Scalar>& y) const
   {  size_t n = y.size();
      assert( x_.size() == n );
      cmpad::vector<Scalar> dy(n);
      dy[0] = x_[0];
      for(size_t i = 1; i < n; ++i)
         dy[i] = x_[i] * y[i-1];
      return dy;
   }
   //
   // set_x
   void set_x(const cmpad::vector<Scalar>& x)
   {  x_ = x;
   }
};

// BEGIN PROTOTYPE
template <class Scalar> class an_ode : public fun_obj<Scalar>
// END PROTOTYPE
{
private:
   // option_
   option_t option_;
   //
   // zero_
   cmpad::vector<Scalar> zero_;
   //
   // yf_
   cmpad::vector<Scalar> yf_;
   //
   // fun_
   an_ode_fun<Scalar> fun_;
public:
   // value_type
   typedef Scalar value_type;
   //
   // option
   const option_t& option(void) const override
   {  return option_; }
   //
   // domain
   size_t domain(void) const override
   {  return option_.n_arg; }
   //
   // range
   size_t range(void) const override
   {  return option_.n_arg; }
   //
   // setup
   void setup(const option_t& option) override
   {  //
      // option_
      option_ = option;
      //
      // zero_
      zero_.resize(option.n_arg);
      for(size_t i = 0; i < zero_.size(); ++i)
         zero_[i] = Scalar(0.0);
      //
      // yf_
      yf_.resize(option.n_arg);
   }
   //
   // operator
   const cmpad::vector<Scalar>& operator()(
      const cmpad::vector<Scalar>& x
   ) override
   {  //
      // x
      assert( x.size() == domain() );
      fun_.set_x(x);
      //
      // tf
      Scalar tf = Scalar(2);
      //
      // ns
      size_t ns = option_.n_arg;
      //
      // yf
      const cmpad::vector<Scalar>& yi = zero_;
      yf_ = cmpad::runge_kutta(fun_, yi, tf, ns);
      assert( yf_.size() == domain() );
      //
      return yf_;
   }
};

}  // END cmpad namespace

// END C++
# endif
