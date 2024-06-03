// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_FUN_SPEED_HPP
# define CMPAD_FUN_SPEED_HPP
/*
{xrst_begin cpp_fun_speed}
{xrst_spell
   obj
}

Determine C++ Execution Speed
#############################

Syntax
******
| |tab| ``# include <cmpad/fun_speed.hpp>``
| |tab| *y* = *fun_obj* ( *x* )
| |tab| *rate* = ``cmpad::fun_speed`` ( *fun_obj*, *option*, *min_time* )

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
dimension of the :ref:`cpp_fun_obj_vec@domain` space for the function object.

y
*
This is a ``cmpad::vector<double>`` object with size equal to the
dimension of the :ref:`cpp_fun_obj_vec@range` space for the function object.

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

min_time
********
This is the minimum time in seconds for the timing of the computation.
The computation of the function object will be repeated enough times
so that this minimum time is reached.

rate
****
This is the speed of one computation of the function object; i.e.,
the number of times per second that the function object gets computed.

{xrst_toc_hidden
   cpp/xam/fun_speed.cpp
}
Example
*******
:ref:`xam_fun_speed.cpp-name` is an example and test that uses this function.

{xrst_end cpp_fun_speed}
-------------------------------------------------------------------------------
*/
# include <iostream>
# include <chrono>
# include <cmpad/uniform_01.hpp>
# include <cmpad/option_t.hpp>

namespace cmpad { // BEGIN cmpad namespace

// BEGIN PROTOTYPE
template <class Fun_Obj> double fun_speed(
   Fun_Obj&         fun_obj    ,
   const option_t&  option     ,
   double           min_time   )
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
   // while t_diff < min_time
   while( t_diff < min_time )
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
