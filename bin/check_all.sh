#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e -u
# -----------------------------------------------------------------------------
# bash function that echos and executes a command
echo_eval() {
	echo $*
	eval $*
}
# -----------------------------------------------------------------------------
#
if [ $# != 1 ]
then
   echo 'usage: bin/check_all.sh (debug|release)'
   exit 1
fi
if [ "$0" != 'bin/check_all.sh' ]
then
   echo 'bin/check_all.sh: must execute this script from its parent directory'
   exit 1
fi
if [ ! -e './.git' ]
then
   echo 'bin/check_all.sh: cannot find ./.git'
   exit 1
fi
if [ "$1" != 'debug' ] && [ "$1" != 'release' ]
then
   echo 'usage: bin/check_all.sh (debug|release)'
   exit 1
fi
build_type="$1"
# -----------------------------------------------------------------------------
list=$( ls bin/check_* | sed -e '/check_all.sh/d' )
for check in $list
do
   $check
done
# -----------------------------------------------------------------------------
# run_cmake.sh
bin/run_cmake.sh $build_type
#
# build
cd build
#
# make
make
#
# example
{ example/example --log_level=test_suite --no_color_output 2>&1 ; }\
   | sed -e 's|.*Entering test case ||' -e '/Leaving test case/d'
#
# -----------------------------------------------------------------------------
echo 'bin/check_all.sh: OK'
exit 0
