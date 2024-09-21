#! /usr/bin/env python3
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
import os
r'''
{xrst_begin py_get_package}

Getting Optional Python Packages
################################

Syntax
******
``python/bin/get_package.py`` *build_type* *package*

build_type
**********
This is either ``debug`` or ``release`` and determines if libraries,
built while installing the packages, are debug or release versions.

cppad_py
========
Currently, cppad_py is the only python package that uses the *build_type*
during its install. The file

   external/cppad_py.\ *build_type*

indicates the build type for the previous install of cppad_py.

package
*******
The is one of the packages in the following list:
{xrst_literal
   bin/get_package.sh
   # BEGIN PYTHON_PACKAGE_LIST
   # END PYTHON_PACKAGE_LIST
}

{xrst_end py_get_package}
'''
#
import toml
import sys
import re
import subprocess
import pathlib
#
# program
program = 'python/bin/get_package.py'
#
# top_srcdir
top_srcdir = os.getcwd()
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
# install_cppad_py
def install_cppad_py(build_type) :
   #
   # external
   if not os.path.isdir( 'external' ) :
      os.mkdir('external')
   os.chdir('external')
   #
   # package_webpage
   webpage = 'https://github.com/bradbell/cppad_py.git'
   #
   # build_flag
   for build_type_tmp in [ 'debug', 'release' ] :
      build_flag = f'cppad.{build_type_tmp}'
      if os.path.exists(build_flag) :
         os.remove(build_flag)
   build_flag = f'cppad.{build_type}'
   #
   # cppad.git
   if not os.path.isdir( f'cppad_py.git' ) :
      command_str = f'git clone {webpage} cppad_py.git'
      system_command( [ command_str ] )
   #
   os.chdir( f'cppad_py.git' )
   #
   # list_of_commands
   list_of_commands = [
      'git reset --hard' ,
      'git pull',
   ]
   system_command( list_of_commands )
   #
   # install_settings
   file_obj         = open( 'bin/install_settings.py', 'r')
   install_settings = file_obj.read()
   file_obj.close()
   #
   # install_settings
   prefix           = f'{top_srcdir}/build/{build_type}'
   pattern          = r'\ncmake_install_prefix *=.*'
   replace          = f"\ncmake_install_prefix = '{prefix}'"
   install_settings = re.sub(pattern, replace, install_settings)
   pattern          = r'\nbuild_type *=.*'
   replace          = f"\nbuild_type = '{build_type}'"
   install_settings = re.sub(pattern, replace, install_settings)
   pattern          = r'\nsymbolic_link *=.*'
   replace          = f"\nsymbolic_link = 'false'"
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
      f'pip install .',
   ]
   system_command(list_of_commands)
   #
   # build_flag
   os.chdir('..')
   pathlib.Path(build_flag).touch()
#
# main
def main() :
   if not ( os.path.isdir( '.git' ) and sys.argv[0] == program ) :
      msg = f'{program}: must be executed from cmpad top source directory'
      sys.exit(msg)
   #
   # package_list
   package_list = [ 'autograd', 'cppad_py', 'jax', 'torch' ]
   #
   # usage
   usage  = f'{program} build_type package\n'
   usage += 'build_type: is debug or release and package is one of:\n'
   usage += ','.join(package_list)
   if len( sys.argv ) != 3 :
      sys.exit(usage)
   #
   # build_type
   build_type = sys.argv[1]
   if build_type not in [ 'debug', 'release' ] :
      msg = f'{program}: build_type = {build_type} is not debug or release'
      sys.exit(msg)
   ok  = sys.prefix.endswith( f'/build/{build_type}' )
   if not ok :
      msg  = f'{program}: The sys.prefix does not end with /build/{build_type}'
      msg += 'Need to source bin/environment.sh before runing {program}.'
      sys.exit(msg)
   #
   # package
   package      = sys.argv[2]
   if package not in package_list :
      msg  = f'{program}: package = {package} is not yet implemented'
      sys.exit(msg)
   # install
   if package == 'cppad_py' :
      install_cppad_py(build_type)
   else :
      pypi_name = {
         'autograd' : 'autograd' ,
         'torch'    : 'torch --index-url https://download.pytorch.org/whl/cpu'    ,
         'jax'      : 'jax[cpu]' ,
      }
      name  = pypi_name[package]
      list_of_commands = [ f'pip install {name}' ]
      system_command(list_of_commands)
   #
   # command
   command = ' '.join( sys.argv )
   print( f'{command}: OK' )
#
main()
