# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# example_list
# examples that to not require AD packages
SET(example_list
   an_ode.cpp
   csv_read.cpp
   csv_speed.cpp
   csv_write.cpp
   det_by_minor.cpp
   det_of_minor.cpp
   fun_obj.cpp
   fun_speed.cpp
   near_equal.cpp
   runge_kutta.cpp
   uniform_01.cpp
)
#
# example_list
# examples that require AD packages
FOREACH(package adept adolc autodiff clad cppad cppad_jit cppadcg sacado)
   IF( ${cmpad_has_${package}} )
      SET(example_list ${example_list} gradient/${package}.cpp)
   ENDIF( )
ENDFOREACH( )
#
# xam
# All the ./*.cpp files should be included below and in ../test/xam.cpp
ADD_LIBRARY(xam SHARED ${example_list} )
SET_TARGET_PROPERTIES(xam PROPERTIES SOVERSION ${cmpad_VERSION})
#
IF( ${cmpad_has_clad} )
   TARGET_COMPILE_OPTIONS(xam PUBLIC -fplugin=${clad_LINK_LIBRARIES})
ENDIF( )
