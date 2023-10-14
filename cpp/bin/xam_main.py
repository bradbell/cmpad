#! /usr/bin/env python3
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
# {xrst_begin cpp_xam_main.py}
# {xrst_spell
#     xam
# }
# {xrst_comment_ch #}
#
# Example and Test Using C++ Main Program
# #######################################
#
# cpp/xam_main.csv
# ****************
# This program create the file cpp/xam_main.csv.
# If this file already exists, the previous version is removed
# and a completely new version is created.
# Below is an example of the contents of this file:
#
# ..  csv-table::
#     :widths: auto
#     :header-rows: 1
#     :file: {xrst_dir cpp/xam_main.csv}
#
# Source Code
# ***********
# {xrst_literal
#     # BEGIN PYTHON
#     # END PYTHON
# }
# {xrst_end cpp_xam_main.py}
# -----------------------------------------------------------------------------
# BEGIN PYTHON
import sys
import os
import csv
import re
import subprocess
def main() :
   #
   # program
   program = 'cpp/bin/xam_main.py'
   #
   # run_cmpad
   run_cmpad = 'cpp/build/src/run_cmpad'
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
   if not os.path.isfile(run_cmpad) :
      msg  = f'{program}: {run_cmpad} does not exist.'
      msg += '\nUse use make in cpp/build to create it.'
      sys.exit(msg)
   #
   # package_list
   # use configure file to determine list of available packages
   package_list = [ 'double' ]
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
         package_list.append(package)
   print( f'package_list = {package_list}' )
   #
   # change directory
   os.chdir('cpp/build')
   #
   # run_cmpad
   index      = len('cpp/build')
   run_cmpad  = run_cmpad[index+1 :]
   #
   # file_name
   file_name = '../xam_main.csv'
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
         for package in package_list :
            #
            # command
            command = [
               run_cmpad,
               f'--package={package}',
               f'--algorithm={algorithm}',
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
   #
   print( f'{program}: OK')
#
main()
# END PYTHON