// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin_parent cpp_run_cmpad}

The cmpad Main Program
######################

Syntax
******
| |tab| ``cmpad`` *arguments*

Arguments
*********
All of the arguments below have a default value that is used
when the argument is not present.

.. csv-table::
   :widths: auto
   :header-rows: 1

   short version, long version
   ``-a``  *algorithm* , ``--algorithm``  *algorithm*
   ``-f``  *file_name* , ``--file_name``  *file_name*
   ``-m``  *min_time*  , ``--min_time``   *min_time*
   ``-n``  *n_arg*     , ``--n_arg``      *n_arg*
   ``-p``  *package*   , ``--package``    *package*
   ``-t``              , ``--time_setup``
   ``-v``              , ``--version``
   ``-h``              , ``--help``

Defaults
========
{xrst_literal
   cpp/src/parse_args.cpp
   // BEGIN DEFAULT ARGUMENTS
   // END DEFAULT ARGUMENTS
}


algorithm
*********
The only choices (so far) for this argument are :ref:`cpp_det_by_minor-name`
and :ref:`an_ode-name` .

det_by_minor
============
If *algorithm* is ``det_by_minor``, *n_arg* must be a square
and its square root is the row and column dimension of the matrix.

file_name
*********
is the csv file where the results of this test are placed.
If the file does not exist,
the file is created and it's header row is written.
The results for this test are placed at the end of the file.

min_time
********
This is the minimum time in seconds to average the computation rate over.
The computation will be repeated enough times so that this minimum time
is reached.

n_arg
*****
This is the size of the argument to the algorithm; i.e.,
its the dimension of its :ref:`cpp_fun_obj@domain` space.

package
*******
This is either ``double`` or the AD package used for this test.
The possible AD packages are:
double, adolc, autodiff, cppad, cppad_jit, cppadcg, or sacado.
Note that cppad_jit is the JIT compiled version of cppad derivatives.

time_setup
**********
If this argument is present, the setup time is included during the speed
testing for this algorithm.
Some AD packages may spend more setup time to use less evaluation time
for each new argument value.

version
*******
If this argument is present,
print the cmpad version number on standard out and then exit program
without any further processing.

help
****
If this argument is present,
print the help message on standard out and then exit program
without any further processing.

{xrst_toc_hidden before
   bin/cpp/xam_main.py
}
Example
*******
The file :ref:`xam_main.py-name`
is an example and test that uses this program.

{xrst_end cpp_run_cmpad}
------------------------------------------------------------------------------
{xrst_begin run_cmpad.cpp}

Main Program Implementation
###########################

Subroutines
***********
{xrst_toc_table
   cpp/src/parse_args.cpp
}

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end run_cmpad.cpp}
*/
// BEGIN C++
# include <algorithm>
# include <string>
# include <iostream>
# include <cmpad/vector.hpp>
# include <cmpad/option_t.hpp>
# include <cmpad/algo/det_by_minor.hpp>
# include <cmpad/algo/an_ode.hpp>
# include <cmpad/fun_speed.hpp>
# include <cmpad/csv_speed.hpp>
# include "parse_args.hpp"

# include <cmpad/adept/gradient.hpp>
# include <cmpad/adolc/gradient.hpp>
# include <cmpad/autodiff/gradient.hpp>
# include <cmpad/cppad/gradient.hpp>
# include <cmpad/cppad_jit/gradient.hpp>
# include <cmpad/cppadcg/gradient.hpp>
# include <cmpad/sacado/gradient.hpp>

// CMPAD_PACKAGE_TEST
# define CMPAD_PACKAGE_TEST(package) \
   if( algorithm == "det_by_minor" ) \
   {  cmpad::package::gradient<cmpad::det_by_minor> grad_det; \
      double rate = cmpad::fun_speed(grad_det, option, min_time); \
      cmpad::csv_speed( \
         file_name, rate, min_time, #package , algorithm, option \
      ); \
      case_found = true; \
   } \
   else if( algorithm == "an_ode" ) \
   {  cmpad::package::gradient<cmpad::an_ode> grad_det; \
      double rate = cmpad::fun_speed(grad_det, option, min_time); \
      cmpad::csv_speed( \
         file_name, rate, min_time, #package , algorithm, option \
      ); \
      case_found = true; \
   }


