#! /usr/bin/env bash
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
set -u -e
if [ $# != 1 ]
then
   echo 'bin/run_cmake.sh (debug|release)'
   exit 1
fi
if [ ! -e 'bin/run_cmake.sh' ]
then
   echo 'bin/run_cmake.sh: must be executed from its parent directory'
   exit 1
fi
if [ "$1" != 'debug' ] && [ "$1" != 'release' ]
then
   echo 'usage: bin/check_all.sh (debug|release)'
   exit 1
fi
build_type="$1"
# -----------------------------------------------------------------------------
# build
if [ ! -e build ]
then
   mkdir build
fi
cd build
if [ -e CMakeCache.txt ]
then
   rm CMakeCache.txt
fi
#
# PKG_CONFIG_PATH
# if this is empty, cmake uses local install of packages
PKG_CONFIG_PATH=''
#
# make
cmake -B . -S .. -D cmpad_vector=cppad -D CMAKE_BUILD_TYPE=$build_type
# -----------------------------------------------------------------------------
echo 'bin/run_cmake.sh: OK'
exit 0
