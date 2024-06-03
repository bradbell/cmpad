// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin xam_gradient_sacado.cpp}

Example and Test of Gradient Using sacado
#########################################

check_grad_det
**************
see :ref:`check_grad_det.hpp-name`

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end  xam_gradient_sacado.cpp}
*/
// BEGIN C++
# include <cmpad/configure.hpp>
# include <cmpad/algo/det_by_minor_vec.hpp>
# include <cmpad/algo/an_ode_vec.hpp>
# include <cmpad/algo/llsq_obj_vec.hpp>
# include <cmpad/sacado/gradient_vec.hpp>
# include "check_grad_det.hpp"
# include "check_grad_ode.hpp"
# include "check_grad_llsq.hpp"

bool xam_gradient_sacado(void)
{  //
   // ok
   bool ok = true;
   //
   // ok
   cmpad::sacado::gradient_vec<cmpad::det_by_minor_vec> grad_det;
   ok &= check_grad_det(grad_det);
   //
   // ok
   cmpad::sacado::gradient_vec<cmpad::an_ode_vec> grad_ode;
   ok &= check_grad_ode(grad_ode);
   //
   // ok
   cmpad::sacado::gradient_vec<cmpad::llsq_obj_vec> grad_llsq;
   ok &= check_grad_llsq(grad_llsq);
   //
   return ok;
}
// END C++