// get_package_available
cmpad::vector<std::string> get_package_available(void)
{  cmpad::vector<std::string> package_available;
   package_available.push_back("double");
# if CMPAD_HAS_ADEPT
   package_available.push_back("adept");
# endif
# if CMPAD_HAS_ADOLC
   package_available.push_back("adolc");
# endif
# if CMPAD_HAS_AUTODIFF
   package_available.push_back("autodiff");
# endif
# if CMPAD_HAS_CPPAD
   package_available.push_back("cppad");
# endif
# if CMPAD_HAS_CPPAD_JIT
   package_available.push_back("cppad_jit");
# endif
# if CMPAD_HAS_CPPADCG
   package_available.push_back("cppadcg");
# endif
# if CMPAD_HAS_SACADO
   package_available.push_back("sacado");
# endif
   return package_available;
}

int main(int argc, char* argv[])
{  //
   // arguments
   arguments_t arguments = parse_args(argc, argv);
   //
   // package_vec
   cmpad::vector<std::string> package_vec = get_package_available();
   //
   // algorithm_vec
   cmpad::vector<std::string> algorithm_vec;
   algorithm_vec.push_back("det_by_minor");
   algorithm_vec.push_back("an_ode");
   //
   // itr
   cmpad::vector<std::string>::iterator itr;
   //
   // file_name
   std::string file_name = arguments.file_name;
   //
   // package
   std::string package = arguments.package;
   itr = std::find(package_vec.begin(), package_vec.end(), package);
   if( itr == package_vec.end() )
   {  std::cerr << "run_cmpad Error: ";
      std::cerr << "package = " << package << " is not available" << "\n";
      return 1;
   }
   //
   // algorithm
   std::string algorithm = arguments.algorithm;
   itr = std::find(algorithm_vec.begin(), algorithm_vec.end(), algorithm);
   if( itr == algorithm_vec.end() )
   {  std::cerr << "run_cmpad Error: ";
      std::cerr << "algorithm = " << algorithm << " is not available" << "\n";
      return 1;
   }
   //
   // n_arg
   size_t n_arg = arguments.n_arg;
   if( algorithm == "det_by_minor" )
   {  size_t ell = size_t( std::sqrt( double(n_arg) ) );
      if( ell * ell != n_arg )
         ++ell;
      if( ell * ell != n_arg )
      {  std::cerr << "run_cmpad Error: algorithm = " << algorithm
                   << ": n_arg = " << n_arg << " is not a square.\n";
         return 1;
      }
   }
   //
   // time_setup
   bool time_setup = arguments.time_setup;
   //
   // min_time
   double min_time = arguments.min_time;
   if( min_time <= 0.0 || 1.0 < min_time )
   {  std::cerr << "run_cmpad Error: min_time = ";
      std::cerr << min_time <<
         " is less than or equal zero or greater than one.\n";
      return 1;
   }
   //
   // option
   cmpad::option_t option;
   option.n_arg       = n_arg;
   option.time_setup = time_setup;
   //
   // case_found
   bool case_found = false;
   //
   // file_name, case_found
   if( package == "double" )
   {  if( algorithm == "det_by_minor" )
      {  cmpad::det_by_minor<double> det;
         double rate = cmpad::fun_speed(det, option, min_time);
         cmpad::csv_speed(
            file_name, rate, min_time, "double", algorithm, option
         );
         case_found = true;
      }
      if( algorithm == "an_ode" )
      {  cmpad::an_ode<double> det;
         double rate = cmpad::fun_speed(det, option, min_time);
         cmpad::csv_speed(
            file_name, rate, min_time, "double", algorithm, option
         );
         case_found = true;
      }
   }
   //
   // file_name, case_found
# if CMPAD_HAS_ADEPT
   else if( package == "adept" )
   {  CMPAD_PACKAGE_TEST(adept) }
# endif
# if CMPAD_HAS_ADOLC
   else if( package == "adolc" )
   {  CMPAD_PACKAGE_TEST(adolc) }
# endif
   //
   // file_name, case_found
# if CMPAD_HAS_AUTODIFF
   else if( package == "autodiff" )
   {  CMPAD_PACKAGE_TEST(autodiff) }
# endif
   //
   // file_name, case_found
# if CMPAD_HAS_CPPAD
   else if( package == "cppad" )
   {  CMPAD_PACKAGE_TEST(cppad) }
# endif
   //
   // file_name, case_found
# if CMPAD_HAS_CPPAD_JIT
   else if( package == "cppad_jit" )
   {  CMPAD_PACKAGE_TEST(cppad_jit) }
# endif
   //
   // file_name, case_found
# if CMPAD_HAS_CPPADCG
   else if( package == "cppadcg" )
   {  CMPAD_PACKAGE_TEST(cppadcg) }
# endif
   //
   // file_name, case_found
# if CMPAD_HAS_SACADO
   else if( package == "sacado" )
   {  CMPAD_PACKAGE_TEST(sacado) }
# endif
   //
   if( case_found )
      return  0;
   //
   std::cerr << "cmpad: BUG\n";
   return 1;
}
// END C++
