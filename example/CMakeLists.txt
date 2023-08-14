# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# soversion: year.month.day
SET(soversion 2023.8.14)
#
# xam
ADD_LIBRARY(xam SHARED
   uniform_01.cpp
   csv_read.cpp
   csv_write.cpp
)
SET_TARGET_PROPERTIES(xam PROPERTIES SOVERSION ${soversion})
