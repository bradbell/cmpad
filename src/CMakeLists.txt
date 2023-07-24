# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# soversion: year.month.day
SET(soversion 23.7.24)
#
# cmpad
ADD_LIBRARY(cmpad SHARED
   csv_read.cpp
   uniform_01.cpp
)
SET_TARGET_PROPERTIES(cmpad PROPERTIES SOVERSION ${soversion})
