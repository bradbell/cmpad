// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_FUN_SPEED_HPP
# define CMPAD_FUN_SPEED_HPP
/*
{xrst_begin fun_speed}
{xrst_spell
   obj
}

Determine Execution Speed of a Function Object
##############################################

Syntax
******
|  ``# include <cmpad/fun_speed.hpp>``
|  *y* = *fun_obj* ( *x* )
|  *rate* = ``cmpad::fun_speed`` ( *fun_obj*, *option*, *time_min* )

Prototype
*********
{xrst_literal
   // BEGIN PROTOTYPE
   // END PROTOTYPE
}

fun_obj
*******
We are testing the speed of the evaluation of *y* by this function object.

x
*
This is a ``cmpad::vector<double>`` object with size equal to the
dimension of the :ref:`fun_obj@domain` space for the function object.

y
*
This is a ``cmpad::vector<double>`` object with size equal to the
dimension of the :ref:`fun_obj@range` space for the function object.

option
******
This is the :ref:`option_t-name` object used to setup the function object
with the call
{xrst_code cpp}
   fun_obj.setup(option)
{xrst_code}

time_setup
==========
If option.time_setup is true (false) the setup function is (is not)
included in the time for each function evaluation.
If the setup time is not included, the only thing that changes
between function evaluations is the argument vector *x* .

time_min
********
This is the minimum time in seconds for the timing of the computation.
The computation of the function object will be repeated enough times
so that this minimum time is reached.

rate
****
This is the speed of one computation of the function object; i.e.,
the number of times per second that the function object gets computed.

{xrst_toc_hidden
   test/fun_speed.cpp
}
Example
*******
The file :ref:`fun_speed.cpp-name` is an example and test that
uses this function.

{xrst_end fun_speed}
-------------------------------------------------------------------------------
*/
# include <cmpad/uniform_01.hpp>

namespace cmpad { // BEGIN cmpad namespace

// BEGIN PROTOTYPE
template <class Fun_Obj> double fun_speed(
   Fun_Obj&         fun_obj    ,
   const option_t&  option     ,
   double           time_min   )
// END PROTOTYPE
{  //
   // steady_clock
   using std::chrono::steady_clock;
   //
   // time_point, duration
   typedef std::chrono::time_point<steady_clock> time_point;
   typedef std::chrono::duration<double>         duration;
   //
   // fun_obj.setup
   fun_obj.setup(option);
   //
   // x
   size_t n = fun_obj.domain();
   cmpad::vector<double> x(n);
   //
   // repeat, t_start, t_end, t_diff
   size_t     repeat  = 0;
   time_point t_start = steady_clock::now();
   time_point t_end   = steady_clock::now();
   double     t_diff  = duration(t_end - t_start).count();
   //
   // while t_diff < time_min
   while( t_diff < time_min )
   {  //
      // repeat
      if( repeat == 0 )
         repeat = 1;
      else
      {  if( 2 * repeat <= repeat )
         {  std::cerr << "cmpad::fun_speed: 2 * repeat <= repeat\n";
            std::exit(1);
         }
         repeat = 2 * repeat;
      }
      //
      // t_start
      t_start = steady_clock::now();
      //
      // computation
      for(size_t i = 0; i < repeat; ++i)
      {  uniform_01(x);
         if( option.time_setup )
            fun_obj.setup(option);
         fun_obj(x);
      }
      // t_diff
      t_end   = steady_clock::now();
      t_diff  = duration(t_end - t_start).count();
   }
   double rate = double(repeat) / t_diff;
   return rate;
}

} // END cmpad namespace
# endif
