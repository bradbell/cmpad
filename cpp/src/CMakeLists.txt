# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
# run_cmpad
ADD_EXECUTABLE(run_cmpad run_cmpad.cpp parse_args.cpp)
TARGET_LINK_LIBRARIES(run_cmpad cmpad)
IF( ${cmpad_has_clad} )
   TARGET_COMPILE_OPTIONS(run_cmpad PUBLIC -fplugin=${clad_LINK_LIBRARIES})
ENDIF( )
