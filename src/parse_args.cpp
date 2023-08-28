// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin parse_args}

Parse Command Line Arguments
############################

Prototype
*********
{xrst_literal
   // BEGIN PROTOTYPE
   // END PROTOTYPE
}

arguments_t
***********
{xrst_literal
   src/parse_args.hpp
   // BEGIN ARGUMENTS_T
   // END ARGUMENTS_T
}

.. csv-table::
   :header-rows: 1

   option name, meaning
   algorithm, see :ref:`main@algorithm`
   file_name, see :ref:`main@file_name`
   time_min, see :ref:`main@time_min`
   package, see :ref:`main@package`
   size, see :ref:`main@size`
   time_setup, see :ref:`main@time_setup`

{xrst_end parse_args}
*/
# include <stdlib.h>
# include <argp.h>
# include "parse_args.hpp"

namespace { 

   error_t next_arg(int key, char* arg, argp_state* state)
   {  // arugments
      arguments_t* arguments = reinterpret_cast<arguments_t*>(state->input);
      //
      // key
      switch( key )
      {
         // algorithm
         case 'a':
         arguments->algorithm = arg;
         break;
   
         // file_name
         case 'f':
         arguments->file_name = arg;
         break;
   
         // time_min
         case 'm':
         arguments->time_min = std::atof(arg);
         break;
   
         // package
         case 'p':
         arguments->package = arg;
         break;
   
         // size
         case 's':
         arguments->size = size_t( std::atoi(arg) );
         break;
   
         // time_setup
         case 't':
         arguments->time_setup = true;
         break;
   
         // default
         default:
         return ARGP_ERR_UNKNOWN;
         break;
      }
      return 0;
   }

}; 

// BEGIN PROTOTYPE
arguments_t parse_args(int argc, char* argv[])
// END PROTOTYPE
{  
   // BEGIN DEFAULT ARGUMENTS
   arguments_t arguments;
   arguments.algorithm  = "det_by_minor";
   arguments.file_name  = "cmpad.csv";
   arguments.time_min   = 0.5;
   arguments.package    = "double";
   arguments.size       = 5;
   arguments.time_setup = false;
   // END DEFAULT ARGUMENTS
   //
   // algorithm_help
   const char* algorithm_help = "is one of { "
      "det_by_minor"
      " } [defualt: det_by_minor]";
   //
   // file_name_help
   const char* file_name_help = 
      "csv file that result is added to [default: cmpad.csv]";
   //
   // time_min_help
   const char* time_min_help = 
      "minumum number of seconds to average speed over [default: 0.5]";
   //
   // package_help
   const char* package_help = "is one of { "
      "double, adolc, autodiff, cppad, cppad_jit, cppadcg, sacado"
      " } [default: double]";
   //
   // size_help
   const char* size_help = "size of argument to algorithm [default: 5]";
   //
   // time_setup_help
   const char* time_setup_help = 
      "include setup time in speed tests [default: false]";
   //
   // options
   argp_option options[] = {
      // option_name,  key, value_name,   flag, help
      {  "algorithm",   'a', "string",    0, algorithm_help},
      {  "file_name",  'f', "string",     0, file_name_help },
      {  "time_min",    'm', "double",    0, time_min_help},
      {  "package",     'p', "string",    0, package_help},
      {  "size",        's', "size_t",    0, size_help},
      {  "time_setup",  't', 0,           0, time_setup_help},
      { 0 }
   };
   //
   // doc
   const char* doc = "Compare C++ AD package speeds";
   //
   // args_doc
   const char* args_doc = nullptr;
   //
   // argp
   argp argparse = { options, next_arg, args_doc, doc };
   //
   // arguments
   argp_parse(&argparse, argc, argv, 0, 0, &arguments);
   //
   // arguments
   return arguments;
};


