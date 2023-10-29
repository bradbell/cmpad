#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e -u
# -----------------------------------------------------------------------------
# {xrst_begin get_package.sh}
# {xrst_spell
#     sh
#     eigen
#     srcdir
#     pwd
#     rm
# }
# {xrst_comment_ch #}
#
# Getting Optional C++ Packages
# #############################
# This shell script can be used to install optional AD packages
# that cmpad can test. In addition, it can be used to install packages
# required by these optional packages.
#
# Syntax
# ******
# ``cpp/bin/get_package.sh`` *build_type* *package_1* [ *package_2* [ ... ] ]
# ``cpp/bin/get_package.sh`` *build_type* ``all``
#
# build_type
# ==========
# This is either ``debug`` or ``release`` and determines if libraries,
# built while installing the packages, are debug or release versions.
#
# all
# ===
# If *package_1* is ``all`` , all of the possible packages,
# except fastad and clad (thoes under construction) are installed.
# In this case, *package_2* .. must not be present on the command line.
#
# package_j
# =========
# The packages *package_1* , *package_2*, ...
# are the list of packages that will be installed.
# This list must have at least one package ; i.e.,
# *package_2* , *package_3* , ... are optional.
#
# package_set
# ***********
# This is the set of the packages (so far) that can be installed:
# {xrst_code sh}
package_set='{ adept, adolc, autodiff, clad, cppad, cppad_jit, cppadcg'
package_set="$package_set,  fastad, eigen, sacado }"
# {xrst_code}
# If one of these packages is not install, it will not be included in
# the cmpad testing.
#
# .. _adept:     https://github.com/rjhogan/Adept-2
# .. _adolc:     https://github.com/coin-or/ADOL-C
# .. _autodiff:  https://github.com/autodiff/autodiff
# .. _clad:      https://github.com/vgvassilev/clad
# .. _cppad:     https://github.com/coin-or/CppAD
# .. _cppad_jit: https://github.com/coin-or/CppAD
# .. _cppadcg:   https://github.com/joaoleal/CppADCodeGen
# .. _fastad:    https://github.com/JamesYang007/FastAD
# .. _sacado:    https://trilinos.github.io/sacado.html
#
# .. csv-table::
#  :widths: auto
#  :header-rows: 1
#
#  Web Site,      Implemented
#  `adept`_,      :ref:`gradient <adept_gradient.hpp-name>`
#  `adolc`_,      :ref:`gradient <adolc_gradient.hpp-name>`
#  `autodiff`_,   :ref:`gradient <autodiff_gradient.hpp-name>`
#  `clad`_,       Under Construction
#  `cppad`_,      :ref:`gradient <cppad_gradient.hpp-name>`
#  `cppad_jit`_,  :ref:`gradient <cppad_jit_gradient.hpp-name>`
#  `cppadcg`_,    :ref:`gradient <cppadcg_gradient.hpp-name>`
#  `fastad`_,     Under Construction
#  `sacado`_,     :ref:`gradient <sacado_gradient.hpp-name>`
#
# #. Implemented is the list of cmpad derivatives implemented so far
# #. Installing autodiff or fastad also installs eigen.
# #. Installing cppad or cppad_jit has the same effect.
# #. Installing cppadcg also installs cppad.
#
# top_srcdir
# **********
# The working directory, when this command is executed, must be the
# top source directory for cmpad; i.e.,
# the directory containing the ``.git`` directory for cmpad.
# {xrst_code sh}
top_srcdir=$(pwd)
# {xrst_code}
#
# {xrst_comment
#     $top_srcdir/CMakeLists.txt assumes that prefix setting is as below
# }
# prefix
# ******
# This is the prefix for the packages installed by ``cpp/bin/get_package.sh`` :
# {xrst_code sh}
prefix=$top_srcdir/cpp/build/prefix
# {xrst_code}
# Note that this is a local install and does not require any special
# permissions.
#
# external
# ********
# The source code, and corresponding builds, for all installed packages
# is in the *top_srcdir*\ ``/external`` directory.
# Thus you can remove the *prefix* directory and reinstall a new list
# of packages quickly.
# If you have trouble with a particular *package* ,
# and ``external/``\ *package*\ .\ *build_type* exists,
# you may want to try the following:
#
# | |tab| ``rm external/``\ *package*\ .\ *build_type*
# | |tab| ``bin/cpp/get_package`` *build_type* *package*
#
# {xrst_end get_package.sh}
# -----------------------------------------------------------------------------
# echo_eval
# bash function that echos and executes a command
echo_eval() {
	echo $*
   eval $*
}
# -----------------------------------------------------------------------------
program='cpp/bin/get_package.sh'
#
if [ ! -d '.git' ]
then
   echo "$program: must be executed from cmpad top soruce directory"
   exit 1
fi
if [ "$#" -lt 2 ]
then
   echo "$program: found $# arugments and expected 2 or more"
   echo
   echo "usage: $program build_type all"
   echo "usage: $program build_type package_1 [package_2 [...] ]"
   echo 'where build_type is debug or release and package_j is one of'
   echo "$package_set"
   exit 1
fi
#
# build_type
build_type="$1"
if [ "$build_type" != 'debug' ] && [ "$build_type" != 'release' ]
then
   echo
   echo "usage: $program build_type all"
   echo "usage: $program build_type package_1 [package_2 [...] ]"
   echo "build_type=$build_type is not debug or release"
   exit 1
fi
#
# package
package="$2"
#
# all
if [ "$package" == 'all' ]
then
   if [ "$#" -gt 2 ]
   then
      echo "usage: $program build_type all"
      echo 'package_2, ..., must not be present when package_1 is all'
      exit 1
   fi
   # exclude clad and fastad
   package_list='adept adolc autodiff cppadcg sacado'
   echo_eval $program $build_type $package_list
   echo "$program $package $build_type all: OK"
   exit 0
fi
#
# package
while [ "$#" -gt 2 ]
do
   package="$2"
   if [ "$package" == 'all' ]
   then
      echo "usage: $program program error"
      exit 1
   fi
   echo_eval $program $build_type $package
   shift
done
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
   configure="$configure -D LLVM_EXTERNAL_LIT=$(which lit)"
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
   echo "package = $package is not one of the following:"
   echo "$package_set"
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
   echo_eval git pull
   echo_eval git checkout --quiet $version
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
