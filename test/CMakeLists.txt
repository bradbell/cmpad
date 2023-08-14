# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# CHECK_LIBRARY_EXISTS
INCLUDE(CheckLibraryExists)
#
# test
ADD_EXECUTABLE(test
   test.cpp
   ../example/csv_read.cpp
   ../example/csv_speed.cpp
   ../example/csv_write.cpp
   ../example/det_by_minor.cpp
   ../example/det_of_minor.cpp
   ../example/fun_speed.cpp
   ../example/gradient.cpp
   ../example/uniform_01.cpp
)
LINK_DIRECTORIES( ${CMAKE_BINARY_DIR}/src )
#
# For Sacado
ADD_DEFINITIONS("-DCPPAD_SACADO_SPEED -DRAD_AUTO_AD_Const")
#
TARGET_LINK_LIBRARIES(test cmpad )
