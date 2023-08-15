// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin fun_speed.cpp}

gradient: Example and Test
##########################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end  fun_speed.cpp}
*/
// BEGIN C++
# include <boost/test/unit_test.hpp>
# include <cmpad/configure.hpp>
# include <cmpad/det_by_minor.hpp>
# include <cmpad/adolc/gradient.hpp>
# include <cmpad/cppad/gradient.hpp>
# include <cmpad/cppad_jit/gradient.hpp>
# include <cmpad/sacado/gradient.hpp>
# include <cmpad/autodiff/gradient.hpp>
# include <cmpad/fun_speed.hpp>

namespace {
   template <class Algo>
   void check_speed_det(
      const std::string&     name     ,
      cmpad::gradient<Algo>& grad_det )
   {  //
      // message
      BOOST_TEST_MESSAGE( "   " + name );
      //
      // option
      cmpad::option_t option;
      //
      // time_min
      // minimum time for test in seconds
      double time_min = 0.2;
      //
      // previous_rate, size
      double previous_rate = 0.0;
      for(size_t ell = 5; ell < 8; ++ell)
      {  //
         // option
         option.size       = ell;
         option.time_setup = false;
         //
         // grad_det
         grad_det.setup(option);
         //
         // rate
         double rate  = cmpad::fun_speed(grad_det, option, time_min);
         //
         // ratio
         // number of floating operations goes up by a factor of ell
         double ratio = previous_rate / (ell * rate);
         //
         if( ! (previous_rate == 0.0 || (0.1 < ratio && ratio < 3.0) ) )
         {  std::cout << name << ": ell = " << ell << ": ratio = ";
            std::cout << std::to_string(ratio) << "\n";
         }
         if( previous_rate != 0.0 )
            BOOST_CHECK( 0.1 < ratio && ratio < 3.0 );
         previous_rate = rate;
      }
   }
}

BOOST_AUTO_TEST_CASE(fun_speed)
{  //
   // det_by_minor
   using cmpad::det_by_minor;
   //
# if CMPAD_HAS_ADOLC
   cmpad::adolc::gradient<det_by_minor>       adolc_grad_det;
   check_speed_det("adolc grad_det",          adolc_grad_det);
# endif
   //
# if CMPAD_HAS_CPPAD
   //
   // cppad
   cmpad::cppad::gradient<det_by_minor>       cppad_grad_det;
   check_speed_det("cppad grad_det",          cppad_grad_det);
   //
   // cppad_jit
   /* fails when cppad build with debugging
   cmpad::cppad_jit::gradient<det_by_minor>    cppad_jit_grad_det;
   check_speed_det("cppad_jit grad_det",       cppad_jit_grad_det);
   */
# endif
   //
# if CMPAD_HAS_SACADO
   cmpad::sacado::gradient<det_by_minor>      sacado_grad_det;
   check_speed_det("sacado grad_det",         sacado_grad_det);
# endif
   //
# if CMPAD_HAS_AUTODIFF
   cmpad::autodiff::gradient<det_by_minor>    autodiff_grad_det;
   check_speed_det("autodiff grad_det",       autodiff_grad_det);
# endif
}
// END C++
