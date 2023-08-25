# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# test_list
# tests that to not depend on AD packages
SET(test_list
   test.cpp
   csv_speed.cpp
   xam.cpp
)
#
# test_list
# tests that depend on AD packages
FOREACH(package adolc autodiff cppad cppad_jit cppadcg sacado)
   IF( ${cmpad_has_${package}} )
      SET(test_list ${test_list} ${package}.cpp)
   ENDIF( )
ENDFOREACH( )
#
# test
ADD_EXECUTABLE(test ${test_list})
#
TARGET_LINK_LIBRARIES(test cmpad xam)
