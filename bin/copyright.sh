#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e -u
# ---------------------------------------------------------------------------
if [ $# != 2 ]
then
   echo 'usage: bin/copyright.sh file_name comment_string'
   echo 'file_name:      path to file we are adding copyright statement to'
   echo 'comment_string: This makes the rest of line, in file_name, a comment.'
   echo '                This may need to be quoted and may be empty.'
   exit 1
fi
#
# $file_name, comment_string
file_name="$1"
comment_string="$2"
if [ ! -f "$file_name" ]
then
   echo "copyright.sh: cannot find the file '$file_name'."
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
      echo "copyright.sh: $file_name is executable but does not have a shebang"
      exit 1
   fi
else
   if sed -n -e '1,1p' $file_name | grep '^#!' > /dev/null
   then
      echo "copyright.sh: $file_name has a shebang but is not executable"
      exit 1
   fi
fi
#
# $file_name copyright.$$
mv $file_name copyright.$$
#
# cs
if [ "$comment_string" == '' ]
then
   cs=''
else
   cs="$comment_string "
fi
#
# $file_name
if [ "$shebang" == 'yes' ]
then
   sed -n -e '1,1p' copyright.$$ > $file_name
   cat << EOF >> $file_name
$cs---------------------------------------------------------------------------
EOF
fi
#
# $file_name
cat << EOF >> $file_name
${cs}SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
${cs}SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
${cs}SPDX-FileContributor: 2023 Bradley M. Bell
$cs---------------------------------------------------------------------------
EOF
if [ $shebang == 'yes' ]
then
   sed -n -e '2,$p' copyright.$$ >> $file_name
   chmod +x $file_name
else
   cat copyright.$$ >> $file_name
fi
#
# clean up
rm copyright.$$
echo 'copyright.sh: OK'
exit 0
