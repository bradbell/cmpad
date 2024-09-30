#! /usr/bin/env bash
set -e -u
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# -----------------------------------------------------------------------------
# echo_eval
echo_eval() {
   echo $*
   eval $*
}
# -----------------------------------------------------------------------------
# program
program='bin/check_all.sh'
#
if [ ! -d .git ]
then
   echo "$program: must be executed from the top source directory"
   exit 1
fi
# build_type
if [ $0 != "$program" ]
then
   echo "usage: $program: (debug|release)"
   exit 1
fi
if [ $# != 1 ]
then
   echo "usage: $program: (debug|release)"
   exit 1
fi
if [ "$1" != 'debug' ] && [ "$1" != 'release' ]
then
   echo 'usage: bin/check_all.sh: (debug|release)'
   exit 1
fi
build_type="$1"
#
# environment.sh
source bin/environment.sh
# -----------------------------------------------------------------------------
list=$( ls bin/check_* | sed -e '/check_all.sh/d' -e '/check_main.py/d'  )
for check in $list
do
   echo_eval $check
done
echo_eval bin/run_xrst.sh
#
echo_eval python/bin/check_python.py $build_type
echo_eval cpp/bin/check_cpp.sh  $build_type
#
echo_eval bin/check_main.py
# -----------------------------------------------------------------------------
echo 'bin/check_all.sh: OK'
exit 0
