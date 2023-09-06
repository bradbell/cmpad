# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# print_variable
MACRO(print_variable variable)
   MESSAGE(STATUS "${variable} = ${${variable}}" )
ENDMACRO( )
#
# cmake requires version
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
#
# PROGECT_NAME, PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR
PROJECT(cmpad)
#
# cmpad_install_prefix
SET(cmpad_install_prefix "${PROJECT_SOURCE_DIR}/../build/prefix" )
#
# PKG_CONFIG_PATH
IF( "$ENV{PKG_CONFIG_PATH}" STREQUAL "" )
   SET(tmp "")
   FOREACH(dir lib lib64 share)
      IF( EXISTS ${cmpad_install_prefix}/${dir}/pkgconfig )
         IF( NOT tmp STREQUAL "" )
            SET(tmp "${tmp};")
         ENDIF( )
         SET(tmp "${tmp}${cmpad_install_prefix}/${dir}/pkgconfig")
      ENDIF( )
   ENDFOREACH( )
   SET(ENV{PKG_CONFIG_PATH} "${tmp}")
ENDIF( )
MESSAGE(STATUS "PKG_CONFIG_PATH = $ENV{PKG_CONFIG_PATH}")
#
# pkg_check_modules
FIND_PACKAGE(PkgConfig REQUIRED)
#
# Boost_UNIT_TEST_FRAMEWORK_LIBRARY
FIND_PACKAGE(Boost REQUIRED unit_test_framework)
#
# ${package}_LINK_LIBRARIES
FOREACH(package adolc cppad cppadcg)
   pkg_check_modules(${package} ${package})
   IF( ${package}_LINK_LIBRARIES )
      print_variable( ${package}_LINK_LIBRARIES )
   ELSE( )
      SET(${package}_LINK_LIBRARIES "")
   ENDIF( )
ENDFOREACH( )
#
# adept_LINK_LIBRARIES
SET(adept_LINK_LIBRARIES "")
FOREACH(dir lib lib64)
   FOREACH(ext dll dylib so)
      SET(tmp "${cmpad_install_prefix}/${dir}/libadept.${ext}" )
      IF( EXISTS ${tmp} )
         SET( adept_LINK_LIBRARIES "${tmp}" )
      ENDIF( )
   ENDFOREACH( )
ENDFOREACH( )
print_variable( adept_LINK_LIBRARIES )
#
# sacado_LINK_LIBRARIES
FOREACH(dir lib lib64)
   IF( IS_DIRECTORY "${cmpad_install_prefix}/${dir}/cmake/Trilinos" )
      SET(Trilinos_DIR "${cmpad_install_prefix}/${dir}/cmake/Trilinos" )
   ENDIF( )
ENDFOREACH( )
FIND_PACKAGE(Trilinos CONFIG)
IF( Trilinos_FOUND )
   SET(sacado_LINK_LIBRARIES "${Sacado_LIBRARIES}")
ELSE( )
   SET(sacado_LINK_LIBRARIES "")
ENDIF( )
print_variable( sacado_LINK_LIBRARIES )
#
# Special compiler flag that makes Sacado faster
IF( NOT ( "${sacado_LINK_LIBRARIES}" STREQUAL "" ) )
   ADD_DEFINITIONS( "-DRAD_AUTO_AD_Const" )
ENDIF( )
#
# include directories
INCLUDE_DIRECTORIES(
   ${PROJECT_SOURCE_DIR}/include
   ${cmpad_install_prefix}/include
)
#
# link libraries
LINK_LIBRARIES(
   ${adept_LINK_LIBRARIES}
   ${adolc_LINK_LIBRARIES}
   ${cppad_LINK_LIBRARIES}
   ${sacado_LINK_LIBRARIES}
   ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)
#
# CMAKE_CXX_STANDARG
SET(CMAKE_CXX_STANDARD 17)
#
# include/cmpad/configure.hpp
# cmpad_has_${package}
ADD_SUBDIRECTORY(include/cmpad)
#
# other subdirectories
ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(xam)
ADD_SUBDIRECTORY(test)
