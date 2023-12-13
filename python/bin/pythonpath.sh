#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e -u
# ----------------------------------------------------------------------------
# program
program='python/bin/environment.sh'
#
if [ ! -d .git ]
then
   echo "$program: must be run from the top soruce directory"
   exit 1
fi
#
# python_dir
python_dir="$(pwd)/python"
#
# prefix
prefix="$python_dir/build/prefix"
#
# PYTHONPATH
site_packages=$(find -L $prefix -name 'site-packages')
site_packages=$(echo $site_packages | sed -e 's|  *|:|' )
PYTHONPATH="$python_dir:$site_packages"
echo "export PYTHONPATH=$PYTHONPATH"
#
exit 0
