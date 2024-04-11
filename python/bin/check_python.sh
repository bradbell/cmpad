#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e -u
# ----------------------------------------------------------------------------
program='python/bin/check_python.sh'
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
# -----------------------------------------------------------------------------
#
# python_env
echo "source bin/environment.sh build_type=$build_type"
source bin/environment.sh
#
# pytest
pytest $(ls python/xam/*.py | sed -e '/\/temp.py$/d' )
#
echo "$program: OK"
exit 0
