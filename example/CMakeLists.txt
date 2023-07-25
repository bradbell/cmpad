# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# example
ADD_EXECUTABLE(example
   example.cpp
   csv_read.cpp
   csv_speed.cpp
   csv_write.cpp
   det_by_minor.cpp
   det_of_minor.cpp
   fun_speed.cpp
   gradient.cpp
   uniform_01.cpp
)
LINK_DIRECTORIES( ${CMAKE_BINARY_DIR}/src )
TARGET_LINK_LIBRARIES(example cmpad)
