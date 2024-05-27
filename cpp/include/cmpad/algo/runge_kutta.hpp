// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_ALGO_RUNGE_KUTTA_HPP
# define CMPAD_ALGO_RUNGE_KUTTA_HPP

/*
{xrst_begin_parent runge_kutta}
{xrst_spell
   dy
   ns
   tf
   yf
   yi
   yt
}

A C++ Fourth Order Runge Kutta Solver
#####################################

Syntax
******
| |tab| ``# include <cmpad/algo/runge_kutta.hpp>``
| |tab| *yf* = ``cmpad::runge_kutta`` ( *fun* , *yi* , *tf*, *ns* )

Prototype
*********
{xrst_literal
   // BEGIN PROTOTYPE
   // END PROTOTYPE
}

Purpose
*******
This routine returns an approximate solution
for :math:`y( t^f )` where :math:`y(0) = y^i` and
:math:`y' (t) = f(y)` .

Vector
******
The vectors *yi* and *yf* have this
fun_obj_vec :ref:`fun_obj_vec@Vector` type. 

fun
***
The syntax *dy* = *fun* ( *yt* ) ,
were *yt* is :math:`y(t)` ,
sets *dy* equal to the derivative :math:`y'(t)`  .
Both *yt* and *dy* are represented as *Vector* objects.

yi
**
is the value of :math:`y(t)` at :math:`t = 0` .

tf
**
is the value of *t* at which we wish to evaluate :math:`y(t)` .

ns
**
is the number of :ref:`Runge-Kutta steps<rk4_step-name>` to use.
The more steps the smaller the step size and the more accurate
the solution.

yf
**
The return value *yf* has the same size as *yi* and is the approximation
for :math:`y(t)` at *t* = *tf* .

{xrst_toc_table after
   cpp/xam/runge_kutta.cpp
}
Example
*******
:ref:`xam_runge_kutta.cpp-name`
contains an example and test of ``runge_kutta`` .

{xrst_end runge_kutta}
---------------------------------------------------------------------------
{xrst_begin runge_kutta.hpp}

C++ runge_kutta Source Code
###########################

{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end runge_kutta.hpp}
---------------------------------------------------------------------------
*/
// BEGIN C++

# include <cmpad/vector.hpp>

namespace cmpad { // BEGIN cmpad namespace

// BEGIN PROTOTYPE
template <class Vector, class Fun>
Vector runge_kutta(
   const Fun&                           fun ,
   const Vector&                        yi  ,
   const typename Vector::value_type    tf  ,
   size_t                               ns  )
// END PROTOTYPE
{
   // scalar_type
   typedef typename Vector::value_type scalar_type;
   //
   // two, six
   scalar_type two = scalar_type(2.0);
   scalar_type six = scalar_type(6.0);
   // n
   size_t n = yi.size();
   //
   // h
   scalar_type h  = tf / scalar_type( double(ns) );
   //
   // k1, k2, k3, k4, y_tmp
   Vector k1(n), k2(n), k3(n), k4(n), y_tmp(n);
   //
   //
   // i_step, yf
   Vector yf = yi;
   for(size_t i_step = 0; i_step < ns; ++i_step)
   {  //
      // k1
      k1 = fun(yf);
      //
      // k2
      for(size_t i = 0; i < n; ++i)
         y_tmp[i] = yf[i] + h * k1[i] / two;
      k2 = fun(y_tmp);
      //
      // k3
      for(size_t i = 0; i < n; ++i)
         y_tmp[i] = yf[i] + h * k2[i] / two;
      k3 = fun(y_tmp);
      //
      // k4
      for(size_t i = 0; i < n; ++i)
         y_tmp[i] = yf[i] + h * k3[i];
      k4 = fun(y_tmp);
      //
      // yf
      for(size_t i = 0; i < n; ++i)
         yf[i] = yf[i] + h * (k1[i] + two * k2[i] + two * k3[i] + k4[i]) / six;
   }
   return yf;
}

} // END cmpad namespace
// END C++
# endif
