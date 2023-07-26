#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e -u
# -----------------------------------------------------------------------------
# echo_eval
# bash function that echos and executes a command
echo_eval() {
	echo $*
   eval $*
}
# -----------------------------------------------------------------------------
if [ "$0" != 'bin/get_package.sh' ]
then
   echo 'bin/get_package.sh: must be executed from its parent directory'
   exit 1
fi
if [ "$#" != 1 ]
then
   echo 'usage: bin/get_package package'
   echo 'where package is adolc, cppad, sacado.'
   exit 1
fi
#
# package
package="$1"
# ---------------------------------------------------------------------------
#
# top_srcdir
top_srcdir=$(pwd)
#
# prefix
# $top_srcdir/CMakeLists.txt assumes that prefix setting is as below
prefix=$top_srcdir/build/prefix
#
# web_page, version, configure
case $package in

   adolc)
   web_page='https://github.com/coin-or/ADOL-C.git'
   version='master'
   configure="--prefix=$prefix --with-colpack=$prefix"
   configure="$configure --enable-static --enable-shared --enable-atrig-erf"
   configure="cd ..; autoreconf -fi; cd build ; ../configure $configure"
   ;;

   cppad)
   web_page='https://github.com/coin-or/CppAD.git'
   version='master'
   configure='cmake -S .. -B . -D CMAKE_BUILD_TYPE=release'
   configure="$configure -D cppad_prefix=$prefix"
   configure="$configure -D cppad_cxx_flags='-D CPPAD_DEBUG_AND_RELEASE'"
   ;;

   sacado)
   web_page='https://github.com/trilinos/Trilinos/archive/refs/tags'
   version='trilinos-release-14-0-0'
   configure='cmake -S .. -B . -D CMAKE_BUILD_TYPE=release'
   configure="$configure -D Trilinos_ENABLE_Sacado=ON"
   configure="$configure -D Sacado_ENABLE_TESTS=OFF"
   configure="$configure -D CMAKE_INSTALL_PREFIX=$prefix"
   # -D Trilinos_INSTALL_LIB_DIR=$prefix/$libdir
   ;;

   *)
   echo 'bin/get_package.sh: package'
   echo 'package is not adolc, or cppad'
   exit 1
   ;;
esac
#
# n_job
if which nproc > /dev/null
then
   n_job=$(nproc)
else
   n_job=$(sysctl -n hw.ncpu)
fi
#
# package_top_srcdir
if echo $web_page | grep '\.git#' > /dev/null
then
   package_top_srcdir="$package.git"
else
   package_top_srcdir="$package"
fi  
#
# configured_flag
configured_flag="external/$package.configured"
# -----------------------------------------------------------------------------
if [ -e "$configured_flag" ]
then
   echo "Skipping configuration because following file exists:"
   echo $configured_flag
   echo_eval cd external/$package_top_srcdir.git/build
   echo_eval make -j $n_job install
   echo "bin/get_package.sh: $package OK"
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
# package top source directory
if echo $web_page | grep '\.git#' > /dev/null
then
   if [ ! -d "$package.git" ]
   then
      echo_eval git clone $web_page $package_top_srcdir
   fi
   echo_eval cd $package_top_srcdir
   echo_eval git reset --hard
   echo_eval git checkout --quiet $version
else
   if [ "$package" != 'sacado' ]
   then
      echo "bin/get_package.sh: $package: expected web_page to end with .git"
      exit 1
   fi
   if [ -e "$version.tar.gz" ]
   then
      rm $version.tar.gz
   fi
   wget $web_page/$version.tar.gz
   tar -xzf "$version.tar.gz"
   mv Trilinos-$version $package_top_srcdir
   cd $package_top_srcdir
fi
#
# patch source
if [ "$package" == 'adolc' ]
then
   sed -i ADOL-C/src/uni5_for.c -e 's|for (\([ij]\)=|for(int \1=|'
fi
if [ "$package" == 'sacado' ]
then
   # see https://github.com/trilinos/Trilinos/issues/11923
   file="packages/teuchos/core/src/Teuchos_BigUIntDecl.hpp"
   if ! grep '^#include <cstdint>' $file > /dev/null
   then
      sed -i $file -e 's|#include <iosfwd>|&\n#include <cstdint>|'
   fi
fi
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
# -----------------------------------------------------------------------------
echo "bin/get_package.sh: $package OK"
exit 0
