# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# cmake requires version
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
#
# PROGECT_NAME, PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR
PROJECT(cmpad)
#
# cmpad_install_prefix
SET(cmpad_install_prefix "${PROJECT_SOURCE_DIR}/build/prefix" )
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
FOREACH(package adolc cppad)
   #
   # ${package}_LINK_LIBRARIES
   pkg_check_modules(${package} REQUIRED ${package})
   IF( ${package}_LINK_LIBRARIES )
      MESSAGE(STATUS "${package}_LINK_LIBRARIES = ${${package}_LINK_LIBRARIES}")
   ELSE( )
      SET(${package}_LINK_LIBRARIES "")
   ENDIF( )
ENDFOREACH( )
#
# Sacado_LIBRARIIES
FOREACH(dir lib lib64)
   IF( IS_DIRECTORY "${cmpad_install_prefix}/${dir}/cmake/Trilinos" )
      SET(Trilinos_DIR "${cmpad_install_prefix}/${dir}/cmake/Trilinos" )
   ENDIF( )
ENDFOREACH( )
FIND_PACKAGE(Trilinos CONFIG)
#
# include directories
INCLUDE_DIRECTORIES(
   ${PROJECT_SOURCE_DIR}/include
   ${cmpad_install_prefix}/include
)
#
# link libraries
LINK_LIBRARIES(
   ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
   ${Sacado_LIBRARIES}
   ${adolc_LINK_LIBRARIES}
   ${cppad_LINK_LIBRARIES}
)
#
# CMAKE_CXX_STANDARG
SET(CMAKE_CXX_STANDARD 17)
#
# subdirectories
ADD_SUBDIRECTORY(include/cmpad)
ADD_SUBDIRECTORY(lib)
ADD_SUBDIRECTORY(example)
