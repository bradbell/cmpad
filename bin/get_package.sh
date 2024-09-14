#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e -u
# -----------------------------------------------------------------------------
# {xrst_begin get_package}
# {xrst_spell
#     colpack
#     eigen
#     rm
#     srcdir
#     xad
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
# | ``cpp/bin/get_package.sh`` *build_type* *package_1* [ *package_2* [ ... ] ]
# | ``cpp/bin/get_package.sh`` *build_type* ``all``
#
# build_type
# ==========
# This is either ``debug`` or ``release`` and determines if C++ and C
# libraries, built while installing the packages,
# are debug or release versions.
#
# all
# ===
# If *package_1* is ``all`` , all of the possible packages,
# except clad, fastad and xad (those under construction) are installed.
# In this case, *package_2* ... must not be present on the command line.
#
# package_j
# =========
# The packages *package_1* , *package_2*, ...
# are the list of packages that will be installed.
# This list must have at least one package ; i.e.,
# *package_2* , *package_3* , ... are optional.
#
# AD Package List
# ***************
# This is the set of AD packages (so far) that can be installed:
# If one of these packages is not install, it will not be included in
# the cmpad testing.
#
# {xrst_comment BEGIN_SORT_THIS_LINE_PLUS_1}
# .. _adept:     https://github.com/rjhogan/Adept-2
# .. _adolc:     https://github.com/coin-or/ADOL-C
# .. _autodiff:  https://github.com/autodiff/autodiff
# .. _autograd:  https://github.com/HIPS/autograd.git
# .. _clad:      https://github.com/vgvassilev/clad
# .. _codi:      https://github.com/scicompkl/codipack
# .. _cppad:     https://github.com/coin-or/CppAD
# .. _cppad_jit: https://github.com/coin-or/CppAD
# .. _cppad_py:  https://github.com/bradbell/cppad_py
# .. _cppadcg:   https://github.com/joaoleal/CppADCodeGen
# .. _fastad:    https://github.com/JamesYang007/FastAD
# .. _jax:       https://github.com/google/jax
# .. _sacado:    https://trilinos.github.io/sacado.html
# .. _torch:     https://github.com/pytorch/pytorch
# .. _xad:       https://github.com/auto-differentiation/xad
# {xrst_comment END_SORT_THIS_LINE_MINUS_1}
#
# {xrst_comment BEGIN_SORT_THIS_LINE_PLUS_6}
# .. csv-table::
#  :widths: auto
#  :header-rows: 1
#
#  AD Package,    Implementation,                             Language
#  `adept`_,      :ref:`adept_gradient.hpp-name`,             cpp
#  `adolc`_,      :ref:`adolc_gradient.hpp-name`,             cpp
#  `autodiff`_,   :ref:`autodiff_gradient.hpp-name`,          cpp
#  `autograd`_,   :ref:`autograd_gradient.py-name`,           python
#  `codi`_,       :ref:`codi_gradient.hpp-name`,              cpp
#  `cppad_jit`_,  :ref:`cppad_jit_gradient.hpp-name`,         cpp
#  `cppad_py`_,   :ref:`cppad_py_gradient.py-name`,           python
#  `cppad`_,      :ref:`cppad_gradient.hpp-name`,             cpp
#  `cppadcg`_,    :ref:`cppadcg_gradient.hpp-name`,           cpp
#  `jax`_,        :ref:`jax_gradient.py-name`,                python
#  `sacado`_,     :ref:`sacado_gradient.hpp-name`,            cpp
#  `torch`_,      :ref:`torch_gradient.py-name`,              python
# {xrst_comment END_SORT_THIS_LINE_MINUS_1}
# {xrst_suspend}
pkg_available=' adept adolc autodiff autograd codi'
pkg_available="$pkg_available cppad_jit cppad_py cppadcg"
pkg_available="$pkg_available jax torch sacado "
# {xrst_resume}
#
# #. Implementation is the list of cmpad derivatives implementations so far
# #. Installing adolc also installs colpack.
# #. Installing autodiff or fastad also installs eigen.
# #. Installing cppad or cppad_jit has the same effect.
# #. Installing cppadcg also installs cppad.
#
# Under Construction
# ==================
# .. csv-table::
#  :widths: auto
#  :header-rows: 1
#
#  AD Package,    Language
#  `clad`_,       cpp
#  `fastad`_,     cpp
#  `xad`_,        cpp
# {xrst_suspend}
under_construction='clad fastad xad'
# {xrst_resume}
#
# prefix
# ******
# The prefixes for the packages installed by ``bin/get_package.sh`` is
#
# | |tab| *top_srcdir* / ``build`` *build_type*
#
# where *build_type* is ``debug`` or ``release`` .
#
# Virtual Environment
# *******************
# The following commands set the prefix as a virtual environment:
#
# | build_type=\ *build_type*
# | source bin/environment.sh
#
# where *build_type* is ``debug`` or ``release``.
#
# external
# ********
# The source code, and corresponding builds, for all the c++ packages,
# and the python package cppad_py,
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
# {xrst_toc_hidden
#     cpp/bin/get_package.sh
#     python/bin/get_package.py
# }
#
# Language Specific
# *****************
# The scripts :ref:`cpp_get_package-name` and :ref:`py_get_package-name`
# can be used to get individual C++ and Python AD packages.
#
# {xrst_end get_package}
# -----------------------------------------------------------------------------
# echo_eval
# bash function that echos and executes a command
echo_eval() {
   echo $*
   eval $*
}
# -----------------------------------------------------------------------------
program='bin/get_package.sh'
#
if [ ! -d '.git' ]
then
   echo "$program: must be executed from cmpad top source directory"
   exit 1
