#! /usr/bin/env python
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
import sys
import os
import platform
import glob
import pytest
#
# program
program = 'python/bin/check_python.py'
#
# build_type
if not sys.argv[0] == program and len(sys.argv) == 2 :
   msg = f'usage: {program} build_type'
   sys.exit(msg)
build_type = sys.argv[1]
#
# ./.git
if not os.path.isdir('.git') :
   msg = f'{program} must be run from cmpad top source directory'
   sys.exit(msg)
#
# cwd
cwd = os.getcwd()
#
if sys.prefix != f'{cwd}/build/{build_type}' :
   msg  = f'{program}: sys.prefix = {sys.prefix}\n'
   msg += f'set build_type={build_type} and then execute:'
   msg += 'source bin/environment.sh'
   sys.exit(msg)
#
# sys.path
if not os.path.isdir('python/cmpad') :
   msg = 'expected python/cmpad below top source directory'
   sys.exit(msg)
sys.path.insert(0, os.getcwd() + '/python')
python_version        = platform.python_version()
(major, minor, patch) = python_version.split('.')
for lib in [ 'lib', 'lib64' ] :
   directory = f'python/build/prefix/{lib}/python{major}.{minor}/site-packages'
   if os.path.isdir(directory) :
      sys.path.insert(0, os.getcwd() + '/' + directory)
#
# cmpad
import cmpad
#
# test_list
glob_list = glob.glob('python/xam/*.py')
test_list = list()
for file in glob_list :
   ok = not file.endswith( 'temp.py' )
   for package in [ 'autograd', 'cppad_py' , 'jax', 'torch' ] :
      if not cmpad.has_package[package] :
         if file.endswith( f'_{package}.py' ) :
            ok = False
   if ok :
      test_list.append(file)
#
# pytest
pytest.main(test_list) 
#
print( f'{program}: OK' )
