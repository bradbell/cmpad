#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e -u
# ----------------------------------------------------------------------------
program='python/bin/check_python.sh'
prefix='python/build/prefix'
#
if [ ! -d .git ]
then
   echo "$program: must be run from the top soruce directory"
   exit 1
fi
if [ ! -e "$prefix" ]
then
   echo "$program: prefix =$prefix"
   echo 'prefix does not exists, so not testing any python packages.'
   exit 0
fi
# -----------------------------------------------------------------------------
#
# python_env
source python/bin/python_env.sh
#
# pytest
pytest $(ls python/xam/*.py | sed -e '/\/temp.py$/d' )
#
echo "$program: OK"
exit 0
