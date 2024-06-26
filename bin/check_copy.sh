#! /usr/bin/env bash
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
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
license='SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later'
missing='no'
changed='no'
for file_name in $(git ls-files | sed \
   -e '/^.gitignore$/d' \
   -e '/^.readthedocs.yaml$/d' \
   -e '/^readm.md$/d' \
   -e '/^xam_main.csv$/d' \
)
do
   if ! grep "$license\$" $file_name > /dev/null
   then
      if [ "$missing" == 'no' ]
      then
         echo "Cannot find line that ends with:"
         echo "   $license"
         echo "In the following files:"
      fi
      echo "$file_name"
      missing='yes'
   fi
done
for file_name in $(git status --porcelain | sed -e 's|^...||' )
do
   if [ -f $file_name ]
   then
      sed \
      -e 's|\(SPDX-FileContributor\): *\([0-9]\{4\}\)[-0-9]* |\1: \2-24 |' \
      -e 's|\(SPDX-FileContributor\): 2024-24 |\1: 2024 |' \
      $file_name > temp.$$
      if diff $file_name temp.$$ > /dev/null
      then
         rm temp.$$
      else
         if [ "$changed" == 'no' ]
         then
            echo 'The following file contributor dates have been updated'
         fi
         echo $file_name
         changed='yes'
         if [ -x $file_name ]
         then
            mv temp.$$ $file_name
            chmod +x $file_name
         else
            mv temp.$$ $file_name
         fi
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
