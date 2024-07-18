#! /usr/bin/env python3
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
# {xrst_begin xam_main.py}
# {xrst_spell
#     src
# }
# {xrst_comment_ch #}
#
# Example and Test Using Main Programs
# ####################################
#
# Python
# ******
# The python cmpad main program is
# {xrst_code py}
py_run_cmpad = 'python/bin/run_cmpad.py'
# {xrst_code}
#
# C++
# ***
# The C++ main program is
# {xrst_code py}
cpp_run_cmpad = 'cpp/build/src/run_cmpad'
# {xrst_code}
#
# xam_main.csv
# ************
# This program create the file ``xam_main.csv`` .
# If this file already exists, the previous version is removed
# and a completely new version is created.
# The meaning of the columns are described in :ref:`csv_column-name` .
# Below is a display of an
# :download:`example xam_man.csv <{xrst_dir xam_main.csv}>` .
# The values *n_arg* and *n_other* determine the number of floating
# point operations and are small for these cases so that the
# program runs quickly:
# 
#
# ..  csv-table::
#     :widths: auto
#     :header-rows: 1
#     :file: {xrst_dir xam_main.csv}
#
# Source Code
# ***********
# {xrst_literal
#     # BEGIN PYTHON
#     # END PYTHON
# }
# {xrst_end xam_main.py}
# -----------------------------------------------------------------------------
# BEGIN PYTHON
import sys
import os
import csv
import re
import subprocess
import importlib
import platform
#
# sys.path
python_version  = platform.python_version()
(major, minor, patch) = python_version.split('.')
for lib in [ 'lib', 'lib64' ] :
   directory = f'python/build/prefix/{lib}/python{major}.{minor}/site-packages'
   if os.path.isdir(directory) :
      sys.path.insert(0, os.getcwd() + '/' + directory)
#
def main() :
   #
   # program
   program = 'bin/xam_main.py'
   #
   # configure_file
   configure_file = 'cpp/include/cmpad/configure.hpp'
   #
   # check
   if len(sys.argv) != 1 :
      msg = f'{program}: does not expect any arguments'
      sys.exit(msg)
   if sys.argv[0] != program :
      msg = f'{program}: must be executed from the top source directory'
      sys.exit(msg)
   if not os.path.isfile(configure_file) :
      msg  = f'{program}: {configure_file} does not exist.'
      msg += '\nUse cpp/bin/run_cmake.sh to create it.'
      sys.exit(msg)
   if not os.path.isfile(cpp_run_cmpad ) :
      msg           = f'{program}: {cpp_run_cmpad} does not exist.'
      msg          += '\nUse use make in cpp/build to create it.'
      sys.exit(msg)
   #
   # cpp_package_list
   # use configure file to determine list of available packages
   cpp_package_list = list()
   file_obj  = open(configure_file, 'r')
   file_data = file_obj.read()
   file_obj.close()
   ad_package = 'adept,adolc,autodiff,codi,cppad,cppad_jit,cppadcg,sacado'
   for package in ad_package.split(',') :
      PACKAGE = package.upper()
      pattern = f'# *define *CMPAD_HAS_{PACKAGE} *[01]'
      match   = re.search(pattern, file_data)
      if match == None :
         msg   = f'{program}: {configure_file} cannot find the pattern'
         msg += f'\n{pattern}'
         sys.exit(msg)
      if match.group(0)[-1] == '1' :
         cpp_package_list.append(package)
   print( f'cpp_package_list = {cpp_package_list}' )
   #
   # python_package_list
   python_package_list = list()
   for package in [ 'autograd', 'cppad_py', 'jax', 'torch' ] :
      try :
         importlib.import_module(package)
         python_package_list.append(package)
      except :
         pass
   print( f'python_package_list = {python_package_list}' )
   #
   # package_list
   package_list = [ 'none' ] + cpp_package_list + python_package_list
   #
   # file_name
   file_name = 'xam_main.csv'
   if os.path.isfile(file_name) :
      os.remove(file_name)
   #
   # default_min_time
   default_min_time = 0.5
   #
   # n_arg_dict
   n_arg_dict = {
      'det_by_minor' : 9 ,
      'an_ode'       : 100 ,
      'llsq_obj'     : 9,
   }
   #
   # n_other_dict
   n_other_dict = {
      'det_by_minor' : 0 ,
      'an_ode'       : 9 ,
      'llsq_obj'     : 100
   }
   #
   # time_setup
   for time_setup in [ True, False ] :
      #
      # algorithm
      algorithm_list = [ 'det_by_minor' , 'an_ode' , 'llsq_obj' ]
      for algorithm in algorithm_list :
         #
         # n_arg
         n_arg  = n_arg_dict[algorithm]
         #
         # n_other
         n_other = n_other_dict[algorithm]
         #
         # package
         for package in package_list :
            #
            # run_cmpad_list
            if package == 'none' :
               run_cmpad_list = [ cpp_run_cmpad, py_run_cmpad ]
            elif package in cpp_package_list :
               run_cmpad_list = [ cpp_run_cmpad ]
            else :
               assert package in python_package_list
               run_cmpad_list = [ py_run_cmpad ]
            #
            # run_cmpad
            for run_cmpad in run_cmpad_list :
               #
               # command
               command = [
                  run_cmpad,
                  f'--package={package}',
                  f'--algorithm={algorithm}',
                  f'--n_arg={n_arg}',
                  f'--n_other={n_other}',
                  f'--file_name={file_name}',
               ]
               if time_setup :
                  command.append('--time_setup')
               #
               # run command
               print( ' '.join(command) )
               result = subprocess.run(command)
               if result.returncode != 0 :
                  msg  = ' '.join(command)
                  msg += '\nxam_main.py: command above failed'
                  sys.exit(msg)
   #
   # file_obj
   file_obj = open(file_name)
   reader = csv.DictReader(file_obj)
   for row in reader :
      algorithm = row['algorithm']
      assert float(row['min_time']) == default_min_time
      assert int(row['n_arg']) == n_arg_dict[algorithm]
      assert row['package'] in package_list
      assert row['algorithm'] in algorithm_list
      assert row['time_setup'] in [ 'true', 'false' ]
      assert int( row['n_other'] ) == n_other_dict[algorithm]
   #
   print( f'{program}: OK')
#
main()
# END PYTHON
