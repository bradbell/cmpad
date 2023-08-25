// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# include <boost/test/unit_test.hpp>
# include <cmpad/algo/det_by_minor.hpp>
# include <cmpad/cppad/gradient.hpp>
# include "check_speed_det.hpp"

BOOST_AUTO_TEST_CASE(fun_speed_cppad)
{  cmpad::cppad::gradient<cmpad::det_by_minor> grad_det;
   check_speed_det(grad_det);
}
