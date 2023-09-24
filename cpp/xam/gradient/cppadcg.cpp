// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin xam_gradient_cppadcg.cpp}

Example and Test of Gradient Using cppadcg
##########################################

check_grad_det
**************
see :ref:`check_grad_det.hpp-name`

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end  xam_gradient_cppadcg.cpp}
*/
// BEGIN C++
# include <cmpad/configure.hpp>
# include <cmpad/algo/det_by_minor.hpp>
# include <cmpad/algo/an_ode.hpp>
# include <cmpad/cppadcg/gradient.hpp>
# include "check_grad_det.hpp"
# include "check_grad_ode.hpp"

bool xam_gradient_cppadcg(void)
{  //
   // ok
   bool ok = true;
   //
   // ok
   {  cmpad::cppadcg::gradient<cmpad::det_by_minor> grad_det;
      ok &= check_grad_det(grad_det);
   }
   //
   // ok
   {  cmpad::cppadcg::gradient<cmpad::an_ode> grad_ode;
      ok &= check_grad_ode(grad_ode);
   }
   //
   return ok;
}
// END C++
