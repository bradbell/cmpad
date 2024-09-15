#! /usr/bin/env bash
set -u -e
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
# echo_eval
echo_eval() {
   echo $*
   eval $*
}
# -----------------------------------------------------------------------------
if [ "$#" != 0 ]
then
   echo 'bin/check_if_0.sh: expects no arguments'
   exit 1
fi
if [ "$0" != 'bin/check_if_0.sh' ]
then
   echo 'bin/check_if_0.sh: must be executed from its parent directory'
   exit 1
fi
# -------------------------------------------------------------------------
if git grep '^# *if *0'
then
   echo '"# if 0" is used for temporary testing and should not be checked in'
   exit 1
fi
# -------------------------------------------------------------------------
echo 'check_if_0.sh: OK'
exit 0
