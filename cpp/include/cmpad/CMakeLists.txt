# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
# cmpad_has_${package}
# for package = adept, adolc, clad, cppad, cppadcg, sacado, cppad_jit
#
FOREACH(package adept adolc clad cppad cppadcg sacado)
   IF( "${${package}_LINK_LIBRARIES}" STREQUAL "" )
      SET( cmpad_has_${package} 0 )
   ELSE( )
      SET( cmpad_has_${package} 1 )
   ENDIF( )
ENDFOREACH( )
#
# cmpad_has_xad
IF( EXISTS "${cmpad_install_prefix}/include/XAD/XAD.hpp" )
   SET( cmpad_has_xad 1 )
ELSE( )
   SET( cmpad_has_xad 0 )
ENDIF( )
#
# cmpad_has_codi
IF( EXISTS "${cmpad_install_prefix}/include/codi.hpp" )
   SET( cmpad_has_codi 1 )
ELSE( )
   SET( cmpad_has_codi 0 )
ENDIF( )
#
# cmpad_has_autodiff
IF( EXISTS
   "${cmpad_install_prefix}/include/autodiff/forward/real.hpp" )
   SET( cmpad_has_autodiff 1 )
ELSE( )
   SET( cmpad_has_autodiff 0 )
ENDIF( )
#
# cmpad_compiler_is_clang
# cmpad_compiler_is_gnu
# cmpad_compiler_is_msvc
STRING( TOLOWER "${CMAKE_CXX_COMPILER_ID}" compiler )
FOREACH(name clang gnu msvc )
   IF( "${compiler}" STREQUAL "${name}" )
      SET(cmpad_compiler_is_${name} 1)
   ELSE( )
      SET(cmpad_compiler_is_${name} 0)
   ENDIF( )
ENDFOREACH( )
IF( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang" )
   SET(cmpad_compiler_is_clang 1)
ENDIF( )
#
# cmpad_has_cppadcg
# cmpad_has_cppad_jit
SET(cmpad_has_cppad_jit ${cmpad_has_cppad})
IF( NOT cmpad_compiler_is_clang )
   IF( NOT cmpad_compiler_is_gnu )
      SET( cmpad_has_cppadcg 0 )
      IF( NOT cmpad_compiler_is_msvc )
         SET( cmpad_has_cppad_jit 0 )
      ENDIF( )
   ENDIF( )
ENDIF( )
# ---------------------------------------------------------------------------
# cmpad_vector_${name}
# for name = cppad, std
#
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
IF( cmpad_vector_cppad AND NOT cmpad_has_cppad )
   MESSAGE(FATAL_ERROR "cmpad_vector is cppad but cppad is not installed.")
ENDIF( )
# ---------------------------------------------------------------------------
#
CONFIGURE_FILE(
   ${CMAKE_CURRENT_SOURCE_DIR}/configure.hpp.in
   ${CMAKE_CURRENT_SOURCE_DIR}/configure.hpp
)
# ---------------------------------------------------------------------------
# cmpad_has_${package} PARENT_SCOPE
FOREACH(package
   adept adolc autodiff clad codi cppad cppad_jit cppadcg sacado xad
)
   print_variable( cmpad_has_${package} )
   SET(cmpad_has_${package} ${cmpad_has_${package}} PARENT_SCOPE)
ENDFOREACH( )
