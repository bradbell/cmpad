#! /usr/bin/env python3
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
# {xrst_begin py_xam_main.py}
# {xrst_spell
#     xam
# }
# {xrst_comment_ch #}
#
# Example and Test Using Python Main Program
# ##########################################
#
# python/xam_main.csv
# *******************
# This program create the file python/xam_main.csv.
# If this file already exists, the previous version is removed
# and a completely new version is created.
# Below is an example of the contents of this file:
#
# ..  csv-table::
#     :widths: auto
#     :header-rows: 1
#     :file: {xrst_dir python/xam_main.csv}
#
# Source Code
# ***********
# {xrst_literal
#     # BEGIN PYTHON
#     # END PYTHON
# }
# {xrst_end py_xam_main.py}
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
   program = 'bin/python/xam_main.py'
   #
   # check
   if len(sys.argv) != 1 :
      msg = f'{program}: does not expect any arguments'
      sys.exit(msg)
   if sys.argv[0] != program :
      msg = f'{program}: must be executed from the top source directory'
      sys.exit(msg)
   #
   # package_list
   package_list = [ 'float', 'cppad_py' ]
   print( f'package_list = {package_list}' )
   #
   # file_name
   file_name = 'python/xam_main.csv'
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
               'bin/python/run_cmpad.py',
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
