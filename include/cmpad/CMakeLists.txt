# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# cmpad_has_${package}
FOREACH(package adolc cppad cppadcg sacado)
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
# cmpad_compiler_is_clang
# cmpad_compiler_is_gnu
# cmpad_compiler_is_msvc
FOREACH(name clang gnu msvc )
   STRING( TOLOWER "${CMAKE_CXX_COMPILER_ID}" compiler )
   IF( "${compiler}" STREQUAL "${name}" )
      SET(cmpad_compiler_is_${name} 1)
   ELSE( )
      SET(cmpad_compiler_is_${name} 0)
   ENDIF( )
ENDFOREACH( )
#
# cmpad_has_cppadcg
# cmpad_has_cppad_jit
IF( NOT cmpad_compiler_is_clang )
   IF( NOT cmpad_comlier_is_gnu )
      SET( cmpad_has_cppadcg 0 )
      IF( NOT cmpad_compiler_is_msvc )
         SET( cmpad_has_cppad_jit 0 )
      ENDIF( )
   ENDIF( )
ENDIF( )
#
# cmpad_vector_<name>
# for <name> equal to cppad or std
SET(cmpad_vector std CACHE STRING
   "Is cmpad::vector a cppad or std vector ?"
)
SET(cmpad_vector_cppad 0)
SET(cmpad_vector_std   0)
IF( ${cmpad_vector} STREQUAL "cppad" )
   SET(cmpad_vector_cppad 1)
ELSEIF( ${cmpad_vector} STREQUAL "std" )
   SET(cmpad_vector_std 1)
ELSE( )
   MESSAGE(FATAL_ERROR "cmpad_vector is not cppad, or std")
ENDIF( )
#
CONFIGURE_FILE(
   ${CMAKE_CURRENT_SOURCE_DIR}/configure.hpp.in
   ${CMAKE_CURRENT_SOURCE_DIR}/configure.hpp
)
