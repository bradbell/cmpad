#! /usr/bin/env python3
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
# {xrst_begin xam_main.py}
# {xrst_spell
#     src
#     xam
# }
# {xrst_comment_ch #}
#
# Example and Test Using cmpad Main Program
# #########################################
#
# src/xam_main.csv
# ****************
# This program create the file src/xam_main.csv.
# If this file already exists, the previous version is removed
# and a completely new version is created.
# Below is an example of the contents of this file:
#
# ..  csv-table::
#     :widths: auto
#     :header-rows: 1
#     :file: {xrst_dir src/xam_main.csv}
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
import subprocess
def main() :
   #
   # cmpad_main
   cmpad_main = 'build/src/cmpad'
   #
   # check
   usage = 'bin/xam_main.py'
   if len(sys.argv) != 1 :
      msg = 'bin/xam_main.py: does not expect any arguments'
      sys.exit(msg)
   if sys.argv[0] != 'bin/xam_main.py' :
      msg = 'bin/xam_main.py: must be executed from its parent directory'
      sys.exit(msg)
   if not os.path.isfile(cmpad_main) :
      msg = f'bin/xam_main.py: {cmpad_main} does not exist'
      sys.exit(msg)
   #
   # change directory
   os.chdir('build')
   #
   # cmpad_main
   index = cmpad_main.find('/')
   cmpad_main = cmpad_main[index+1 :]
   #
   # file_name
   file_name = '../src/xam_main.csv'
   if os.path.isfile(file_name) :
      os.remove(file_name)
   #
   # default_min_time
   default_min_time = 0.5
   #
   # default_size
   default_size = 5
   #
   #
   # package
   package_list = 'double,adolc,autodiff,cppad,cppad_jit,cppadcg,sacado'
   package_list = package_list.split(',')
   for package in package_list :
      #
      # algorithm
      algorithm_list = [ 'det_by_minor' ]
      for algorithm in algorithm_list :
         #
         # time_setup
         for time_setup in [ True, False ] :
            #
            # command
            command = [
               cmpad_main,
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
      assert int(row['size']) == default_size
      assert row['package'] in package_list
      assert row['algorithm'] in algorithm_list
      assert row['time_setup'] in [ 'true', 'false' ]
#
main()
print('bin/xam_main.py: OK')
# END PYTHON
