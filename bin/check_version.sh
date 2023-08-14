#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
set -u -e
if [ "$#" != 0 ]
then
   echo 'bin/check_version.sh: expects no arguments'
   exit 1
fi
if [ "$0" != 'bin/check_version.sh' ]
then
   echo 'bin/check_version.sh: must be executed from its parent directory'
   exit 1
fi
# -------------------------------------------------------------------------
version=$(date +%Y.%m.%d | sed -e 's|\.0*|.|g')
#
# lib/CMakeLists.txt
file=lib/CMakeLists.txt
cat << EOF > temp.sed
s|soversion *[0-9][0-9][.][0-9][0-9]*[.][0-9][0-9]*|soversion $version|
EOF
sed $file -f temp.sed > temp.out
if ! diff $file temp.out > /dev/null
then
   mv temp.out $file
   echo_eval git diff $file
else
   rm temp.out
fi
rm temp.sed
# -------------------------------------------------------------------------
echo 'check_version.sh: OK'
exit 0
