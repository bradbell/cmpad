// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
// This test suite runs each of the tests in ../xam/*.cpp

# include <ctime>
# include <boost/test/unit_test.hpp>
# include <cmpad/configure.hpp>

// CMPAD_TEST_EXAMPLE
# define CMPAD_TEST_EXAMPLE(name) \
   extern bool xam_##name(void); \
   BOOST_AUTO_TEST_SUITE( xam ) \
   BOOST_AUTO_TEST_CASE(name) \
   {  BOOST_CHECK( xam_##name () == true ); } \
   BOOST_AUTO_TEST_SUITE_END()

// BEGIN_SORT_THIS_LINE_PLUS_1
CMPAD_TEST_EXAMPLE(an_ode)
CMPAD_TEST_EXAMPLE(csv_read)
CMPAD_TEST_EXAMPLE(csv_speed)
CMPAD_TEST_EXAMPLE(csv_write)
CMPAD_TEST_EXAMPLE(det_by_minor)
CMPAD_TEST_EXAMPLE(det_of_minor)
CMPAD_TEST_EXAMPLE(fun_obj)
CMPAD_TEST_EXAMPLE(fun_speed)
CMPAD_TEST_EXAMPLE(llsq_obj)
CMPAD_TEST_EXAMPLE(near_equal)
CMPAD_TEST_EXAMPLE(runge_kutta)
CMPAD_TEST_EXAMPLE(uniform_01)
// END_SORT_THIS_LINE_MINUS_1
//
# if CMPAD_HAS_ADEPT
CMPAD_TEST_EXAMPLE(gradient_adept)
# endif
# if CMPAD_HAS_ADOLC
CMPAD_TEST_EXAMPLE(gradient_adolc)
# endif
# if CMPAD_HAS_AUTODIFF
CMPAD_TEST_EXAMPLE(gradient_autodiff)
# endif
# if CMPAD_HAS_CODI
CMPAD_TEST_EXAMPLE(gradient_codi)
# endif
# if CMPAD_HAS_CPPAD
CMPAD_TEST_EXAMPLE(cppad_llsq_obj)
CMPAD_TEST_EXAMPLE(gradient_cppad)
# endif
# if CMPAD_HAS_CPPAD_JIT
CMPAD_TEST_EXAMPLE(gradient_cppad_jit)
# endif
# if CMPAD_HAS_CPPADCG
CMPAD_TEST_EXAMPLE(gradient_cppadcg)
# endif
# if CMPAD_HAS_SACADO
CMPAD_TEST_EXAMPLE(gradient_sacado)
# endif
