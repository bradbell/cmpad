// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_VECTOR_HPP
# define CMPAD_VECTOR_HPP
/*
{xrst_begin vector}
{xrst_spell
   std
   vec
   cmake
}

The cmpad Vector Template Type
##############################

Syntax
******

| ``# include <cmpad/vector.hpp>``
| ``cmpad::vector`` < *Scalar* > *vec*

Scalar
******
is the type of the elements of *vec* .

vec
***
is a cmpad vector.

std
***
If ``-D cmpad_vector=std``
is specified on the cmake command line,
then ``cmpad::vector`` is ``std::vector`` .

cppad
*****
If ``-D cmpad_vector=cppad``
is specified on the cmake command line,
then ``cmpad::vector`` is ``CppAD::vector`` .

{xrst_end vector}
*/

# include <cmpad/configure.hpp>

# if CMPAD_VECTOR_STD
# include <vector>
namespace cmpad { using std::vector; }
# endif

# if CMPAD_VECTOR_CPPAD
# include <cppad/utility/vector.hpp>
namespace cmpad { using CppAD::vector; }
# endif


# endif
