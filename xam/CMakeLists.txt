# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# soversion: year.month.day
SET(soversion 2023.8.14)
#
# xam
# All the ./*.cpp files should be included below and in ../test/xam.cpp
ADD_LIBRARY(xam SHARED
   an_ode.cpp
   csv_read.cpp
   csv_speed.cpp
   csv_write.cpp
   det_by_minor.cpp
   det_of_minor.cpp
   fun_obj.cpp
   fun_speed.cpp
   gradient/adolc.cpp
   gradient/autodiff.cpp
   gradient/cppad.cpp
   gradient/cppad_jit.cpp
   gradient/cppadcg.cpp
   gradient/sacado.cpp
   near_equal.cpp
   runge_kutta.cpp
   uniform_01.cpp
)
SET_TARGET_PROPERTIES(xam PROPERTIES SOVERSION ${soversion})
