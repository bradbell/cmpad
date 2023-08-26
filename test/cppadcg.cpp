// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# include <boost/test/unit_test.hpp>
# include <cmpad/algo/det_by_minor.hpp>
# include <cmpad/cppadcg/gradient.hpp>
# include "check_speed_det.hpp"

BOOST_AUTO_TEST_SUITE(fun_speed)
BOOST_AUTO_TEST_CASE(cppadcg)
{  cmpad::cppadcg::gradient<cmpad::det_by_minor> grad_det;
   check_speed_det(grad_det);
}
BOOST_AUTO_TEST_SUITE_END()
