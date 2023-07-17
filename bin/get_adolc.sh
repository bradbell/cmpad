#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# -----------------------------------------------------------------------------
# package
package='adolc'
#
# top_srcdir
top_srcdir=$(pwd)
#
# prefix
# $top_srcdir/CMakeLists.txt assumes that prefix setting is as below
prefix=$top_srcdir/build/prefix
#
# web_page
web_page="https://github.com/coin-or/ADOL-C.git"
#
# version
version=master
#
# configure
flags="--prefix=$prefix --with-colpack=$prefix --libdir=$prefix/$libdir"
flags="$flags --enable-static --enable-shared --enable-atrig-erf"
configure="cd ..; autoreconf -fi; cd build ; ../configure $flags"
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
   echo_eval cp $prefix/pkgconfig/adolc.pc $prefix/lib/pkgconfig/adolc.pc
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
   #
fi
echo_eval cd $package.git
echo_eval git reset --hard
echo_eval git checkout --quiet $version
#
# patch source
sed -i ADOL-C/src/uni5_for.c -e 's|for (\([ij]\)=|for(int \1=|'
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
#
# adolc.pc
if [ ! -d $prefix/lib/pkgconfig ]
then
   mkdir -p $prefix/lib/pkgconfig
fi
cp $prefix/pkgconfig/adolc.pc $prefix/lib/pkgconfig/adolc.pc
# -----------------------------------------------------------------------------
echo "bin/get_$package.sh: OK"
exit 0
