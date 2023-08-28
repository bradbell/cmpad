# ifndef SRC_PARSE_ARGS_HPP
# define SRC_PARSE_ARGS_HPP

# include <string>

// BEGIN ARGUMENTS_T
struct arguments_t
{  
   std::string  algorithm;
   std::string  file_name;
   double       time_min;
   std::string  package;
   size_t       size;
   bool         time_setup;
};
// END ARGUMENTS_T

// parse_args
arguments_t parse_args(int argc, char* argv[]);

# endif
