#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e -u
# ----------------------------------------------------------------------------
program='python/bin/run_xam.sh'
#
if [ ! -d .git ]
then
   echo "$program: must be run from the top soruce directory"
   exit 1
fi
if [ "$#" != 1 ] && [ "$#" != 2 ]
then
   echo "usage: $program file [option]"
   echo 'where python/xam/file is a python example file'
   echo 'and the only possible value for option is debug.'
   exit 1
fi
file="$1"
debug='false'
if [ "$#" == 2 ]
then
   if [ "$2" == 'debug' ]
   then
      debug='true'
   else
         echo "$program: option = $2 , debug is only valid option"
         exit 1
   fi
fi
if [ ! -e "python/xam/$file" ]
then
   echo "$program: file = $file and python/xam/$file is not a file."
   exit 1
fi
# ----------------------------------------------------------
$(python/bin/pythonpath.sh)
#
# temp.py
sed -e 's|^def test_.*|if True :|'  python/xam/$file > python/xam/temp.py
if [ "$debug" == 'true' ]
then
   python3 -m pdb python/xam/temp.py
else
   python3 python/xam/temp.py
fi
#
echo "$program: OK"
exit 0
