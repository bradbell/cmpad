# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# cmake requires version
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
#
# PROGECT_NAME, PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR
PROJECT(cmpad)
#
# cmpad_install_prefix
SET(cmpad_install_prefix "${PROJECT_SOURCE_DIR}/build/prefix" )
#
# PKG_CONFIG_PATH
SET(ENV{PKG_CONFIG_PATH} "${cmpad_install_prefix}/lib/pkgconfig")
MESSAGE(STATUS "PKG_CONFIG_PATH = $ENV{PKG_CONFIG_PATH}")
#
# pkg_check_modules
FIND_PACKAGE(PkgConfig REQUIRED)
#
# Boost_UNIT_TEST_FRAMEWORK_LIBRARY
FIND_PACKAGE(Boost REQUIRED unit_test_framework)
#
# cppad_LINK_LIBRARIES
pkg_check_modules(cppad REQUIRED cppad)
IF( cppad_LINK_LIBRARIES )
   MESSAGE(STATUS "cppad_LINK_LIBRARIES = ${cppad_LINK_LIBRARIES}")
ELSE( )
   SET(cppad_LINK_LIBRARIES "")
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
   ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
   ${cppad_LINK_LIBRARIES}
)
#
# CMAKE_CXX_STANDARG
SET(CMAKE_CXX_STANDARD 14)
#
# subdirectories
ADD_SUBDIRECTORY(include/cmpad)
ADD_SUBDIRECTORY(example)
