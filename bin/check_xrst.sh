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
   echo 'usage: bin/check_xrst.sh'
   exit 1
fi
if [ "$0" != 'bin/check_xrst.sh' ]
then
   echo 'bin/check_xrst.sh: must execute this script from its parent directory'
   exit 1
fi
echo_eval xrst --page_source --local_toc --html_theme sphinx_rtd_theme
echo 'bin/check_xrst.sh: OK'
exit 0
