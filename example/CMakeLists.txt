# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# CHECK_LIBRARY_EXISTS
INCLUDE(CheckLibraryExists)
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
#
# Sacado_LIBRARIIES
FOREACH(dir lib lib64)
   IF( IS_DIRECTORY "${cmpad_install_prefix}/${dir}/cmake/Trilinos" )
      SET(Trilinos_DIR "${cmpad_install_prefix}/${dir}/cmake/Trilinos" )
   ENDIF( )
ENDFOREACH( )
FIND_PACKAGE(Trilinos CONFIG)
#
# For Sacado
ADD_DEFINITIONS("-DCPPAD_SACADO_SPEED -DRAD_AUTO_AD_Const")
#
TARGET_LINK_LIBRARIES(example cmpad ${Sacado_LIBRARIES} )
