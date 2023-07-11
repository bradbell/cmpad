#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e -u
if [ $# != 0 ]
then
   echo 'check_invisible.sh does not expect any arguments'
   exit 1
fi
# ---------------------------------------------------------------------------
for file in $(git ls-files)
do
   sed $file \
      -e 's|[ \t][ \t]*$||' \
      -e '1{/^[ \t]*$/d}' \
      -e '${/^[ \t]*$/d}' > check_invisible.$$
   #
   if ! diff $file check_invisible.$$
   then
      read -p "remove invisible white space from $file [y/n] ?" response
      if [ "$response" == 'y' ]
      then
        mv check_invisible.$$ $file
      fi
   fi
done
if [ -e check_invisible.$$ ]
then
   rm check_invisible.$$
fi
#
echo 'check_invisible.sh: OK'
exit 0
