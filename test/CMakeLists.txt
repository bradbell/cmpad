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
   fun_speed.cpp
   csv_speed.cpp
   xam.cpp
)
#
# For Sacado
# 2023-08-16: The definition below causes a crash in
#  test/test --run_test=example/gradient_sacado
# ADD_DEFINITIONS("-DRAD_AUTO_AD_Const")
#
TARGET_LINK_LIBRARIES(test cmpad xam)
