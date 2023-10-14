// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef SRC_PARSE_ARGS_HPP
# define SRC_PARSE_ARGS_HPP

# include <string>

// BEGIN ARGUMENTS_T
struct arguments_t
{
   std::string  algorithm;
   std::string  file_name;
   size_t       g_index;
   double       min_time;
   std::string  package;
   size_t       n_arg;
   bool         time_setup;
};
// END ARGUMENTS_T

// parse_args
arguments_t parse_args(int argc, char* argv[]);

# endif
