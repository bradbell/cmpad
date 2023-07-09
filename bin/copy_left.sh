#! /usr/bin/env bash
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e
if [ "$2" == '' ]
then
   echo 'usage: bin/copy_left.sh file_name comment_string'
   exit 1
fi
#
# $file_name, cs
file_name="$1"
cs="$2"
if [ ! -f "$file_name" ]
then
   echo "copy_left.sh: cannot find the file '$file_name'."
   exit 1
fi
#
# shebang
shebang='no'
if [ -x $file_name ]
then
   if sed -n -e '1,1p' $file_name | grep '^#!' > /dev/null
   then
      shebang='yes'
   else
      echo "copy_left.sh: $file_name is executable but does not have a shebang"
      exit 1
   fi
else
   if ! sed -n -e '1,1p' $file_name | grep '^#!' > /dev/null
   then
      echo "copy_left.sh: $file_name has a shebang but is not executable"
      exit 1
   fi
fi
echo "shebang=$shebang"
#
# $file_name copy_left.$$
mv $file_name copy_left.$$
#
# $file_name
if [ "$shebang" == 'yes' ]
then
   sed -n -e '1,1p' copy_left.$$ > $file_name
fi
#
# $file_name
cat << EOF >> $file_name
$cs SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
$cs SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
$cs SPDX-FileContributor: 2023 Bradley M. Bell
$cs ---------------------------------------------------------------------------
EOF
if [ $shebang == 'yes' ]
then
   sed -n -e '2,$p' copy_left.$$ >> $file_name
   chmod +x $file_name
else
   cat copy_left.$$ >> $file_name
fi
#
# clean up
rm copy_left.$$
echo 'copy_left.sh: OK'
exit 0
