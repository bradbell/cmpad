# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# cmpad_vector_is_<name>
# for <name> equal to boost, cppad, std
SET(cmpad_vector std CACHE STRING
   "Is cmpad::vector a boost, cppad, or std vector ?"
)
SET(cmpad_vector_is_boost 0)
SET(cmpad_vector_is_cppad 0)
SET(cmpad_vector_is_std   0)
IF( ${cmpad_vector} STREQUAL "boost" )
   SET(cmpad_vector_is_boost 1)
ELSEIF( ${cmpad_vector} STREQUAL "cppad" )
   SET(cmpad_vector_is_cppad 1)
ELSEIF( ${cmpad_vector} STREQUAL "std" )
   SET(cmpad_vector_is_std 1)
ELSE( )
   MESSAGE(FATAL_ERROR "cppad_vector is not boost, cppad, or std")
ENDIF( )
#
CONFIGURE_FILE(
   ${CMAKE_CURRENT_SOURCE_DIR}/configure.hpp.in
   ${CMAKE_CURRENT_SOURCE_DIR}/configure.hpp
)
