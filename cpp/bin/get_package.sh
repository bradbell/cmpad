#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e -u
# -----------------------------------------------------------------------------
# {xrst_begin cpp_get_package}
# {xrst_comment_ch #}
#
# Getting Optional C++ Packages
# #############################
#
# Syntax
# ******
# ``cpp/bin/get_package.sh`` *build_type* *package*
#
# build_type
# ==========
# This is either ``debug`` or ``release`` and determines if libraries,
# built while installing the packages, are debug or release versions.
#
# package
# =======
# The is one of the packages in the following list
# {xrst_literal ,
#     bin/get_package.sh
#     # BEGIN CPP_PACKAGE_LIST, # END CPP_PACKAGE_LIST
#     # BEGIN CPP_PACKAGE_NOT_IMPLEMENTED, # END CPP_PACKAGE_NOT_IMPLEMENTED
#     # BEGIN CPP_PACKAGE_SUPPORT, # END CPP_PACKAGE_SUPPORT
# }
#
# {xrst_end cpp_get_package}
# -----------------------------------------------------------------------------
# echo_eval
# bash function that echos and executes a command
echo_eval() {
	echo $*
   eval $*
}
# -----------------------------------------------------------------------------
#
# program
program='cpp/bin/get_package.sh'
#
# top_srcdir
top_srcdir=$(pwd)
#
if [ ! -d '.git' ]
then
   echo "$program: must be executed from cmpad top soruce directory"
   exit 1
fi
if [ "$#" -ne 2 ]
then
   echo "$program: found $# arugments and expected 2 or more"
   echo
   echo "usage: $program build_type pakcage"
   exit 1
fi
#
# build_type
build_type="$1"
if [ "$build_type" != 'debug' ] && [ "$build_type" != 'release' ]
then
   echo
   echo "$program build_type package"
   echo "build_type=$build_type is not debug or release"
   exit 1
fi
#
# prefix
prefix="$top_srcdir/build/$build_type"
#
# package
package="$2"
#
if [ "$package" == 'cppad_jit' ]
then
   package='cppad'
fi
# ---------------------------------------------------------------------------
#
if [ "$package" == autodiff ] || [ "$package" == 'fastad' ]
then
   # autodiff requires eigen
   $program $build_type eigen
fi
if [ "$package" == cppadcg ]
then
   # cpapdcg requires cppad
   $program $build_type cppad
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

   adept)
   web_page='https://github.com/rjhogan/Adept-2.git'
   version='master'
   configure="--prefix=$prefix"
   configure="$configure --enable-static --enable-shared"
   configure="autoreconf -fi; ./configure $configure"
   ;;

   adolc)
   web_page='https://github.com/coin-or/ADOL-C.git'
   version='master'
   configure="--prefix=$prefix --with-colpack=$prefix"
   configure="$configure --enable-static --enable-shared --enable-atrig-erf"
   configure="cd ..; autoreconf -fi; cd build ; ../configure $configure"
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

   clad)
   web_page='https://github.com/vgvassilev/clad.git'
   version='master'
   configure='cmake -S .. -B .'
   configure="$configure -D CMAKE_INSTALL_PREFIX=$prefix"
   configure="$configure -D CLAD_INCLUDE_DOCS=OFF"
   configure="$configure -D LLVM_EXTERNAL_LIT=$(which lit)"
   ;;

   codipack)
   web_page='https://github.com/scicompkl/codipack.git'
   version='master'
   configure='cmake -S .. -B .'
   configure="$configure -D CMAKE_INSTALL_PREFIX=$prefix"
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
   version='3.4.0'
   configure='cmake -S .. -B .'
   configure="$configure -D CMAKE_INSTALL_PREFIX=$prefix"
   ;;

   fastad)
   web_page='https://github.com/JamesYang007/FastAD.git'
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
   echo "$program: build_type package"
   echo "package = '$package' is not available"
   exit 1
   ;;

