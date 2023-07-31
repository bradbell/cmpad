# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# cmpad_has_${package}
FOREACH(package adolc cppad sacado)
   IF( "${${package}_LINK_LIBRARIES}" STREQUAL "" )
      SET( cmpad_has_${package} 0 )
   ELSE( )
      SET( cmpad_has_${package} 1 )
   ENDIF( )
   print_variable(cmpad_has_${package})
ENDFOREACH( )
IF( EXISTS "${cmpad_install_prefix}/include/autodiff/forward/real.hpp" )
   SET( cmpad_has_autodiff 1 )
ELSE( )
   SET( cmpad_has_autodiff 0 )
ENDIF( )
print_variable(cmpad_has_autodiff)
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
