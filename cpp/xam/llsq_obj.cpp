// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ----------------------------------------------------------------------------

/*
{xrst_begin xam_llsq_obj.cpp}

Example and Test of llsq_obj
############################

{xrst_toc_hidden
   cpp/xam/cppad/llsq_obj.cpp
}
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end xam_llsq_obj.cpp}
*/
// BEGIN C++
# include <cmpad/algo/llsq_obj.hpp>
# include <cmpad/near_equal.hpp>

bool xam_llsq_obj(void)
{  // ok
   bool ok = true;
   //
   // llsq
   typedef typename cmpad::vector<double> Vector;
   cmpad::llsq_obj<Vector>                llsq;
   //
   // llsq.setup
   cmpad::option_t option;
   option.n_arg   = 3;
   option.n_other = 4;
   llsq.setup(option);
   //
   // x
   Vector x = { 1.0, 2.0, 3.0 };
   //
   // y
   const Vector& y = llsq(x);
   ok &= y.size() == 1;
   //
   // sumsq
   double sumsq = 0;
   //
   for(size_t j = 0; j < option.n_other; ++j)
   {  //
      // t_j
      double t_j = -1.0 + 2.0 * double(j) / double(option.n_other - 1);
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
   ok &= cmpad::near_equal( y[0], check, rel_error );
   //
   return ok;
}

// END C++
