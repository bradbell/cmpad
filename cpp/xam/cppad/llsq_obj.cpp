// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ----------------------------------------------------------------------------

/*
{xrst_begin xam_cppad_llsq_obj.cpp}

Example and Test of CppAD Special llsq_obj
##########################################

{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end xam_cppad_llsq_obj.cpp}
*/
// BEGIN C++
# include <cmpad/cppad/llsq_obj.hpp>
# include <cmpad/near_equal.hpp>
# include <cppad/example/valvector/class.hpp>

bool xam_cppad_llsq_obj(void)
{  // ok
   bool ok = true;
   //
   // scalar_type
   typedef CppAD::AD<valvector> scalar_type;
   //
   // llsq
   typedef typename cmpad::vector<scalar_type> Vector;
   cmpad::cppad::llsq_obj<Vector>              llsq;
   //
   // n_arg, n_other
   size_t n_arg   = 3;
   size_t n_other = 4;
   //
   // llsq.setup
   cmpad::option_t option;
   option.n_arg   = n_arg;
   option.n_other = n_other;
   llsq.setup(option);
   //
   // ax
   cmpad::vector<double> x(n_arg);
   Vector ax(n_arg);
   for(size_t i = 0; i < n_arg; ++i)
   {  x[i]  = double(i);
      ax[i] = x[i];
   }
   //
   // ay
   const Vector& ay = llsq(ax);
   ok &= ay.size()    == 1;
   //
   // sumsq
   double sumsq = 0.0;
   //
   for(size_t j = 0; j < n_other; ++j)
   {  //
      // t_j
      double t_j = -1.0 + 2.0 * double(j) / double(n_other - 1);
      //
      // q_j
      double q_j = std::copysign( 1.0, t_j );
      if( t_j == 0 )
         q_j = 0.0;
      //
      // r_j
      double m_j = x[0] + x[1] * t_j + x[2] * t_j * t_j;
      double r_j = m_j - q_j;
      //
      // sumsq
      sumsq += r_j * r_j;
   }
   //
   // check
   double check = 0.5 * sumsq;
   //
   // rel_error
   double rel_error = std::numeric_limits<double>::epsilon() * 100.0;
   //
   // ok
   valvector y0 = Value( ay[0] );
   ok &= cmpad::near_equal( y0[0], check, rel_error );
   //
   return ok;
}

// END C++
