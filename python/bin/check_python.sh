#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e -u
# ----------------------------------------------------------------------------
program='python/bin/check_python.sh'
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
#
# xam_main.py
python/bin/xam_main.py
#
# pytest
cd python
python -m pytest xam/*.py
#
echo "$program: OK"
exit 0
