#! /usr/bin/env bash
set -e -u
# ----------------------------------------------------------------------------
program='bin/python/run_pytest.sh'
prefix="$(pwd)/python/build/prefix"
#
if [ ! -d .git ]
then
   echo "$program: must be run from the top soruce directory"
   exit 1
fi
#
# PYTHONPATH
site_packages=$(find -L $prefix -name 'site-packages')
site_packages=$(echo $site_packages | sed -e 's|  *|:|' )
export PYTHONPATH="$site_packages"
echo "$site_packages"
#
# pytest
cd python
python -m pytest xam/*.py
#
echo "$program: OK"
exit 0
