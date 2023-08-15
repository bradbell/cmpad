#! /usr/bin/env bash
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ----------------------------------------------------------------------------
set -e -u
if [ $# != 0 ]
then
   echo 'bin/check_copy.sh does not expect any arguments'
   exit 1
fi
if [ ! -e 'bin/check_copy.sh' ]
then
   echo 'bin/check_copy.sh: must be executed from its parent directory'
   exit 1
fi
# ---------------------------------------------------------------------------
ignore_list='
   .gitignore
   xam/csv_speed.csv
   .readthedocs.yaml
   readme.md
'
missing='no'
for file_name in $(git ls-files)
do
   if ! echo "$ignore_list" | tr '\n' ' ' | grep " $file_name " > /dev/null
   then
      if ! grep 'SPDX-FileCopyrightText:' $file_name > /dev/null
      then
         echo "missing SPDX-FileCopyrightText: $file_name"
         missing='yes'
      fi
   fi
done
#
if [ "$missing" = 'yes' ]
then
   echo 'bin/check_copy.sh: See copyright errors above'
   exit 1
fi
echo 'bin/check_copy.sh: OK'
exit 0
