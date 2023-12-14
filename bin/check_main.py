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
   command = [ 'git', 'checkout' , file_name ]
   print( ' '.join(command) )
   result = subprocess.run(command)
   if result.returncode != 0 :
      msg  = ' '.join(command)
      msg += f'\n{program}: command above failed'
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
   print( ' '.join(command) )
   result = subprocess.run(command)
   if result.returncode != 0 :
      msg  = ' '.join(command)
      msg += f'\n{program}: command above failed'
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
      package    = old_row['package']
      algorithm  = old_row['algorithm']
      time_setup = old_row['time_setup']
      found     = False
      for new_row in new_table :
         if package == new_row['package'] :
            if algorithm == new_row['algorithm'] :
               if time_setup == new_row['time_setup'] :
                  found = True
      if not found :
         if not print_error :
            msg  = 'following (packages, algorithm, time_setup) are in '
            msg += f'the old but not new {file_name}'
            print(msg)
            print_error = True
         print( f'( {package}, {algorithm}, {time_setup} ) ' )
   #
   if print_error :
      sys.exit( f'{program}: Erorr' )
   #
   # print_warning
   print_warning = False
   for new_row in new_table :
      package    = new_row['package']
      algorithm  = new_row['algorithm']
      time_setup = new_row['time_setup']
      found     = False
      for old_row in old_table :
         if package == old_row['package'] :
            if algorithm == old_row['algorithm'] :
               if time_setup == old_row['time_setup'] :
                  found = True
      if not found :
         if not print_warning :
            msg  = 'following (packages, algorithm, time_setup) are in '
            msg += f'the new but not old {file_name}'
            print(msg)
            print_warning = True
         print( f'( {package}, {algorithm}, {time_setup} ) ' )
   #
   print( f'{program}.py: OK')
#
main()
