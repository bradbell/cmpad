# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin py_csv_speed}
{xrst_spell
   newlines
}

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
is the name of the file were the results will be recorded.

#. This is a csv file. To be specific commas separate columns
   and newlines terminate rows.

#. A line is added to this file corresponding to
   rate in this call to csv_speed.

#. If the file is empty on input, the following csv header line
   is written to the file before the result for this call::

      rate,min_time,package,algorithm,n_arg,date,compiler,debug,language

#. If the file is not empty on input, it is assumed that the header line
   for this file is as above.

rate
****
This is the number of times per second that the algorithm,
or a derivative of the algorithm, was calculated.

min_time
********
This is the :ref:`cpp_fun_speed@min_time` used
by fun_speed when it computed *rate*.

package
*******
This is the name of the AD package that *rate* corresponds to.
If *package* is ``float`` , this is not a derivative calculation
but rather an evaluations of the algorithm using the python type float.

algorithm
*********
This is the name of the algorithm; e.g., :ref:`py_det_by_minor-name` .

n_arg
*****
This is the value of *option*\ ``[n_arg]`` .

time_setup
**********
This is the value of *option*\ ``[time_setup]`` .

date
****
This is the date when csv_speed is called.
The *date* value is automatically determined and not an argument to csv_speed.

compiler
********
This is a string identifying the version of python used for this test.
The *compiler* value
is automatically determined and not an argument to csv_speed.

debug
*****
The *debug* value is automatically determined and not an argument to csv_speed.

#. If *package* is ``double``, this is the empty string.
#. If *package* is not ``double``,
   this is true (false) if *package* was installed using the
   debug (release) :ref:`get_package.py@Syntax@build_type` .

{xrst_toc_hidden
   python/xam/csv_speed.py
}

language
********
This is always ``python`` because this routine is for timing Python functions.


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
def csv_speed(file_name, rate, min_time, package, algorithm, option) :
   assert type(file_name) == str
   assert type(rate)      == float
   assert type(min_time)  == float
   assert type(package)   == str
   assert type(algorithm) == str
   assert type(option)    == dict
   assert type( option['n_arg'] )      == int
   assert type( option['time_setup'] ) == bool
   # END DEF
   # fieldnames
   filednames = [
      'rate',
      'min_time',
      'package',
      'algorithm',
      'n_arg',
      'time_setup',
      'date',
      'compiler',
      'debug',
      'language'
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
   if package == 'double' :
      debug = ''
   else :
      module        = __import__(package)
      package_file  = module.__file__
      package_path  = os.path.realpath(package_file)
      debug_index   = package_path.find('/prefix.debug/')
      release_index = package_path.find('/prefix.release/')
      if 0 <= debug_index and 0 <= release_index :
         msg  = f'package = {package}, path = {file_path}\n'
         msg += 'Contains both /prefix.debug/ and /prefix.release/'
         assert msg, False
      if debug_index < 0 and release_index < 0 :
         msg  = f'package = {package}, path = {file_path}\n'
         msg += 'Does not contain /prefix.debug/ or /prefix.release/'
         assert msg, False
      if 0 < debug_index :
         debug = 'true'
      else :
         debug = 'false'
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
      'time_setup' : bool_str[ option['time_setup'] ],
      'date'       : date,
      'compiler'   : compiler,
      'debug'      : debug,
      'language'   : 'python'
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
