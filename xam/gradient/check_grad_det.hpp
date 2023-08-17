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
# include <cmpad/det_of_minor.hpp>
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
   // size
   for(size_t size = 3; size < 5; ++size)
   {
      // option
      cmpad::option_t option;
      option.size       = size;
      option.time_setup = static_cast<bool>(size % 2);
      //
      // grad_det
      grad_det.setup(option);
      //
      // x
      // values in the matrix in row major order
      cmpad::vector<double> x(size * size);
      cmpad::uniform_01(x);
      //
      // g
      cmpad::vector<double> g = grad_det(x);
      //
      // r, c
      // index values corresponding to computing determinat of entire matrix
      cmpad::vector<size_t> r(size+1), c(size+1);
      for(size_t i = 0; i < size; ++i)
      {  r[i] = i+1;
         c[i] = i+1;
      }
      r[size] = 0;
      c[size] = 0;
      //
      // i, j
      // for each row and column index in the matrix
      for(size_t i = 0; i < size; i++)
      {  for(size_t j = 0; j < size; j++)
         {
            // r, c
            // minor with row i and column j removed
            if( i == 0 )
               r[size] = 1;
            else
               r[i-1] = i+1;
            if( j == 0 )
               c[size] = 1;
            else
               c[j-1] = j+1;
            //
            // det_minor
            // determinant of minor corresponding to (i, j) removed
            double det_minor = cmpad::det_of_minor(x, size, size-1, r, c);
            //
            // check
            // derivative of determinant with respect matrix element (i, j)
            double check = det_minor;
            if( (i + j) % 2 == 1 )
               check = - det_minor;
            //
            // ok
            ok &= near_equal(g[ i * size + j ], check, rel_error, x);
            //
            // r, c
            // restore to computing determinant of entire matrix
            if( i == 0 )
               r[size] = 0;
            else
               r[i-1] = i;
            if( j == 0 )
               c[size] = 0;
            else
               c[j-1] = j;
         }
      }
   }
   return ok;
}
// END C++

# endif
