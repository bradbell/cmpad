# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
import os
import csv
import datetime
import platform
#
def csv_speed(file_name, rate, min_time, package, algorithm, option) :
   #
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
   row = {
      'rate'       : rate,
      'min_time'   : min_time,
      'package'    : package,
      'algorithm'  : algorithm,
      'n_arg'      : option['n_arg'],
      'time_setup' : option['time_setup'],
      'date'       : date,
      'compiler'   : platform.python_version(),
      'debug'      : __debug__,
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
      
