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
#
# package_list
package_list='adolc, autodiff, cppad, cppadcg, sacado, eigen, or argparse'
#
if [ "$0" != 'bin/get_package.sh' ]
then
   echo 'bin/get_package.sh: must be executed from its parent directory'
   exit 1
fi
if [ "$#" != 2 ]
then
   echo 'usage: bin/get_package package build_type'
   echo "where package is $package_list"
   echo 'and build_type is debug or release'
   exit 1
fi
#
# package, build_type
package="$1"
build_type="$2"
if [ "$build_type" != 'debug' ] && [ "$build_type" != 'release' ]
then
   echo 'bin/package.sh: package build_type'
   echo 'build_type is not debug or release'
   exit 1
fi
# ---------------------------------------------------------------------------
#
# top_srcdir
top_srcdir=$(pwd)
#
# prefix
# $top_srcdir/CMakeLists.txt assumes that prefix setting is as below
prefix=$top_srcdir/build/prefix
#
# argparse_file
argparse_file="$prefix/include/argparse/argparse.hpp"
# ---------------------------------------------------------------------------
if [ ! -e "$argparse_file" && "$pacakge" != 'argparse' ]
then
   # cmpad main program requires argparse
   bin/get_package.sh argparse $build_type
fi
if [ "$package" == autodiff ]
then
   # autodiff requires eigen
   bin/get_package.sh eigen $build_type
fi
if [ "$package" == cppadcg ]
then
   # cpapdcg requires cppad
   bin/get_package.sh cppad $build_type
fi
#
# PKG_CONFIG_PATH
PKG_CONFIG_PATH="$PKG_CONFIG_PATH:$prefix/lib/pkgconfig"
PKG_CONFIG_PATH="$PKG_CONFIG_PATH:$prefix/lib64/pkgconfig"
PKG_CONFIG_PATH="$PKG_CONFIG_PATH:$prefix/share/pkgconfig"
export PKG_CONFIT_PATH
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

   argparse)
   web_page='https://github.com/p-ranav/argparse.git'
   version='master'
   configure='cmake -S .. -B .'
   configure="$configure -D CMAKE_INSTALL_PREFIX=$prefix"
   ;;


   autodiff)
   web_page='https://github.com/autodiff/autodiff.git'
   version='main'
   configure='cmake -S .. -B .'
   configure="$configure -D CMAKE_INSTALL_PREFIX=$prefix"
   for name in TESTS PYTHON EXAMPLES DOCS
   do
      configure="$configure -D AUTODIFF_BUILD_$name=OFF"
   done
   ;;

   cppad)
   web_page='https://github.com/coin-or/CppAD.git'
   version='master'
   configure='cmake -S .. -B .'
   configure="$configure -D cppad_prefix=$prefix"
   configure="$configure -D cppad_cxx_flags='-D CPPAD_DEBUG_AND_RELEASE'"
   ;;

   cppadcg)
   web_page="https://github.com/joaoleal/CppADCodeGen.git"
   version='master'
   configure='cmake -S .. -B .'
   configure="$configure -D CMAKE_INSTALL_PREFIX=$prefix"
   configure="$configure -D EIGEN3_INCLUDE_DIR=$prefix/include"
   configure="$configure -D GOOGLETEST_GIT=ON"
   ;;

   eigen)
   web_page='https://gitlab.com/libeigen/$package.git'
   version='master'
   configure='cmake -S .. -B .'
   configure="$configure -D CMAKE_INSTALL_PREFIX=$prefix"
   ;;

   sacado)
   web_page='https://github.com/trilinos/Trilinos/archive/refs/tags'
   version='trilinos-release-14-4-0'
   configure='cmake -S .. -B .'
   configure="$configure -D Trilinos_ENABLE_Sacado=ON"
   configure="$configure -D Sacado_ENABLE_TESTS=OFF"
   configure="$configure -D CMAKE_INSTALL_PREFIX=$prefix"
   configure="$configure -D BUILD_SHARED_LIBS=ON"
   # -D Trilinos_INSTALL_LIB_DIR=$prefix/$libdir
   ;;

   *)
   echo 'bin/get_package.sh: package build_type'
   echo "package is not $package_list"
   exit 1
   ;;

esac
if [ "$package" == 'adolc' ]
then
   if [ "$build_type" == 'debug' ]
   then
      configure="$configure --enable-debug"
   fi
else
   configure="$configure -D CMAKE_BUILD_TYPE=$build_type"
fi
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
if echo $web_page | grep '\.git' > /dev/null
then
   package_top_srcdir="$package.git"
else
   package_top_srcdir="$package"
fi
echo $package_top_srcdir
#
# other_build
if [ $build_type == 'debug' ]
then
   other_build='release'
else
   other_build='debug'
fi
#
# configure_flag
configured_flag="external/$package.$build_type"
# -----------------------------------------------------------------------------
if [ -e "external/$package.$other_build" ]
then
   rm "external/$package.$other_build"
fi
if [ -e "$configured_flag" ]
then
   echo "Skipping configuration because following file exists:"
   echo $configured_flag
   echo_eval cd external/$package_top_srcdir/build
   echo_eval make -j $n_job install
   #
   if [ "$package" == 'eigen' ]
   then
      if [ -e $prefix/include/Eigen ]
      then
         rm $prefix/include/Eigen
      fi
      ln -s $prefix/include/eigen3/Eigen $prefix/include/Eigen
   fi
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
if echo $web_page | grep '\.git' > /dev/null
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
   if [ "$package_top_srcdir" != 'sacado' ]
   then
      echo 'bin/get_package.sh: program error'
      exit 1
   fi
   if [ ! -e sacado ]
   then
      if [ -e "$version.tar.gz" ]
      then
         rm $version.tar.gz
      fi
      wget $web_page/$version.tar.gz
      tar -xzf "$version.tar.gz"
      mv Trilinos-$version sacado
   fi
   cd sacado
fi
#
# patch source
if [ "$package" == 'adolc' ]
then
   sed -i ADOL-C/src/uni5_for.c -e 's|for (\([ij]\)=|for(int \1=|'
fi
#
# build
if [ ! -d build ]
then
   echo_eval mkdir build
fi
echo_eval cd build
#
# CMakeCache.txt
if [ -e CMakeCache.txt ]
then
   rm CMakeCache.txt
fi
#
# configure
echo_eval $configure
#
# configured_flag
echo_eval touch $top_srcdir/$configured_flag
#
# install
echo_eval make -j $n_job install
if [ "$package" == 'eigen' ]
then
   if [ -e $prefix/include/Eigen ]
   then
      rm $prefix/include/Eigen
   fi
   ln -s $prefix/include/eigen3/Eigen $prefix/include/Eigen
fi
if [ "$package" == 'argparse' ]
then
   if [ ! -e "$argparse_file" ]
   then
      echo "bin/get_package.sh $package $build_type"
      echo 'after install cannot find'
      echo "$argparse_file"
      exit 1
   fi
fi
#
# -----------------------------------------------------------------------------
echo "bin/get_package.sh $package $build_type: OK"
exit 0
