# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
import argparse
import math
#
# cmpad_version
cmpad_version = 'cmpad-2023.9.25'
# ----------------------------------------------------------------------------
# grad_fun_obj
def grad_fun_obj(algorithm, package) :
   #
   # algo
   if algorithm == 'det_py_minor' :
      algo = cmpad.det_by_minor()

   elif algorithm == 'an_ode' :
      algo = cmpad.an_ode()
   else :
      msg = f'algorithm = {algorithm} is not implemented'
      assert msg, False
   #
   if package == 'cppad_py' :
      return cmpad.cppad_py.gradient(algo)
   else :
      msg = f'package = {package} is not implemented'
      assert msg, False
   #
   assert False
# ----------------------------------------------------------------------------
def run_cmpad() :
   #
   # program
   program = 'run_cmpad.py'
   #
   # parser
   parser = argeparse.ArgumentParser(
      prog = program, description = 'compare AD packages'
   )
   # --algorithm
   parser.add_argument('-a', '--algorithm',
      metavar='algorithm', default='det_by_minor',
      help = 'is one of { det_by_minor}'
   )
   # --file_name
   parser.add_argument('-f', '--file_name',
      metavar='file_name', default='cmpad.csv',
      help = 'csv file that the line is added to'
   )
   # --min_time
   parser.add_argument('-m', '--min_time',
      metavar='min_time', default='0.5',
      help = 'minimum time in seconds to average computation rate'
   )
   # --n_arg
   parser.add_argument('-n', '--n_arg',
      metavar='n_arg', default='9',
      help = 'double or an AD package name'
   )
   # --package
   parser.add_argument('-p', '--package',
      metavar='package', default='double',
      help = 'double or an AD package name'
   )
   # --time_setup
   parser.add_argument('-t', '--time_setup', action='store_true',
      help = 'if present, include setup time in speed tests'
   )
   # --version
   parser.add_argument('-v', '--version', action='store_true',
      help = 'if present, print the cmpad version number and halt'
   )
   #
   # arguments
   arguments = parser.parse_args()
   #
   # version
   if( arguments.version )
   {  print(cppad_version)
      return
   }
   #
   # package
   package = arguments.package
   if package not in [ 'cppad_py' ] :
   {  msg = f'{program}: package = {package} is not available'
      sys.exit(msg)
   }
   #
   # algorithm
   algorithm = arguments.algorithm
   if algorithm not in [ 'det_by_minor' ] :
   {  msg = f'{program}: algorithm = {algorithm} is not available'
      sys.exit(msg)
   }
   #
   # n_arg
   n_arg = int( arguments.n_arg )
   if( algorithm == 'det_by_minor' )
   {  ell = int( math.sqrt( n_arg ) )
      if ell * ell != n_arg :
      {  msg  = f'{program}: algorithm = {algorithm}: '
         msg += f'n_arg = {n_arg} is not a square'
         sys.exit(msg)
      }
   }
   #
   # min_time
   min_time = float( arguments.min_time )
   if( min_time <= 0.0 or 1.0 < min_time )
   {  msg  = f'{program}: min_time = {min_time} '
      msg += 'is less than or equal zero or greater than one'
      sys.exit(msg)
   }
   #
   # time_setup
   time_setup = arguments.time_setup
   #
   # option
   option = {
      'n_arg'      : n_arg ,
      'time_setup' : time_setup,
   }
   #
   # rate
   fun_obj = grad_fun_obj(algorithm, package)
   rate    = cmpad.fun_speed(fun_obj, option, min_time)
   #
   # csv_speed
   cmpad.csv_speed(file_name, rate, min_time, package, algorithm, option)
