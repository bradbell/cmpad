#! /usr/bin/env python3
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin run_cmpad.py}

Main Program Python Implementation
##################################

Documentation
*************
:ref:`run_cmpad-name` .

Example
*******
:ref:`xam_main.py-name`

Source Code
***********
{xrst_literal
   # BEGIN PYTHON
   # END PYTHON
}

{xrst_end run_cmpad.py}
'''
# BEGIN PYTHON
import argparse
import math
import sys
import os
import platform
import numpy
import autograd
import jax
import torch
#
# cmpad_version
cmpad_version = 'cmpad-2024.4.8'
# ----------------------------------------------------------------------------
#
# program
program = 'python/bin/run_cmpad.py'
if not ( os.path.isdir('.git') and sys.argv[0] == program ) :
   msg = f'{program} must be run from cmpad top source directory'
   sys.exit(msg)
#
# python/venv
if not os.path.isdir( 'python/venv' ) :
   msg  = f'{program}: python packages not installed uinsg bin/get_package.sh'
   sys.exit(msg)
#
# sys.prefix
ok = sys.prefix.startswith( os.getcwd() ) and sys.prefix.endswith( 'python/venv' )
if not ok :
   msg  = f'{program}: must first execute the following commands:\n'
   msg += 'source python/venv/bin/activate'
   sys.exit(msg)
#
if not os.path.isdir('python/cmpad') :
   msg = 'expected python/cmpad below top source directory'
   sys.exit(msg)
#
# sys.path
sys.path.insert(0, os.getcwd() + '/python')
python_version  = platform.python_version()
#
(major, minor, patch) = python_version.split('.')
for lib in [ 'lib', 'lib64' ] :
   directory = f'python/build/prefix/{lib}/python{major}.{minor}/site-packages'
   if os.path.isdir(directory) :
      sys.path.insert(0, os.getcwd() + '/' + directory)
# -----------------------------------------------------------------------------
# cmpad
import cmpad
# ----------------------------------------------------------------------------
# none_fun_obj
def none_fun_obj(algorithm) :
   if algorithm == 'det_by_minor' :
      return cmpad.det_by_minor()
   elif algorithm == 'an_ode' :
      return cmpad.an_ode()
   elif algorithm == 'llsq_obj' :
      return cmpad.llsq_obj(numpy)
   else :
      assert False
#
# grad_fun_obj
def grad_fun_obj(algorithm, package) :
   #
   # algo
   if algorithm == 'det_by_minor' :
      algo = cmpad.det_by_minor()
   elif algorithm == 'an_ode' :
      algo = cmpad.an_ode()
   elif algorithm == 'llsq_obj' :
      if package == 'autograd' :
         algo = cmpad.llsq_obj(autograd.numpy)
      elif package == 'cppad_py' :
         algo = cmpad.llsq_obj(numpy)
      elif package == 'jax' :
         algo = cmpad.llsq_obj(jax.numpy)
      elif package == 'pytorch' :
         algo = cmpad.llsq_obj(cmpad.pytorch.like_numpy)
      else :
         assert False
   #
   if package == 'autograd' :
      return cmpad.autograd.gradient(algo)
   elif package == 'cppad_py' :
      return cmpad.cppad_py.gradient(algo)
   elif package == 'jax' :
      return cmpad.jax.gradient(algo)
   elif package == 'pytorch' :
      return cmpad.pytorch.gradient(algo)
   else :
      assert False
   #
   assert False
# ----------------------------------------------------------------------------
def main() :
   #
   # parser
   parser = argparse.ArgumentParser(
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
      help = 'none or an AD package name'
   )
   # --n_other
   parser.add_argument('-o', '--n_other',
      metavar='n_other', default='0',
      help = 'The meaning of this integer is algorithm specific.'
   )
   # --package
   parser.add_argument('-p', '--package',
      metavar='package', default='none',
      help = 'none or an AD package name'
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
   if arguments.version :
      print(cmpad_version)
      return
   #
   # file_name
   file_name = arguments.file_name
   #
   # package
   package = arguments.package
   if package not in [ 'none', 'autograd', 'cppad_py', 'jax', 'pytorch' ] :
      msg = f'{program}: package = {package} is not available'
      sys.exit(msg)
   #
   # algorithm
   algorithm = arguments.algorithm
   if algorithm not in [ 'det_by_minor', 'an_ode', 'llsq_obj' ] :
      msg = f'{program}: algorithm = {algorithm} is not available'
      sys.exit(msg)
   #
   # n_other
   n_other = int( arguments.n_other )
   if algorithm == 'det_by_minor' and n_other != 0 :
      msg = f'{program}: algorithm = {algorithm}: n_other is not zero'
      sys.exit(msg)
   if algorithm == 'an_ode' and n_other <= 0 :
      msg = f'{program}: algorithm = {algorithm}: n_other is <= zero'
      sys.exit(msg)
   #
   # n_arg
   n_arg = int( arguments.n_arg )
   if algorithm == 'det_by_minor' :
      ell = int( math.sqrt( n_arg ) )
      if ell * ell != n_arg :
         msg  = f'{program}: algorithm = {algorithm}: '
         msg += f'n_arg = {n_arg} is not a square'
         sys.exit(msg)
   #
   # min_time
   min_time = float( arguments.min_time )
   if min_time <= 0.0 or 1.0 < min_time :
      msg  = f'{program}: min_time = {min_time} '
      msg += 'is less than or equal zero or greater than one'
      sys.exit(msg)
   #
   # time_setup
   time_setup = arguments.time_setup
   #
   # option
   option = {
      'n_arg'      : n_arg      ,
      'n_other'    : n_other    ,
      'time_setup' : time_setup ,
   }
   #
   # csv_speed
   if package == 'none' :
      fun_obj = none_fun_obj(algorithm)
   else :
      fun_obj = grad_fun_obj(algorithm, package)
   rate    = cmpad.fun_speed(fun_obj, option, min_time)
   special = False
   cmpad.csv_speed(
      file_name, rate, min_time, package, algorithm, special, option
   )
   #
#
main()
# END PYTHON
