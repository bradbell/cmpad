#! /usr/bin/env python3
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
import os
r'''
{xrst_begin get_package.py}
{xrst_spell
   srcdir
   getcwd
   rm
}

Getting Option Python Packages
##############################
This script can be used to install optional python AD packages
that cmpad can test.

Syntax
******
``bin/python/get_package.py`` *build_type* *package_1* [ *package_2* [ ... ] ]

build_type
==========
This is either ``debug`` or ``release`` and determines if libraries,
built while installing the packages, are debug or release versions.

package_j
=========
The packages *package_1* , *package_2*, ...
are the list of packages that will be installed.
This list must have at least one package ; i.e.,
*package_2* , *package_3* , ... are optional.

packages
********
This is the set of the packages (so far) that can be installed::

   { 'cppad_py' }

If one of these packages is installed,
it will be included in the cmpad testing.

.. _cppad_py: https://github.com/bradbell/cppad_py

.. csv-table::
   :widths: auto
   :header-rows: 1

   Web Site,      Implemented
   `cppad_py`_,   :ref:`cppad_py_gradient-name`


top_srcdir
**********
The working directory, when this command is executed, must be the
top source directory for cmpad; i.e.,
the directory containing the ``.git`` directory for cmpad.
{xrst_code py}'''
top_srcdir = os.getcwd()
r'''{xrst_code}

prefix
******
This is the prefix for the packages installed by
``bin/python/get_package.py`` :
{xrst_code py}'''
prefix     = f'{top_srcdir}/python/build/prefix'
r'''{xrst_code}
Note that this is a local install and does not require any special
permissions.

external
********
The source code, and corresponding builds, for all installed packages
is in the *top_srcdir*\ ``/external`` directory.
Thus you can remove the *prefix* directory and reinstall a new list
of packages quickly.
If you have trouble with a particular *package* ,
and ``external/``\ *package*\ .\ *build_type* exists,
you may want to try the following:

| |tab| ``rm -r external/``\ *package*\ .\ *build_type*
| |tab| ``bin/get_package`` *build_type* *package*

{xrst_end get_package.py}
'''
#
import toml
import sys
import re
import subprocess
#
# program
program = 'bin/python/get_pacakge.py'
#
# system_command
def system_command(list_of_commands) :
   for command_str in list_of_commands :
      print(command_str)
      command_list      = command_str.split()
      subprocess_return = subprocess.run(command_list)
      if subprocess_return.returncode != 0 :
         msg  = 'system command above failed'
         sys.exit(msg)
#
# install_cppad_py
def install_cppad_py(build_type) :
   #
   # get_cppad
   file_obj  = open( 'bin/get_cppad.sh', 'r')
   get_cppad = file_obj.read()
   file_obj.close()
   pattern = r'\ncmake_install_prefix=.*'
   replace = f'\ncmake_install_prefix="{prefix}"'
   get_cppad = re.sub(pattern, replace, get_cppad)
   #
   # get_cppad.sh
   file_obj  = open( 'bin/get_cppad.sh', 'w')
   file_obj.write(get_cppad)
   file_obj.close()
   #
   # pyproject
   file_obj  = open('pyproject.toml', 'r')
   file_data = file_obj.read()
   pyproject = toml.loads(file_data)
   file_obj.close()
   #
   # version
   version = pyproject['project']['version']
   #
   # get_cppad.sh
   list_of_commands = [
      'bin/get_cppad.sh',
      'python -m build' ,
      f'pip install dist/cppad_py-{version}.tar.gz --prefix={prefix}',
   ]
   system_command(list_of_commands)
#
# main
def main() :
   if not os.path.isdir( '.git' ) :
      msg = f'{program}: must be executed from cmpad top source directory'
      sys.exit(msg)
   #
   # usage
   usage  = f'{program} build_type package_1 [ package_2 [..] ]\n'
   usage += 'buid_type: is debug or release\n'
   usage += 'package_j: is the j-th package to install\n'
   if len( sys.argv ) < 3 :
      sys.exit(usage)
   #
   # build_type
   build_type = sys.argv[1]
   if build_type not in [ 'debug', 'release' ] :
      msg = f'{program}: build_type = {build_type} is not debug or release'
      sys.exit(msg)
   #
   # external
   if not os.path.isdir( 'external' ) :
      os.mkdir('external')
   os.chdir('external')
   #
   # package_install
   package_install = {
      'cppad_py' : install_cppad_py ,
   }
   #
   # package_webpage
   package_webpage = {
      'cppad_py' : 'https://github.com/bradbell/cppad_py.git'
   }
   #
   # package
   for index in range(2, len(sys.argv), 1) :
      package = sys.argv[index]
      #
      # webpage
      if package not in package_webpage :
         msg  = f'{program}: package = {package} is not yet implemented'
      webpage = package_webpage[package]
      #
      # package.git
      if not os.path.isdir( f'{package}.git' ) :
         command_str = f'git clone {webpage} {package}.git'
         system_command( [ command_str ] )
      os.chdir( f'{package}.git' )
      command_str = 'git pull'
      system_command( [ command_str ] )
      #
      # install
      package_install[package](build_type)
      #
      # external
      os.chdir( '..' )
   #
   command = ' '.join( sys.argv )
   print( f'{command}: OK' )
#
main()