esac
#
if [ "$package" == 'adolc' ]
then
   if [ "$build_type" == 'debug' ]
   then
      configure="$configure --enable-debug"
   fi
elif [ "$package" == 'adept' ]
then
   if [ "$build_type" == 'debug' ]
   then
      configure="$configure CXXFLAGS='-g -O0'"
   else
      configure="$configure CXXFLAGS='-DNDEBUG -O2'"
   fi
else
   configure="$configure -D CMAKE_BUILD_TYPE=$build_type"
fi
# ----------------------------------------------------------------------------
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
   if [ "$package" == 'adept' ]
   then
      echo_eval cd external/$package_top_srcdir
   else
      echo_eval cd external/$package_top_srcdir/build
   fi
   echo_eval make -j $n_job install
   #
   if [ "$package" == 'eigen' ]
   then
      for link in Eigen unsupported
      do
         if [ -e $prefix/include/$link ] || [ -L $prefix/include/$link ]
         then
            rm $prefix/include/$link
         fi
         ln -s $prefix/include/eigen3/$link $prefix/include/$link
      done
   fi
   echo "$program: $package OK"
   exit 0
fi
# -----------------------------------------------------------------------------
if [ "$package" == 'clad' ]
then
   missing=""
   for program in lsb_release lit
   do
      if ! which $program > /dev/null
      then
         missing="$missing, $package"
      fi
   done
   if [ "$missing" != '' ]
   then
      missing=$(echo $missing | sed -e 's|, ||')
      echo "$program: $package requires following programs:"
      echo "$missing"
      exit 1
   fi
fi
# -----------------------------------------------------------------------------
#
# external/$package_top_srcdir
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
   if [ "$(git branch --show-current)" != '' ]
   then
      echo_eval git pull
   fi
else
   if [ "$package" != 'sacado' ]
   then
      echo "$program: $package: expected web_page to end with .git"
      exit 1
   fi
   if [ "$package_top_srcdir" != 'sacado' ]
   then
      echo "$program: program error"
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
# -----------------------------------------------------------------------------
# patch source
if [ "$package" == 'adolc' ]
then
   # uni5_for.c
   # missing definition of some loop indices
   sed -i ADOL-C/src/uni5_for.c -e 's|for (\([ij]\)=|for(int \1=|'
   #
   # remove extra print out when ADOLC_DEBUG is defined
   list=$(git grep -l '^ *# *if *defined(ADOLC_DEBUG)')
   for file in $list
   do
      sed -i $file -e 's|^\( *\)# *if *\(defined(ADOLC_DEBUG)\)|\1#if 0 // \2|'
   done
   #
   # remove extra print out when ADOLC_LOCDEBUG ADOLC_DEBUB are defined
   list='ADOL-C/src/storemanager.cpp'
   for file in $list
   do
      sed -i $file \
         -e 's|^\( *\)# *ifdef *\(ADOLC_LOCDEBUG\)|\1#if 0 // \2|' \
         -e 's|^\( *\)# *ifdef *\(ADOLC_DEBUG\)|\1#if 0 // \2|'
   done
fi
if [ "$package" == 'clad' ]
then
   if ! grep 'lib64' CMakeLists.txt
   then
      if [ ! -d build ]
      then
         echo_eval mkdir build
      fi
      cd build
      if ! $configure >& /dev/null
      then
         echo 'configure clad failed. Attempting to patch clad CMakeLists.txt'
         for file in $(find .. -name CMakeLists.txt)
         do
            # does not handel case where libraries are in /lib64/
            sed -i -e "s|/lib/|/lib64/|g" $file
         done
      fi
      cd ..
   fi
fi
# -----------------------------------------------------------------------------
# build
if [ "$package" != 'adept' ]
then
   if [ ! -d build ]
   then
      echo_eval mkdir build
   fi
   echo_eval cd build
fi
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
# -----------------------------------------------------------------------------
echo "$program $package $build_type: OK"
exit 0
