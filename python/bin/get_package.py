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
   getcwd
   rm
   srcdir
}

Getting Option Python Packages
##############################
This script can be used to install optional python AD packages
that cmpad can test.

Syntax
******
``python/bin/get_package.py`` *build_type* ``all`
``python/bin/get_package.py`` *build_type* *package_1* [ *package_2* [ ... ] ]

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

   { 'autograd' , 'cppad_py' , 'pytorch' }

If one of these packages is installed,
it will be included in the cmpad testing.

.. _autograd: https://github.com/HIPS/autograd.git
.. _cppad_py: https://github.com/bradbell/cppad_py
.. _pytorch:  https://github.com/pytorch/pytorch

.. csv-table::
   :widths: auto
   :header-rows: 1

   Web Site,      Implementation
   `autograd`_,   :ref:`autograd_gradient-name`
   `cppad_py`_,   :ref:`cppad_py_gradient-name`
   `pytorch`_,    :ref:`pytorch_gradient-name`

all
***
If the ``all`` version of the syntax is used,
all the python packages will be installed.


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
``python/bin/get_package.py`` :
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
# pyproject_version
def pyproject_version() :
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
   return version
#
# install_pytorch
def install_pytorch() :
   #
   # list_of_commands
   list_of_commands = [ f'pip install torch --prefix={prefix}' ]
   system_command(list_of_commands)
#
# install_autograd
def install_autograd(build_type) :
   #
   # version
   version = pyproject_version()
   #
   # list_of_commands
   list_of_commands = [
      'python -m build' ,
      f'pip install dist/autograd-{version}.tar.gz --prefix={prefix}',
   ]
   system_command(list_of_commands)
#
# install_cppad_py
def install_cppad_py(build_type) :
   #
   # install_settings
   file_obj         = open( 'bin/install_settings.py', 'r')
   install_settings = file_obj.read()
   file_obj.close()
   #
   # install_settings
   pattern          = r'\ncmake_install_prefix=.*'
   replace          = f'\ncmake_install_prefix="{prefix}"'
   install_settings = re.sub(pattern, replace, install_settings)
   pattern          = r'\nbuild_type=.*'
   replace          = f"\nbuild_type='{build_type}'"
   install_settings = re.sub(pattern, replace, install_settings)
   #
   # install_settings.py
   file_obj  = open( 'bin/install_settings.py', 'w')
   file_obj.write(install_settings)
   file_obj.close()
   #
   # version
   version = pyproject_version()
   #
   # list_of_commands
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
   usage  = f'{program} build_type all\n'
   usage  = f'{program} build_type package_1 [ package_2 [..] ]\n\n'
   usage += 'build_type: is debug or release\n'
   usage += 'package_j: is the j-th package to install and is one of:\n'
   usage += 'autograd, cppad_py, pytorch'
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
      'autograd' : install_autograd ,
      'cppad_py' : install_cppad_py ,
      'pytorch'  : install_pytorch ,
   }
   #
   # package_webpage
   package_webpage = {
      'autograd' : 'https://github.com/HIPS/autograd.git' ,
      'cppad_py' : 'https://github.com/bradbell/cppad_py.git' ,
      'pytorch'  : None ,
   }
   #
   # package_list
   if sys.argv[2] == 'all' :
      if len(sys.argv) != 3 :
         msg  = f'{program}: all is the second arugment '
         msg += 'and there are other arguments after it.'
         sys.exit(msg)
      package_list = list( package_install.keys() )
   else :
      package_list = sys.argv[2 :]
   #
   # package
   for package in package_list :
      #
      # package
      if package not in package_install :
         msg  = f'{program}: package = {package} is not yet implemented'
         sys.exit(msg)
      #
      # webpage
      webpage = package_webpage[package]
      if webpage == None :
         #
         # package_install
         package_install[package]()
      else :
         # package.git
         if not os.path.isdir( f'{package}.git' ) :
            command_str = f'git clone {webpage} {package}.git'
            system_command( [ command_str ] )
         os.chdir( f'{package}.git' )
         command_str = 'git pull'
         system_command( [ command_str ] )
         #
         # package_install
         package_install[package](build_type)
         #
         # external
         os.chdir( '..' )
   #
   command = ' '.join( sys.argv )
   print( f'{command}: OK' )
#
main()
