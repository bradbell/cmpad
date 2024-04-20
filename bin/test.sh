#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e -u
#
job='debug'
build_type='release'
#
# environment.sh
source bin/environment.sh
#
if [ "$job" == 'debug' ]
then
   file='python/xam/llsq_obj.py'
   git checkout $file
   sed -i -e 's|assert \(.*\)() == True|&\n\1()|' $file
   python -m pdb $file
   git checkout $file
elif [ "$job" == 'check_python' ]
then
   python/bin/check_python.py $build_type
elif [ "$job" == 'xam_main' ]
then
   bin/xam_main.py
else
   echo 'temp.sh: job is invalid'
   exit
fi
#
echo 'temp.sh: OK'
exit 0
