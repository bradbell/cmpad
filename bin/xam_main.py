#! /usr/bin/env python3
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
# {xrst_begin xam_main.py}
# {xrst_spell
#     xam
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
# This program create the file xam_main.csv.
# If this file already exists, the previous version is removed
# and a completely new version is created.
# Below is an example of the contents of this file:
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
import platform
import os
import csv
import re
import subprocess
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
   ad_package = 'adept,adolc,autodiff,cppad,cppad_jit,cppadcg,sacado'
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
   version       = platform.python_version_tuple()
   major         = version[0]
   minor         = version[1]
   site_packages = f'python{major}.{minor}/site-packages'
   for package in [ 'autograd', 'cppad_py' ] :
      for lib in [ 'lib' , 'lib64' ] :
         dir_path = f'python/build/prefix/{lib}/{site_packages}/{package}'
         if os.path.isdir(dir_path) :
            assert package not in python_package_list
            python_package_list.append(package)
   print( f'python_package_list = {python_package_list}' )
   #
   # package_list
   package_list = [ 'double' ] + cpp_package_list + python_package_list
   #
   # file_name
   file_name = 'xam_main.csv'
   if os.path.isfile(file_name) :
      os.remove(file_name)
   #
   # default_min_time
   default_min_time = 0.5
   #
   # default_n_arg
   default_n_arg = 9
   #
   # time_setup
   for time_setup in [ True, False ] :
      #
      # algorithm
      algorithm_list = [ 'det_by_minor' , 'an_ode' ]
      for algorithm in algorithm_list :
         #
         # r_index
         r_index_list = [ 0 ]
         if algorithm == 'an_ode' :
            r_index_list = [ default_n_arg - 1 , default_n_arg - 2 ]
         for r_index in r_index_list :
            #
            # package
            for package in package_list :
               #
               # run_cmpad
               if package == 'double' :
                  run_cmpad_list = [ cpp_run_cmpad, py_run_cmpad ]
               elif package in cpp_package_list :
                  run_cmpad_list = [ cpp_run_cmpad ]
               else :
                  assert package in python_package_list
                  run_cmpad_list = [ py_run_cmpad ]
               for run_cmpad in run_cmpad_list :
                  #
                  # command
                  command = [
                     run_cmpad,
                     f'--package={package}',
                     f'--algorithm={algorithm}',
                     f'--r_index={r_index}',
                     f'--file_name={file_name}',
                  ]
                  if time_setup :
                     command.append('--time_setup')
                  #
                  # run command
                  print( ' '.join(command) )
                  result = subprocess.run(command)
                  if result.returncode != 0 :
                     msg  = 'command above failed\n'
                     sys.exit(msg)
   #
   # file_obj
   file_obj = open(file_name)
   reader = csv.DictReader(file_obj)
   for row in reader :
      assert float(row['min_time']) == default_min_time
      assert int(row['n_arg']) == default_n_arg
      assert row['package'] in package_list
      assert row['algorithm'] in algorithm_list
      assert row['time_setup'] in [ 'true', 'false' ]
      if row['algorithm'] == 'det_by_minor' :
         assert int( row['r_index'] ) == 0
      else :
         assert int(row['r_index']) in [ default_n_arg - 1, default_n_arg - 2 ]
   #
   print( f'{program}: OK')
#
main()
# END PYTHON
