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
   example.cpp
   ../example/csv_speed.cpp
   ../example/det_by_minor.cpp
   ../example/det_of_minor.cpp
   ../example/fun_speed.cpp
   ../example/gradient.cpp
)
#
# For Sacado
ADD_DEFINITIONS("-DRAD_AUTO_AD_Const")
#
TARGET_LINK_LIBRARIES(test cmpad xam)
