#! /usr/bin/env bash
set -e -u
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
if [[ ! -v build_type ]]
then
   echo 'bin/environment.sh: build_type is not defined'
elif [ "$build_type" != 'debug' ] && [ "$build_type" != 'release' ]
then
   echo 'bin/environment.sh: build_type is not debug or release'
elif [ ! -d .git ]
then
   echo "bin/environment.sh: Cannot find .git in pwd = $(pwd)"
else
   #
   # environment.$$
cat << EOF > environment.$$
python3.11 -m venv build/$build_type
source build/$build_type/bin/activate
for package in toml pytest numpy
do
   echo "pip install \$package"
   if ! pip install \$package >& environment.log
   then
      cat environment.log
      echo "Error: pip install \$package"
   fi
done
EOF
   #
   # build/$build_type
   if [ ! -e build/$build_type/bin/activate ]
   then
      echo "# begin: creatting build/$build_type"
      bash environment.$$
      echo "# end: creatting build/$build_type"
   fi
   if [ ! -e build/$build_type/bin/activate ]
   then
      echo "bin/environment.sh: build/$build_type/bin/activate is missing"
      echo "It should have been creaed by see ./environment.$$"
   else
      rm ./environment.$$
      #
      # activate
      if [[ -v VIRTUAL_ENV ]]
      then
         if ! echo $VIRTUAL_ENV | grep "/build/$build_type\$" > /dev/null
         then
            deactivate
            source "build/$build_type/bin/activate"
         fi
      else
         source "build/$build_type/bin/activate"
      fi
      #
      # site_pacakages
      temp_site_packages=$(find build/$build_type -name 'site-packages')
      temp_site_packages=$(echo $temp_site_packages | sed -e 's|  *|:|' )
      #
      # PYTHONPATH
      export PYTHONPATH="$(pwd)/python:$temp_site_packages"
   fi
fi
