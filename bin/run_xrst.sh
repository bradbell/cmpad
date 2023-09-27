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
if [ $# != 0 ]
then
   echo 'usage: bin/run_xrst.sh'
   exit 1
fi
if [ "$0" != 'bin/run_xrst.sh' ]
then
   echo 'bin/run_xrst.sh: must execute this script from its parent directory'
   exit 1
fi
if [ -e build/html ]
then
   echo_eval rm -r build/html
fi
echo_eval xrst --local_toc --html_theme sphinx_rtd_theme
echo 'bin/run_xrst.sh: OK'
exit 0
