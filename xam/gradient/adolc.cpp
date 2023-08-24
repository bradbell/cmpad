// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin xam_gradient_adolc.cpp}

Example and Test of Gradient Using ADOL-C
#########################################

check_grad_det
**************
see :ref:`check_grad_det-name`

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end  xam_gradient_adolc.cpp}
*/
// BEGIN C++
# include <cmpad/configure.hpp>
# include <cmpad/algo/det_by_minor.hpp>
# include <cmpad/adolc/gradient.hpp>
# include "check_grad_det.hpp"

bool xam_gradient_adolc(void)
{  //
   // ok
   bool ok = true;
   //
   // det_by_minor
   using cmpad::det_by_minor;
   //
   // ok
   cmpad::adolc::gradient<det_by_minor> grad_det;
   ok &= check_grad_det(grad_det);
   //
   return ok;
}
// END C++
