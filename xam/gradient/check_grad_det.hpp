// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef XAM_GRADIENT_CHECK_GRAD_DET_HPP
# define XAM_GRADIENT_CHECK_GRAD_DET_HPP
/*
{xrst_begin check_grad_det}

Check Gradient of Determinant
#############################

Syntax
******

| ``# include "check_grad_det.hpp"``
| *ok* = check_grad_det( *grad_det* )


Prototype
*********
{xrst_literal
   // BEGIN PROTOTYPE
   // END PROTOTYPE
}

grad_det
********
Is a :ref:`gradient-name` object for a determinant algorithm.

ok
**
is true (false) if the gradient passes (fails) the test.

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end  check_grad_det}
*/
// BEGIN C++
# include <cmpad/uniform_01.hpp>
# include <cmpad/near_equal.hpp>
# include <cmpad/algo/det_of_minor.hpp>
# include <cmpad/gradient.hpp>

// BEGIN PROTOTYPE
template <class Algo>
bool check_grad_det( cmpad::gradient<Algo>& grad_det )
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
   for(size_t n_arg = 3; n_arg < 5; ++n_arg)
   {
      // option
      cmpad::option_t option;
      option.n_arg       = n_arg;
      option.time_setup = static_cast<bool>(n_arg % 2);
      //
      // grad_det
      grad_det.setup(option);
      //
      // x
      // values in the matrix in row major order
      cmpad::vector<double> x(n_arg * n_arg);
      cmpad::uniform_01(x);
      //
      // g
      cmpad::vector<double> g = grad_det(x);
      //
      // r, c
      // index values corresponding to computing determinat of entire matrix
      cmpad::vector<size_t> r(n_arg+1), c(n_arg+1);
      for(size_t i = 0; i < n_arg; ++i)
      {  r[i] = i+1;
         c[i] = i+1;
      }
      r[n_arg] = 0;
      c[n_arg] = 0;
      //
      // i, j
      // for each row and column index in the matrix
      for(size_t i = 0; i < n_arg; i++)
      {  for(size_t j = 0; j < n_arg; j++)
         {
            // r, c
            // minor with row i and column j removed
            if( i == 0 )
               r[n_arg] = 1;
            else
               r[i-1] = i+1;
            if( j == 0 )
               c[n_arg] = 1;
            else
               c[j-1] = j+1;
            //
            // det_minor
            // determinant of minor corresponding to (i, j) removed
            double det_minor = cmpad::det_of_minor(x, n_arg, n_arg-1, r, c);
            //
            // check
            // derivative of determinant with respect matrix element (i, j)
            double check = det_minor;
            if( (i + j) % 2 == 1 )
               check = - det_minor;
            //
            // ok
            ok &= near_equal(g[ i * n_arg + j ], check, rel_error, x);
            //
            // r, c
            // restore to computing determinant of entire matrix
            if( i == 0 )
               r[n_arg] = 0;
            else
               r[i-1] = i;
            if( j == 0 )
               c[n_arg] = 0;
            else
               c[j-1] = j;
         }
      }
   }
   return ok;
}
// END C++

# endif
