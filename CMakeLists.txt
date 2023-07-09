# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# cmake requires version
CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
#
#
# PROGECT_NAME, PROJECT_SOURCE_DIR, PROJECT_BINARY_DIR
PROJECT(cmpad)
#
# Locate GTest
FIND_PACKAGE(GTest REQUIRED)
#
# include directories
INCLUDE_DIRECTORIES(
   ${PROJECT_SOURCE_DIR}/include
   ${GTEST_INCLUDE_DIRS}
)
#
# link libraries
LINK_LIBRARIES(${GTEST_LIBRARIES} pthread)
#
# CMAKE_CXX_STANDARG
SET(CMAKE_CXX_STANDARD 14)
#
# subdirectories
ADD_SUBDIRECTORY(example)
