# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
# {xrst_begin environment}
# {xrst_spell
#     toml
#     pytest
# }
# {xrst_comment_ch #}
#
# Create and Activate cmpad Environment
# #####################################
#
# Syntax
# ******
# | |tab| ``build_type=``\ *build_type*
# | |tab| ``source bin/environment.sh``
#
# build_type
# **********
# This must be either ``debug`` or ``release`` .
#
# Create Environment
# ******************
# If the file ``build/``\ *build_type*\ ``/bin/activate`` does **not** exist,
# a python virtual environment is create in the directory
# ``build/``\ *build_type* .
# In addition, the python packages xrst, toml, pytest, and numpy
# are installed in this environment.
# In this case, environment.sh will output text saying that it is creating
# ``build/``\ *build_type*\ ``/bin/activate`` .
#
# Activate Environment
# ********************
# If the shell variable value $VIRTUAL_ENV does not end with
# ``build/``\ *build_type*\ , ``build/``\ *build_type*\ ``/bin/activate``
# is used to activate the environment.
# In this case, environment.sh will output text saying that it is sourcing
# ``build/``\ *build_type*\ ``/bin/activate`` .
#
# PYTHONPATH
# **********
# This shell variable will be set to the location of the site-packages
# in the virtual environment.
#
# {xrst_end environment}
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
   # activate
   activate="build/$build_type/bin/activate"
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
echo "source: $activate"
source $activate
#
# install packages that may be required
for package in xrst toml pytest numpy==1.26.4
do
   echo "pip install \$package"
   pip install \$package
done
#
# Most recent test version of xrst
pip uninstall -y xrst
pip install --index-url https://test.pypi.org/simple/ xrst
EOF
   #
   # build/$build_type
   if [ ! -e $activate ]
   then
      echo "begin: creatting $activate"
      bash environment.$$
      echo "end: creatting $activate"
   fi
   if [ ! -e $activate ]
   then
      echo "bin/environment.sh: $activate is missing"
      echo "It should have been created by see ./environment.$$"
   else
      rm ./environment.$$
      #
      # activate
      if ! echo "${VIRTUAL_ENV-x}" | grep "/build/$build_type\$" > /dev/null
      then
         echo "source: $activate"
         source $activate
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
