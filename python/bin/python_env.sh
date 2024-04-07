#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
# Use source this script to set the python environment and path.
#
# program
program='python/bin/python_env.sh'
#
if echo "$0" | grep '/python_env.sh' > /dev/null
then
   echo "$program: must source this file, not execute it"
   exit 1
fi
if [ ! -d .git ]
then
   echo "${program}: Cannot find .git in pwd = $(pwd)"
else
   if [ ! -d python/venv ]
   then
      python3.11 -m venv python/venv
      source python/venv/bin/activate
      pip install toml build pytest
   fi
   #
   # VIRTUAL_ENV
   if ! printenv | grep '^VIRTUAL_ENV=' > /dev/null
   then
      source python/venv/bin/activate
   fi
   if ! echo $VIRTUAL_ENV | grep '/python/venv$' > /dev/null
   then
         echo "${program}: Unexpected VIRTUAL_ENV = $VIRTUAL_ENV"
   else
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
      export PYTHONPATH="$python_dir:$site_packages"
   fi
fi
