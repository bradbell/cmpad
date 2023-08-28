// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin main}

The cmpad Main Program
######################

Syntax
******
| ``cmpad`` *options*

Options
*******
All of the options below have a default value that is used
when the option is not present.

.. csv-table::
   :header-rows: 1

   short version, long version
   ``-a`` *algorithm* , ``--algorithm`` = *algorithm*
   ``-f`` *file_name* , ``--file_name`` = *file_name*
   ``-m`` *min_time*  , ``--min_time`` = *min_time*
   ``-p`` *package*   , ``--package`` = *package*
   ``-s`` *size*      , ``--size`` = *size*
   ``-t``             , ``--time_setup``


algorithm
*********
The only choice (so far) for this option is :ref:`det_by_minor-name` .
The default value for this option is ``det_by_minor`` .

file_name
*********
is the csv file where the results of this test are placed.
If the file does not exist,
the file is created and it's header row is written.
The results for this test are placed at the end of the file.
The default value for this option is ``cmpad.csv`` .

min_time
********
This is the minimum time in seconds for the timing of the computation.
The computation will be repeated enough times so that this minimum time
is reached.

package
*******
This is either ``double`` or the AD package used for this test.
The possible AD packages are:
double, adolc, autodiff, cppad, cppad_jit, cppadcg, or sacado.
Note that cppad_jit is the JIT compiled version of cppad derivatives.
The default value for this option is ``double`` .

size
****
This is the size of the argument to the algorithm.
The meaning of this value depends on the algorithm; e.g.,
for det_by_minor it is the row and column dimension of the matrix.
The default value for this option is ``5`` .

time_setup
**********
If this option is present, the setup time is included during the speed
testing for this algorithm.
So AD packages may spend more setup time to use less evaluation time
for each new argument value.
The default value for this option is ``false`` .

{xrst_toc_table
   src/parse_args.cpp
}

{xrst_end main}
*/
# include <algorithm>
# include <string>
# include <iostream>
# include <cmpad/vector.hpp>
# include <cmpad/option_t.hpp>
# include <cmpad/algo/det_by_minor.hpp>
# include <cmpad/fun_speed.hpp>
# include <cmpad/csv_speed.hpp>
# include "parse_args.hpp"

# if CMPAD_HAS_ADOLC
# include <cmpad/adolc/gradient.hpp>
# endif
# if CMPAD_HAS_AUTODIFF
# include <cmpad/autodiff/gradient.hpp>
# endif
# if CMPAD_HAS_CPPAD
# include <cmpad/cppad/gradient.hpp>
# endif
# if CMPAD_HAS_CPPAD_JIT
# include <cmpad/cppad_jit/gradient.hpp>
# endif
# if CMPAD_HAS_CPPADCG
# include <cmpad/cppadcg/gradient.hpp>
# endif
# if CMPAD_HAS_SACADO
# include <cmpad/sacado/gradient.hpp>
# endif

// CMPAD_PACKAGE_TEST
# define CMPAD_PACKAGE_TEST(package) \
   if( algorithm == "det_by_minor" ) \
   {  cmpad::package::gradient<cmpad::det_by_minor> grad_det; \
      double rate = cmpad::fun_speed(grad_det, option, min_time); \
      cmpad::csv_speed(file_name, rate, #package , algorithm, option); \
      case_found = true; \
   }

int main(int argc, char* argv[])
{  //
   // arguments
   arguments_t arguments = parse_args(argc, argv);
   //
   // package_vec
   cmpad::vector<std::string> package_vec;
   package_vec.push_back("double");
# if CMPAD_HAS_ADOLC
   package_vec.push_back("adolc");
# endif
# if CMPAD_HAS_CPPAD
   package_vec.push_back("cppad");
# endif
# if CMPAD_HAS_CPPAD_JIT
   package_vec.push_back("cppad_jit");
# endif
# if CMPAD_HAS_CPPADCG
   package_vec.push_back("cppadcg");
# endif
# if CMPAD_HAS_SACADO
   package_vec.push_back("sacado");
# endif
   //
   // algorithm_vec
   cmpad::vector<std::string> algorithm_vec;
   algorithm_vec.push_back("det_by_minor");
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
   {  std::cerr << "cmpad Error: ";
      std::cerr << "package = " << package << " is not available" << "\n";
      return 1;
   }
   //
   // algorithm
   std::string algorithm = arguments.algorithm;
   itr = std::find(algorithm_vec.begin(), algorithm_vec.end(), algorithm);
   if( itr == algorithm_vec.end() )
   {  std::cerr << "cmpad Error: ";
      std::cerr << "algorithm = " << algorithm << " is not available" << "\n";
      return 1;
   }
   //
   // size
   size_t size = arguments.size;
   if( size == 0 || 10 < size )
   {  std::cerr << "cmpad Error: size = ";
      std::cerr << size << " is zero or greater than ten.\n";
      return 1;
   }
   //
   // time_setup
   bool time_setup = arguments.time_setup;
   //
   // min_time
   double min_time = arguments.min_time;
   if( min_time <= 0.0 || 1.0 < min_time )
   {  std::cerr << "cmpad Error: min_time = ";
      std::cerr << min_time <<
         " is less than or equal zero or greater than one.\n";
      return 1;
   }
   //
   // option
   cmpad::option_t option;
   option.size       = size;
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
         cmpad::csv_speed(file_name, rate, "double", algorithm, option);
         case_found = true;
      }
   }
   //
   // file_name, case_found
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

