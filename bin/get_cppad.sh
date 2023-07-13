#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# -----------------------------------------------------------------------------
# package
package='cppad'
#
# top_srcdir
top_srcdir=$(pwd)
#
# prefix
# $top_srcdir/CMakeLists.txt assumes that prefix setting is as below
prefix=$top_srcdir/build/prefix
#
# web_page
web_page="https://github.com/coin-or/$package.git"
#
# version
version=master
#
# configure
configure='cmake -S .. -B . -D CMAKE_BUILD_TYPE=release'
configure="$configure -D cppad_prefix=$prefix"
configure="$configure -D cppad_cxx_flags='-D CPPAD_DEBUG_AND_RELEASE'"
# -----------------------------------------------------------------------------
set -e -u
if [ "$0" != "bin/get_$package.sh" ]
then
   echo "bin/get_$package.sh: must be executed from its parent directory"
   exit 1
fi
if [ $# != 0 ]
then
   echo "bin/get_$package.sh expects no arguments"
   exit 1
fi
# -----------------------------------------------------------------------------
# echo_eval
# bash function that echos and executes a command
echo_eval() {
	echo $*
	eval $*
}
# -----------------------------------------------------------------------------
#
# n_job
if which nproc > /dev/null
then
   n_job=$(nproc)
else
   n_job=$(sysctl -n hw.ncpu)
fi
#
# configured_flag
configured_flag="external/$package-$version.configured"
#
if [ -e "$configured_flag" ]
then
   echo "Skipping configuration because following file exists:"
   echo $configured_flag
   echo_eval cd external/$package.git/build
   echo_eval make -j $n_job install
   echo "bin/get_$package.sh: OK"
   exit 0
fi
# -----------------------------------------------------------------------------
#
# external
if [ ! -d external ]
then
   echo_eval mkdir external
fi
echo_eval cd external
#
# $package.git
if [ ! -d "$package.git" ]
then
   echo_eval git clone $web_page $package.git
fi
echo_eval cd $package.git
echo_eval git reset --hard
echo_eval git checkout --quiet $version
#
# build
if [ ! -d build ]
then
   echo_eval mkdir build
fi
echo_eval cd build
#
# configure
echo_eval $configure
#
# configured_flag
echo_eval touch $top_srcdir/$configured_flag
#
# install
echo_eval make -j $n_job install
# -----------------------------------------------------------------------------
echo "bin/get_$package.sh: OK"
exit 0
