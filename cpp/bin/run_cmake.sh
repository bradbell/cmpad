#! /usr/bin/env bash
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
set -u -e
# ---------------------------------------------------------------------------
program='cpp/bin/run_cmake.sh'
if [ "$0" != "$program" ]
then
   echo "$program: must be executed the top source directory"
   exit 1
fi
#
# compiler, build_type, vector
compiler=''
build_type='release'
code_generator=""
vector='-D cmpad_vector=std'
verbose='-D CMAKE_VERBOSE_MAKEFILE=NO'
for (( i=1; i<=$#; i++ ))
do
   i_th_command_line_argument="${!i}"
   case "$i_th_command_line_argument" in

      --clang)
      compiler='-D CMAKE_CXX_COMPILER=clang++'
      ;;

      --debug)
      build_type='debug'
      ;;

      --ninja)
      code_generator='-G Ninja'
      ;;

      --cppad_vector)
      vector='-D cmpad_vector=cppad'
      ;;

      --verbose)
      verbose='-D CMAKE_VERBOSE_MAKEFILE=YES'
      ;;

      *)
      echo "usage: $program \\"
      echo '   [--clang] \'
      echo '   [--debug] \'
      echo '   [--ninja ] \ '
      echo '   [--cppad_vector] \'
      echo '   [--verbose]'
      exit 0
      ;;

   esac
done
# -----------------------------------------------------------------------------
# cpp/build
if [ ! -e cpp/build ]
then
   mkdir -p cpp/build
fi
cd cpp/build
if [ -e CMakeCache.txt ]
then
   rm CMakeCache.txt
fi
#
# PKG_CONFIG_PATH
# if this is empty, cmake uses local install of packages
PKG_CONFIG_PATH=''
#
# for_sacado
for_sacado='-DCMAKE_CXX_EXTENSIONS=Off'
#
# cmake_build_type
cmake_build_type="-D CMAKE_BUILD_TYPE=$build_type"
#
# make
echo cmake -B . -S .. \
   $code_generator $for_sacado $compiler $cmake_build_type $vector $verbose
cmake -B . -S .. \
   $code_generator $for_sacado $compiler $cmake_build_type $vector $verbose
# -----------------------------------------------------------------------------
echo 'bin/run_cmake.sh: OK'
exit 0
