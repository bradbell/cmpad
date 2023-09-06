#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
# bash function that echos and executes a command
echo_eval() {
	echo $*
	eval $*
}
# -----------------------------------------------------------------------------
set -u -e
if [ "$#" != 0 ]
then
   echo 'bin/check_version.sh: expects no arguments'
   exit 1
fi
if [ "$0" != 'bin/check_version.sh' ]
then
   echo 'bin/check_version.sh: must be executed from its parent directory'
   exit 1
fi
# -------------------------------------------------------------------------
check_version() {
   sed "$1" -f temp.sed > temp.out
   if ! diff "$1" temp.out > /dev/null
   then
      mv temp.out "$1"
      echo_eval git diff "$1"
   else
      rm temp.out
   fi
}
# -------------------------------------------------------------------------
# version
version=$(date +%Y.%m.%d | sed -e 's|\.0*|.|g')
#
# temp.sed
cat << EOF > temp.sed
s|soversion *[0-9][0-9][.][0-9][0-9]*[.][0-9][0-9]*|soversion $version|
s|cmpad-[0-9]\\{4\\}[.][0-9][0-9]*[.][0-9][0-9]*|cmpad-$version|
EOF
#
# c++/lib/CMakeLists.txt
check_version c++/lib/CMakeLists.txt
#
# cmpad.xrst
check_version cmpad.xrst
#
# temp.sed
# rm temp.sed
# -------------------------------------------------------------------------
echo 'check_version.sh: OK'
exit 0
