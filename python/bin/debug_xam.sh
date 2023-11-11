#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e -u
# ----------------------------------------------------------------------------
program='python/bin/debug_xam.sh'
prefix="$(pwd)/python/build/prefix"
#
if [ ! -d .git ]
then
   echo "$program: must be run from the top soruce directory"
   exit 1
fi
if [ "$#" != 1 ]
then
   echo "usage: $program file"
   echo 'where pyton/xam/file is a python example file'
   exit 1
fi
file="$1"
if [ ! -e "python/xam/$file" ]
then
   echo "usage: $program $file"
   echo "pyton/xam/$file is not a file"
fi
# ----------------------------------------------------------
#
site_packages=$(find -L $prefix -name 'site-packages')
site_packages=$(echo $site_packages | sed -e 's|  *|:|' )
export PYTHONPATH="$(pwd)/python:$site_packages"
#
# temp.py
sed -e 's|^def test_.*|if True :|'  python/xam/$file > python/xam/temp.py
#
python -m pdb python/xam/temp.py
#
echo "$program: OK"
exit 0
