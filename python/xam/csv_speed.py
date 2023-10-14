# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin xam_csv_speed.py}

Example and Test of Python csv_speed
####################################

Source Code
***********
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end xam_csv_speed.py}
'''
# BEGIN PYTHON
import os
import cmpad
import pathlib
import platform
import csv
#
# xam_csv_speed
def xam_csv_speed() :
   #
   # ok
   ok = True
   #
   # build_dir
   this_file = pathlib.Path(__file__).resolve()
   repo_dir  = this_file.parent.parent.parent
   build_dir = repo_dir.joinpath('build')
   #
   # file_name
   file_name = str ( build_dir.joinpath('csv_speed.csv') )
   if os.path.exists( file_name ) :
      os.remove( file_name )
   #
   # min_time
   min_time = 0.1
   #
   # package
   package = 'double'
   #
   # algorithm
   algorithm = 'det_by_minor'
   #
   # option
   option = { 'n_arg' : 4, 'g_index' : 0, 'time_setup' : False }
   #
   # fun_obj
   fun_obj = cmpad.det_by_minor()
   #
   # rate
   rate = cmpad.fun_speed(fun_obj, option, min_time)
   #
   # csv_speed
   cmpad.csv_speed(
      file_name, rate, min_time, package, algorithm, option
   )
   #
   # csv_table
   file_obj  = open(file_name, 'r')
   reader    = csv.DictReader(file_obj)
   csv_table = list()
   for row in reader :
      csv_table.append(row)
   file_obj.close()
   #
   # language
   language = 'python'
   #
   # compiler
   compiler = platform.python_implementation()+'-'+platform.python_version()
   #
   # ok
   ok = len( csv_table ) == 1
   #
   # ok
   col_names = [
      'rate',
      'min_time',
      'package',
      'algorithm',
      'n_arg',
      'g_index',
      'time_setup',
      'date',
      'compiler',
      'debug',
      'language'
   ]
   ok = list( csv_table[0].keys() ) == col_names
   #
   # str2bool
   str2bool = { 'true' : True, 'false' : False }
   #
   # ok
   row = csv_table[0]
   ok &= float( row['min_time'] )       == min_time
   ok &= row['package']                 == 'double'
   ok &= int( row['n_arg'] )            == option['n_arg']
   ok &= int( row['g_index'] )          == option['g_index']
   ok &= str2bool[ row['time_setup'] ]  == option['time_setup']
   ok &= row['compiler']                == compiler
   ok &= row['language']                == 'python'
   #
   return ok
#
# test_csv_speed
def test_csv_speed() :
   assert xam_csv_speed() == True
# END PYTHON
