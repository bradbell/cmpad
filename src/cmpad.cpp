// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# include <algorithm>
# include <string>
# include <iostream>
# include <cmpad/vector.hpp>
# include <cmpad/option_t.hpp>
# include <cmpad/algo/det_by_minor.hpp>
# include <cmpad/fun_speed.hpp>
# include <cmpad/csv_speed.hpp>

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
      double rate = cmpad::fun_speed(grad_det, option, time_min); \
      cmpad::csv_speed(file_name, rate, #package , algorithm, option); \
      case_found = true; \
   }

int main(int argc, const char* argv[])
{  //  
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
   // usage
   std::string usage = 
      "cmpad file_name package algorithm size time_setup time_min";
   usage += "\nfile_name:  name of csv file where results are written";
   usage += "\npackage:    one of";
   for(size_t i = 0; i < package_vec.size(); ++i)
   {  if( i == package_vec.size() - 1)
         usage += " or";
      else if( 0 < i )
         usage += ",";
      usage += " " + package_vec[i];
   }
   usage += "\nalgorithm:  one of";
   for(const std::string& algorithm : algorithm_vec)
      usage += " " + algorithm;
   usage += "\nsize:       a positive integer";
   usage += "\ntime_setup: true or false";
   usage += "\ntime_min:   positive floating point value <= 1.0";
   usage += "\n\n";
   //
   // argc
   if( argc != 7 )
   {  std::cerr << usage;
      std::cerr << "expected 6 arguments and found " << argc - 1 << "\n";
      return 1;
   }
   //
   // itr;
   cmpad::vector<std::string>::iterator itr;
   //
   // i_arg
   size_t i_arg = 0;
   //
   // file_name, i_arg
   std::string file_name = argv[++i_arg];
   //
   // package, i_arg
   std::string package = argv[++i_arg];
   itr = std::find(package_vec.begin(), package_vec.end(), package);
   if( itr == package_vec.end() )
   {  std::cerr << "cmpad Error: ";
      std::cerr << "package = " << package << " is not available" << "\n";
      return 1;
   }
   //
   // algorithm, i_arg
   std::string algorithm = argv[++i_arg];
   itr = std::find(algorithm_vec.begin(), algorithm_vec.end(), algorithm);
   if( itr == algorithm_vec.end() )
   {  std::cerr << "cmpad Error: ";
      std::cerr << "algorithm = " << algorithm << " is not available" << "\n";
      return 1;
   }
   //
   // size, i_arg
   int size_int = std::atoi( argv[++i_arg] );
   if( size_int <= 0 )
   {  std::cerr << "cmpad Error: ";
      std::cerr << "size = " << size_int << " is not available" << "\n";
      return 1;
   }
   size_t size = size_t(size_int);
   //
   // time_setup, i_arg
   std::string time_setup_str = argv[++i_arg];
   if( time_setup_str != "true" && time_setup_str != "false" )
   {  std::cerr << "cmpad Error: time_setup = ";
      std::cerr << time_setup_str << " is not true or false\n";
      return 1;
   }
   bool time_setup = time_setup_str == "true";
   //
   // time_min, i_arg
   double time_min = std::atof( argv[++i_arg] );
   if( time_min <= 0.0 || 1.0 < time_min )
   {  std::cerr << "cmpad Error: time_min = ";
      std::cerr << time_min << " is not greater than zero and less than one\n";
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
         double rate = cmpad::fun_speed(det, option, time_min);
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



 

