// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin xam_gradient_codi.cpp}

Example and Test of Gradient Using codi
#######################################

check_grad_det
**************
see :ref:`check_grad_det.hpp-name`

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end  xam_gradient_codi.cpp}
*/
// BEGIN C++
# include <cmpad/configure.hpp>
# include <cmpad/algo/det_by_minor.hpp>
# include <cmpad/algo/an_ode.hpp>
# include <cmpad/algo/llsq_obj.hpp>
# include <cmpad/codi/gradient.hpp>
# include "check_grad_det.hpp"
# include "check_grad_ode.hpp"
# include "check_grad_llsq.hpp"

bool xam_gradient_codi(void)
{  //
   // ok
   bool ok = true;
   //
   // ok
   cmpad::codi::gradient<cmpad::det_by_minor> grad_det;
   ok &= check_grad_det(grad_det);
   //
   // ok
   cmpad::codi::gradient<cmpad::an_ode> grad_ode;
   ok &= check_grad_ode(grad_ode);
   //
   // ok
   cmpad::codi::gradient<cmpad::llsq_obj> grad_llsq;
   ok &= check_grad_llsq(grad_llsq);
   //
   return ok;
}
// END C++
