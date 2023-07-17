#! /bin/bash -e
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2003-22 Bradley M. Bell
# ----------------------------------------------------------------------------
if [ ! -e 'bin/check_guard.sh' ]
then
   echo 'bin/check_guard.sh: must be executed from its parent directory'
   exit 1
fi
# ---------------------------------------------------------------------------
list=$(git ls-files *.hpp)
different='no'
for file_name in $list
do
   dir=$(echo $file_name | sed -e 's|/[^/]*$||')
   name=$(echo $file_name | sed -e 's|^.*/||')
   first_dir=$(echo $dir | sed -e 's|/.*||')
   #
   macro_name=$(\
      sed -n -e '/^# *ifndef *CMPAD_[0-9A-Z_]*_HPP$/p' $file_name | \
      sed -e 's|^# *ifndef *||'
   )
   check=$(echo $file_name | tr [a-zA-Z/.] [A-Za-z__])
   #
   if [ "$first_dir" == 'include' ]
   then
      check=$(echo $check | sed -e 's|INCLUDE_||')
   else
      check="CMPAD_$check"
   fi
   #
   if [ "$macro_name" == '' ]
   then
      echo "$file_name: Cannot find  ^# *ifndef *CMPAD_[0-9A-Z_]*_HPP"
      different='yes'
   elif [ "$macro_name" != "$check" ]
   then
      echo "file_name=$file_name"
      echo "macro_name=$macro_name"
      different='yes'
   fi
done
#
if [ $different = 'yes' ]
then
   echo 'bin/check_guard.sh: See include guard errors above'
   exit 1
fi
echo 'bin/check_guard.sh: OK'
exit 0