fi
if [ "$#" -lt 2 ]
then
   echo "$program: found $# arugments and expected 2 or more"
   echo
   echo "usage: $program build_type all"
   echo "usage: $program build_type package_1 [package_2 [...] ]"
   echo 'where build_type is debug or release and package_j is one of'
   echo "$pkg_available $under_construction"
   exit 1
fi
#
# build_type
build_type="$1"
shift
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
package="$1"
#
# all
if [ "$package" == 'all' ]
then
   if [ "$#" -gt 1 ]
   then
      echo "usage: $program build_type all"
      echo 'package_2, ..., must not be present when package_1 is all'
      exit 1
   fi
   pkg_list=$(echo $pkg_available | sed \
      -e 's/\n/ /g'  \
      -e 's/  */ /g' \
   )
   echo_eval $program $build_type $pkg_list
   echo "$program $build_type all: OK"
   exit 0
fi
#
# package
while [ "$#" -ge 1 ]
do
   package="$1"
   shift

   case $package in

   # BEGIN CPP_PACKAGE_SUPPORT
   eigen|colpack)
   # END CPP_PACKAGE_SUPPORT
   echo_eval cpp/bin/get_package.sh $build_type $package
   ;;

   # BEGIN CPP_PACKAGE_NOT_IMPLEMENTED
   clad|fastad|xad)
   # END CPP_PACKAGE_NOT_IMPLEMENTED
   echo_eval cpp/bin/get_package.sh $build_type $package
   ;;

   # BEGIN CPP_PACKAGE_LIST
   adept|adolc|autodiff|codi|cppad_jit|cppad|cppadcg|sacado)
   # END CPP_PACKAGE_LIST
   echo_eval cpp/bin/get_package.sh $build_type $package
   ;;

   # BEGIN PYTHON_PACKAGE_LIST
   autograd|cppad_py|jax|torch)
   # END PYTHON_PACKAGE_LIST
   echo "source bin/environment.sh build_type=$build_type"
   source bin/environment.sh
   echo_eval python/bin/get_package.py $build_type $package
   ;;

   *)
   echo "bin/get_package.sh: package = $package is not available"
   exit 1

   esac
done
echo "$program $build_type $package: OK"
exit 0
