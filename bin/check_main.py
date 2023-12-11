#! /usr/bin/env python3
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
import sys
import csv
import subprocess
#
# program
program = 'bin/check_main.py'
#
# file_name
file_name = 'xam_main.csv'
#
def main() :
   # check
   if len(sys.argv) != 1 :
      msg = f'{program}: does not expect any arguments'
      sys.exit(msg)
   if sys.argv[0] != program :
      msg = f'{program}: must be executed from the top source directory'
      sys.exit(msg)
   #
   # old_table
   command = [ 'ls', file_name ]
   print(command)
   result = subprocess.run(command)
   if result.returncode != 0 :
      msg  = 'command above failed\n'
      sys.exit(msg)
   old_table = list()
   file_obj  = open( file_name, 'r')
   reader    = csv.DictReader(file_obj)
   for row in reader :
      old_table.append(row)
   file_obj.close()
   #
   # bin/xam_main.py
   command = [ 'bin/xam_main.py' ]
   print(command)
   result = subprocess.run(command)
   if result.returncode != 0 :
      msg  = 'command above failed\n'
      sys.exit(msg)
   #
   # new_table
   new_table = list()
   file_obj  = open(file_name, 'r')
   reader    = csv.DictReader(file_obj)
   for row in reader :
      new_table.append(row)
   file_obj.close()
   #
   # print_error
   print_error = False
   for old_row in old_table :
      package   = old_row['package']
      algorithm = old_row['algorithm']
      found     = False
      for new_row in new_table :
         if package==new_row['package'] and algorithm==new_row['algorithm'] :
            found = True
      if not found :
         if not print_error :
            msg  = 'following (packages, algorithm) are in old but not new '
            msg += file_name 
            print(msg)
            print_error = True
         print( f'( {package}, {algorithm} ' )
   #
   if print_error :
      sys.exit( f'{program}: Erorr' )
   print( f'{program}.py: OK')
#
main()
