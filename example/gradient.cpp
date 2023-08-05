// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin gradient.cpp}

gradient: Example and Test
##########################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end  gradient.cpp}
*/
// BEGIN C++
# include <boost/test/unit_test.hpp>
# include <cmpad/configure.hpp>
# include <cmpad/uniform_01.hpp>
# include <cmpad/det_by_minor.hpp>
# include <cmpad/adolc/gradient.hpp>
# include <cmpad/cppad/gradient.hpp>
# include <cmpad/sacado/gradient.hpp>
# include <cmpad/autodiff/gradient.hpp>
# include <cmpad/cppad_jit/gradient.hpp>

namespace {
   template <class Algo>
   void check_grad_det(
      const std::string&     name     ,
      cmpad::gradient<Algo>& grad_det )
   {  //
      //
      // tt
      namespace tt = boost::test_tools;
      //
      // message
      BOOST_TEST_MESSAGE( "   " + name );
      //
      // size
      for(size_t size = 3; size < 5; ++size)
      {
         //
         // option
         cmpad::option_t option;
         option.size = size;
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
         cmpad::vector<size_t> r(size+1), c(size+1);
         for(size_t i = 0; i < size; ++i)
         {  r[i] = i+1;
            c[i] = i+1;
         }
         r[size] = 0;
         c[size] = 0;
         //
         // i, j
         for(size_t i = 0; i < size; i++)
         {  for(size_t j = 0; j < size; j++)
            {
               // r, c
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
               double check = det_minor;
               if( (i + j) % 2 == 1 )
                  check = - det_minor;
               //
               BOOST_TEST( g[ i * size + j ] == check , tt::tolerance(1e-7) );
               //
               // r, c
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
   }
}

BOOST_AUTO_TEST_CASE(Gradient)
{  //
   // det_by_minor
   using cmpad::det_by_minor;
   //
# if CMPAD_HAS_ADOLC
   cmpad::adolc::gradient<det_by_minor>     adolc_grad_det;
   check_grad_det("adolc gradient",         adolc_grad_det);
# endif
   //
# if CMPAD_HAS_CPPAD
   //
   // cppad
   cmpad::cppad::gradient<det_by_minor>     cppad_grad_det;
   check_grad_det("cppad gradient",         cppad_grad_det);
   //
   // cppad_jit
   /*
   This test iis failing
   cmpad::cppad_jit::gradient<det_by_minor> cppad_jit_grad_det;
   check_grad_det("cppad_jit gradient",     cppad_jit_grad_det);
   */
# endif
   //
# if CMPAD_HAS_SACADO
   cmpad::sacado::gradient<det_by_minor>    sacado_grad_det;
   check_grad_det("sacado gradient",        sacado_grad_det);
# endif
   //
# if CMPAD_HAS_AUTODIFF
   cmpad::autodiff::gradient<det_by_minor>  autodiff_grad_det;
   check_grad_det("autodiff gradient",      autodiff_grad_det);
# endif
}
// END C++
