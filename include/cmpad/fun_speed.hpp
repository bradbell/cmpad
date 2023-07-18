# ifndef CPPAD_CMPAD_SPEED_TEST_HPP
# define CPPAD_CMPAD_SPEED_TEST_HPP
/*
{xrst_begin_parent fun_speed}

Determine Execution Speed of a Function Object
##############################################

Syntax
******
|  ``# include <cmpad/fun_speed.hpp>``
|  *fun_obj* . ``setup`` ( *ell* )
|  *n* = *fun_obj*.domain()
|  *y* = *fun_obj* ( *x* )
|  *rate* = ``cmpad::fun_speed`` ( *fun_obj*, *ell*, *time_min* )

Prototype
*********
{xrst_literal
   // BEGIN PROTOTYPE
   // END PROTOTYPE
}

fun_obj
*******
We are testing the speed of the evaluation of *y* by this function object.
The time to execute its setup routine is not included.

setup
*****
The *fun_obj* ``setup`` function is call once with *ell* equal
to is value in the call to ``cmpad::fun_speed``.
The time for this call is not included in the *rate* result .

ell
***
This parameter determines the size of the calculation corresponding
to the function object.

n
*
This is the dimenions of the domain space for the function object.

x
*
This is a ``cmpad::vector<double>`` object with size *n*.

y
*
This is a ``cmpad::vector<double>`` object with size equal to the
dimension of the range space for the function object.

time_min
********
This is the minimum time in seconds for the timing of the comuputation.
The computation of the function object will be repeated until
so that this minimum time is reached.

rate
****
This is the speed of one computation of the function object; i.e.,
the number of times per second that the function object gets computed.

Source Code
***********
The page :ref:`fun_speed.hpp-name` contains the source code for this funciton.

{xrst_end fun_speed}
-------------------------------------------------------------------------------
{xrst_begin fun_speed.hpp}

fun_speed: Source Code
**********************
{xrst_literal
   // BEGIN C++
   // END C++
}


{xrst_end fun_speed.hpp}
-------------------------------------------------------------------------------
*/

# include <cmpad/uniform_01.hpp>

namespace cmpad { // BEGIN cmpad namespace

// BEGIN PROTOTYPE
template <class Fun_Obj> double fun_speed(
   Fun_Obj& fun_obj    , 
   size_t   ell        , 
   double   time_min   )
// END PROTOTYPE
{  //  
   // steady_clock  
   using std::chrono::steady_clock;  
   //
   // time_point, duration
   typedef std::chrono::time_point<steady_clock> time_point;  
   typedef std::chrono::duration<double>         duration;
   //
   // fun_obj
   fun_obj.setup(ell);
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
