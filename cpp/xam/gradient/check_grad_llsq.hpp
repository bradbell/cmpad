// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef XAM_GRADIENT_CHECK_GRAD_LLSQ_HPP
# define XAM_GRADIENT_CHECK_GRAD_LLSQ_HPP
/*
{xrst_begin check_grad_llsq.hpp}

Check C++ Gradient of Determinant
#################################

Syntax
******
| |tab| ``# include "check_grad_llsq.hpp"``
| |tab| *ok* = ``check_grad_llsq`` ( *grad_llsq* )


Prototype
*********
{xrst_literal
   // BEGIN PROTOTYPE
   // END PROTOTYPE
}

grad_llsq
*********
Is a :ref:`cpp_fun_obj-name`
object that computes the gradient for the ref:`cpp_llsq_obj-name` algorithm.

ok
**
is true (false) if the gradient passes (fails) the test.

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end  check_grad_llsq.hpp}
*/
// BEGIN C++
# include <cmpad/uniform_01.hpp>
# include <cmpad/near_equal.hpp>

// BEGIN PROTOTYPE
template <class Gradient>
bool check_grad_llsq( Gradient& grad_llsq )
// END PROTOTYPE
{  //
   // ok
   bool ok = true;
   //
   // rel_error
   double rel_error = 500. * std::numeric_limits<double>::epsilon();
   //
   // near_equal
   using cmpad::near_equal;
   //
   // n_arg, n_other
   size_t n_arg   = 4;
   size_t n_other = 10;
   //
   // time_setup
   for(bool time_setup : { true, false } )
   {  //
      // option
      cmpad::option_t option;
      option.n_arg       = n_arg;
      option.n_other     = n_other;
      option.time_setup  = time_setup;
      //
      // grad_llsq
      grad_llsq.setup(option);
      //
      // x
      // values in the matrix in row major order
      cmpad::vector<double> x(option.n_arg);
      cmpad::uniform_01(x);
      //
      // g
      cmpad::vector<double> g = grad_llsq(x);
      //
      // i
      for(size_t i = 0; i < n_arg; ++i)
      {  //
         // dobj_dxi
         double dobj_dxi = 0.0;
         //
         for(size_t j = 0; j < n_other; ++j)
         {  //
            // tj
            double tj;
            if( n_other == 1 )
               tj = 0.0;
            else
               tj = -1.0 + 2.0 * double(j) / double(n_other-1);
            //
            // qj
            double qj = std::copysign(1.0, tj);
            if( tj == 0.0 )
               qj = 0.0;
            //
            // rj
            double mj = x[0] + x[1] * tj + x[2] * tj*tj + x[3] * tj*tj*tj;
            double rj = mj - qj;
            //
            // tj_i
            double tj_i = 1;
            for(size_t k = 0; k < i; ++k)
               tj_i *= tj;
            //
            // dobj_dxi
            dobj_dxi += rj * tj_i;
         }
         // ok
         ok &= near_equal(g[i], dobj_dxi, rel_error);
      }
   }
   return ok;
}
// END C++

# endif
