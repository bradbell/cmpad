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
   cpp/src/parse_args.hpp
   // BEGIN ARGUMENTS_T
   // END ARGUMENTS_T
}

.. csv-table::
   :widths: auto
   :header-rows: 1

   argument, meaning
   algorithm,   see :ref:`cpp_run_cmpad@algorithm`
   file_name,   see :ref:`cpp_run_cmpad@file_name`
   min_time,    see :ref:`cpp_run_cmpad@min_time`
   package,     see :ref:`cpp_run_cmpad@package`
   n_arg,       see :ref:`cpp_run_cmpad@n_arg`
   time_setup,  see :ref:`cpp_run_cmpad@time_setup`

{xrst_end parse_args}
*/
// see http://www.crasseux.com/books/ctutorial/argp-example.html
# include <iostream>
# include <stdlib.h>
# include <getopt.h>
# include <cmpad/configure.hpp>
# include "parse_args.hpp"

// BEGIN PROTOTYPE
arguments_t parse_args(int argc, char* argv[])
// END PROTOTYPE
{
   arguments_t arguments;
   // BEGIN DEFAULT ARGUMENTS
   arguments.algorithm  = "det_by_minor";
   arguments.file_name  = "cmpad.csv";
   arguments.min_time   = 0.5;
   arguments.package    = "double";
   arguments.n_arg      = 9;
   arguments.time_setup = false;
   // END DEFAULT ARGUMENTS
   //
   // long_options
   struct option long_options[] =
   {  // name,         has_arg,            *flag,            val
      { "algorithm",   required_argument,  0,                'a' },
      { "file_name",   required_argument,  0,                'f' },
      { "min_time",    required_argument,  0,                'm' },
      { "n_arg",       required_argument,  0,                'n' },
      { "package",     required_argument,  0,                'p' },
      // flags
      { "version",     no_argument,        0,                'v' },
      { "help",        no_argument,        0,                'h' },
      { "time_setup",  no_argument,        0,                't' },
      {0,              0,                  0,                 0  }
   };
   //
   // shortopts
   // one : means option is required.
   const char* shortopts = "a:f:m:n:p:vht";
   //
   // error_msg
   std::string error_msg = "";
   //
   // version
   bool version = false;
   //
   // help
   bool help = false;
   //
   // c
   int c = -2;
   while( c != -1 && error_msg == "" )
   {  //
      //
      // option_index
      int option_index = 0;
      //
      // c
      c = getopt_long(argc, argv, shortopts, long_options, &option_index);
      switch(c)
      {  // -1
         case -1:
         break;
         //
         // 0
         case 0:
         error_msg = "cmpad: exiting due to program error";
         break;
         //
         // algorithm
         case 'a':
         arguments.algorithm = optarg;
         break;
         //
         // file_name
         case 'f':
         arguments.file_name = optarg;
         break;
         //
         // min_time
         case 'm':
         arguments.min_time = std::atof( optarg );
         break;
         //
         // n_arg
         case 'n':
         arguments.n_arg = size_t( std::atoi( optarg ) );
         break;
         //
         // package
         case 'p':
         arguments.package = optarg;
         break;
         //
         // version
         case 'v':
         version = true;
         break;
         //
         // help
         case 'h':
         help = true;
         break;
         //
         // time_setup
         case 't':
         arguments.time_setup = true;
         break;
         //
         // ?
         case '?':
         error_msg  = "cmpad: exiting due to option error";
         break;
         //
         // default:
         error_msg = "cmapd: program error";
         break;
      }
   };
   if( error_msg != "" )
   {  std::cerr << error_msg << "\n";
      std::exit(1);
   }
   if( help )
   {  const char* usage =
         "cmpad: Compare C++ AD packages\n\n"
         "-a: --algorithm:  string: "
            "is one of { det_by_minor, an_ode} [det_by_minor]\n"
         "-f: --file_name:  string: "
            "csv file that line is added to [cmpad.csv]\n"
         "-m: --min_time:   double: "
            "minimum time in seconds to average computation rate [0.5]\n"
         "-n: --n_arg:      size_t: "
            "size of argument to algorithm [9]\n"
         "-p: --pakcage:    string: "
            "double or an AD packae name [double]\n"
         "-t: --time_setup:       : "
            "if present, include setup time in speed [false]\n"
         "-v: --version:          : "
            "if present, print the cmpad version number and halt [false]\n"
         "-h: --help:             : "
            "if present, print this message and halt [false]\n"
         "\nValues between '[' and ']' above are defaults.\n";
      std::cout << usage;
      std::exit(0);
   }
   if( version )
   {  std::cout << CMPAD_VERSION << "\n";
      std::exit(0);
   }
   //
   return arguments;
}
