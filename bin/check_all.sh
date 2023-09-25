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
if [ $# != 0 ]
then
   echo 'usage: bin/check_all.sh: does not expect arugments'
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
# -----------------------------------------------------------------------------
list=$( ls bin/check_* | sed -e '/check_all.sh/d' )
for check in $list
do
   $check
done
bin/run_xrst.sh
bin/python/check_python.sh
bin/cpp/check_cpp.sh
# -----------------------------------------------------------------------------
echo 'bin/check_all.sh: OK'
exit 0
