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
   xam.cpp
   ../xam/csv_speed.cpp
   ../xam/det_by_minor.cpp
   ../xam/det_of_minor.cpp
   ../xam/fun_speed.cpp
   ../xam/gradient.cpp
)
#
# For Sacado
ADD_DEFINITIONS("-DRAD_AUTO_AD_Const")
#
TARGET_LINK_LIBRARIES(test cmpad xam)
