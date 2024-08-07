// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef XAM_GRADIENT_CHECK_GRAD_DET_HPP
# define XAM_GRADIENT_CHECK_GRAD_DET_HPP
/*
{xrst_begin check_grad_det.hpp}

Check C++ Gradient of Determinant
#################################

Syntax
******
| |tab| ``# include "check_grad_det.hpp"``
| |tab| *ok* = ``check_grad_det`` ( *grad_det* )


Prototype
*********
{xrst_literal
   // BEGIN PROTOTYPE
   // END PROTOTYPE
}

grad_det
********
Is a :ref:`cpp_fun_obj-name`
object that computes the gradient for the ref:`cpp_det_by_minor-name` algorithm.

ok
**
is true (false) if the gradient passes (fails) the test.

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end  check_grad_det.hpp}
*/
// BEGIN C++
# include <cmpad/uniform_01.hpp>
# include <cmpad/near_equal.hpp>
# include <cmpad/algo/det_of_minor.hpp>

// BEGIN PROTOTYPE
template <class Gradient>
bool check_grad_det( Gradient& grad_det )
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
   // set_minor
   // r and c corresponding to minor with row i and column j removed
   auto set_minor = []
   (cmpad::vector<size_t>& r, cmpad::vector<size_t>& c, size_t i, size_t j)
   {  assert( r.size() == c.size() );
      size_t ell = r.size() - 1;
      assert( i < ell );
      assert( j < ell );
      //
      for(size_t k = 0; k < ell; ++k)
      {  r[k] = k+1;
         c[k] = k+1;
      }
      r[ell] = 0;
      c[ell] = 0;
      //
      if( i == 0 )
         r[ell] = 1;
      else
         r[i-1] = i+1;
      if( j == 0 )
         c[ell] = 1;
      else
         c[j-1] = j+1;
   };
   //
   // ell
   for(size_t ell = 3; ell < 5; ++ell)
   {
      // option
      cmpad::option_t option;
      option.n_arg       = ell * ell;
      option.n_other     = 0;
      option.time_setup = static_cast<bool>(ell % 2);
      //
      // grad_det
      grad_det.setup(option);
      //
      // x
      // values in the matrix in row major order
      cmpad::vector<double> x(ell * ell);
      cmpad::uniform_01(x);
      //
      // g
      cmpad::vector<double> g = grad_det(x);
      //
      // r, c
      // index values corresponding to computing determinat of entire matrix
      cmpad::vector<size_t> r(ell+1), c(ell+1);
      //
      // i, j
      // for each row and column index in the matrix
      for(size_t i = 0; i < ell; i++)
      {  for(size_t j = 0; j < ell; j++)
         {
            // r, c
            set_minor(r, c, i, j);
            //
            // det_minor
            // determinant of minor corresponding to (i, j) removed
            double det_minor = cmpad::det_of_minor(x, ell, ell-1, r, c);
            //
            // check
            // derivative of determinant with respect matrix element (i, j)
            double check = det_minor;
            if( (i + j) % 2 == 1 )
               check = - det_minor;
            //
            // ok
            ok &= near_equal(g[ i * ell + j ], check, rel_error, x);
            //
         }
      }
   }
   return ok;
}
// END C++

# endif
