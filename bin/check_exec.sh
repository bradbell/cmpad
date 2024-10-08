#! /usr/bin/env bash
set -e -u
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ----------------------------------------------------------------------------
if [ $# != 0 ]
then
   echo 'bin/check_exec.sh does not expect any arguments'
   exit 1
fi
if [ ! -e 'bin/check_exec.sh' ]
then
   echo 'bin/check_exec.sh: must be executed from its parent directory'
   exit 1
fi
# ---------------------------------------------------------------------------
ignore_list='
   ./bin/environment.sh
   ./bin/dev_settings.sh
   ./bin/grep_and_sed.sh
'
for file_name in $( git ls-files | sed -e 's|^bin|./bin|' )
do
   if ! echo "$ignore_list" | tr '\n' ' ' | grep " $file_name " > /dev/null
   then
      if echo $file_name | grep '/bin/' > /dev/null
      then
         if [ ! -x $file_name ]
         then
            echo "$file_name is in a bin directory and is not executable."
            read -p 'make it executable [yes/no] ?' response
            if [ "$response" == 'yes' ]
            then
               chmod +x $file_name
            else
               echo 'Add the ignore_list in bin/check_exec.sh ?'
               exit 1
            fi
         fi
      else
         if [ -x $file_name ]
         then
            echo "$file_name is not in a bin directory and is executable."
            read -p 'make it not executable [yes/no] ?' response
            if [ "$response" == 'yes' ]
            then
               chmod -x $file_name
            else
               echo 'Add the ignore_list in bin/check_exec.sh ?'
               exit 1
            fi
         fi
      fi
   fi
done
#
echo 'bin/check_exec.sh: OK'
exit 0
