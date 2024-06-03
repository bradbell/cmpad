# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
# test_list
# tests that to not depend on AD packages
SET(test_list
   test.cpp
   xam.cpp
   none.cpp
)
#
# test_list
# tests that depend on AD packages
FOREACH(package adept adolc autodiff cppadcg cppad_jit sacado cppad)
   SET(package_cpp "${CMAKE_CURRENT_BINARY_DIR}/${package}.cpp" )
   IF( ${cmpad_has_${package}} )
      CONFIGURE_FILE( package.cpp.in ${package_cpp} )
      SET(test_list ${test_list} ${package_cpp} )
   ENDIF( )
ENDFOREACH( )
#
# INCLUDE_DIRECRTORIES
# so source files in binary directory find include files in source directory
INCLUDE_DIRECTORIES(
   ${CMAKE_CURRENT_SOURCE_DIR}
)
#
# test
ADD_EXECUTABLE(test ${test_list})
#
TARGET_LINK_LIBRARIES(test cmpad xam)
