#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e -u
if [ $# != 0 ]
then
   echo 'bin/check_sorted.sh does not expect any arguments'
   exit 1
fi
if [ ! -d .git ]
then
   echo 'bin/check_sorted.sh: must be executed from top source directory'
   exit 1
fi
# ---------------------------------------------------------------------------
for file in $(git ls-files)
do
   if [ "$file" != 'bin/check_sorted.sh' ] && [ "$file" != 'bin/sort_file.py' ]
   then
      if grep 'BEGIN_SORT_THIS_LINE_' $file > /dev/null
      then
         bin/sort_file.py $file
      fi
   fi
done
#
echo 'check_sorted.sh: OK'
exit 0
