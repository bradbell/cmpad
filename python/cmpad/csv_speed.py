# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin py_csv_speed}

Record a Python Speed Result in a Csv File
##########################################

Prototype
*********
{xrst_literal
   # BEGIN DEF
   # END DEF
}

file_name
*********
This is the name of the file were the results will be recorded.
This file uses the :ref:`csv_column-name` format.

#. If the file is empty on input, the following csv header line
   is written as the first line of the file; i.e.,
   {xrst_literal
      xrst/csv_column.xrst
      BEGIN HEADER_LINE
      END HEADER_LINE
   }

#. A line is added to this file corresponding to
   this call to csv_speed.

rate
****
see :ref:`csv_column@rate`

min_time
********
see :ref:`csv_column@min_time`

package
*******
see :ref:`csv_column@package`

algorithm
*********
see :ref:`csv_column@algorithm`

special
*******
see :ref:`csv_column@special`

option
******

n_arg
=====
see :ref:`csv_column@n_arg`

n_other
=======
see :ref:`csv_column@n_other`

time_setup
==========
see :ref:`csv_column@time_setup`


{xrst_toc_hidden
   python/xam/csv_speed.py
}
Example
*******
:ref:`xam_csv_speed.py-name` contains an example and test of this routine.

{xrst_end py_csv_speed}
'''
import os
import csv
import datetime
import platform
#
# bool_str
bool_str = { True : 'true' , False : 'false' }
#
# BEGIN DEF
def csv_speed(
   file_name, rate, min_time, package, algorithm, special, option
   ) :
   assert type(file_name) == str
   assert type(rate)      == float
   assert type(min_time)  == float
   assert type(package)   == str
   assert type(algorithm) == str
   assert type(special)   == bool
   assert type(option)    == dict
   #
   assert package in [ 'none', 'autograd', 'cppad_py', 'pytorch' ]
   #
   assert type( option['n_arg'] )      == int
   assert type( option['n_other'] )    == int
   assert type( option['time_setup'] ) == bool
   # END DEF
   #
   # fieldnames
   filednames = [
      'rate',
      'min_time',
      'package',
      'algorithm',
      'n_arg',
      'n_other',
      'time_setup',
      'date',
      'compiler',
      'debug',
      'language',
      'special'
   ]
   #
   # csv_table
   csv_table = list()
   if os.path.exists( file_name ) :
      file_obj  = open(file_name, 'r')
      reader    = csv.DictReader(file_obj)
      for row in reader :
         csv_table.append(row)
      file_obj.close()
   #
   # date
   date = datetime.date.today().strftime('%Y-%m-%d')
   #
   # debug
   if package != 'cppad_py' :
      debug = ''
   else :
      module        = __import__(package)
      package_file  = module.__file__
      package_path  = os.path.realpath(package_file)
      index         = package_path.find('/python/build/prefix.release/')
      if index < 0 :
         index      = package_path.find('/python/build/prefix.debug/')
      if index < 0 :
         msg  = f'package = {package}, path = {package_path}\n'
         msg += 'is not using version installed by cmpad get_package.sh'
         assert False, msg
      top_srcdir   = package_path[ : index]
      external_dir = f'{top_srcdir}/external'
      if os.path.exists( f'{external_dir}/{package}.debug' ) :
         debug = True
      elif os.path.exists( f'{external_dir}/{package}.release' ) :
         debug = False
      else :
         msg  = f'Using package = {package} but cannot find either of:\n'
         msg += f'{external_dir}/{package}.debug\n'
         msg += f'{external_dir}/{package}.release\n'
         assert False, msg
   #
   # compiler
   compiler = platform.python_implementation()+'-'+platform.python_version()
   #
   row = {
      'rate'       : '{:.1e}'.format(rate),
      'min_time'   : min_time,
      'package'    : package,
      'algorithm'  : algorithm,
      'n_arg'      : option['n_arg'],
      'n_other'    : option['n_other'],
      'time_setup' : bool_str[ option['time_setup'] ],
      'date'       : date,
      'compiler'   : compiler,
      'debug'      : debug,
      'language'   : 'python',
      'special'    : bool_str[special]
   }
   #
   csv_table.append(row)
   #
   # file_name
   file_obj = open(file_name, 'w')
   writer   = csv.DictWriter(file_obj, fieldnames = filednames)
   writer.writeheader()
   for row in csv_table :
      writer.writerow( row )
   file_obj.close()
