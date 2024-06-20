// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_CPPAD_CPPAD_HPP
# define CMPAD_CPPAD_CPPAD_HPP
/*
{xrst_begin include_cppad}
{xrst_spell
   Gen
}

Including CppAD and CppADCodeGen
################################

Discussion
**********
The inclusion of ``cppad.hpp`` is make complicated by the fact that all the
user defined AD base types must be defined before it is included.
This is further complicated by the fact that the ``cppadcg.hpp`` file
incudes ``cppad.hpp`` .


Source Code
***********
{xrst_spell_off}
{xrst_code hpp} */
// This include file does nothing when the CppAD pakage has not been installed
# if CMPAD_HAS_CPPAD
//
// define utilities to make it easier to define an AD base type
# include <cppad/base_require.hpp>
//
// define the valvector AD base type
# include <cppad/example/valvector/class.hpp>
//
// If the CppADCodeGen package has been installed,
// define the template class CppAD::cg_CG for use as an AD base type
# if CMPAD_HAS_CPPADCG
# include <cppad/cg/cppadcg.hpp>
# endif
//
// include cppad.hpp (if not already included by cppadcg.hpp)
# include <cppad/cppad.hpp>
//
// define the valvector summation atomic function (requires cppad.hpp)
# include <cppad/example/valvector/sum.hpp>
//
# endif
/* {xrst_code}
{xrst_spell_on}

{xrst_end include_cppad}
*/

# endif
