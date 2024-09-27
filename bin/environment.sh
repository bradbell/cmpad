# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
if [[ ! "${build_type+x}" ]]
then
   echo 'usage: build_type=(debug or release)'
   echo '       source bin/environment.sh'
elif [ "$build_type" != 'debug' ] && [ "$build_type" != 'release' ]
then
   echo 'bin/environment.sh: build_type is not debug or release'
elif [ ! -d .git ]
then
   echo "bin/environment.sh: Cannot find .git in pwd = $(pwd)"
else
   #
   # environment.$$
   # 2DO: remove ==1.26.4 when autograd works with numpy==2.0.0
   # https://github.com/HIPS/autograd/issues/622
cat << EOF > environment.$$
#
# disconnect from currently active virtual environment
if [[ "${VIRTUAL_ENV+x}" ]]
then
   deactivate
fi
#
# disconnect from extra packages on this system
PYTHONPATH=''
#
# create virtual environment without system site-packages
python3 -m venv build/$build_type
#
# activate the virtual environment
source build/$build_type/bin/activate
#
# install packages that may be required
for package in toml pytest numpy==1.26.4
do
   echo "pip install \$package"
   pip install \$package
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
      echo "It should have been created by see ./environment.$$"
   else
      rm ./environment.$$
      #
      # activate
      if [[ "${VIRTUAL_ENV+x}" ]]
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
