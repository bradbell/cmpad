#! /usr/bin/env python
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
# ---------------------------------------------------------------------------
import sys
import os
import re
#
# file_in, file_out
if len( sys.argv ) != 3 :
   msg = 'bin/cpp2py.py file_in file_out'
   sys.exit(msg)
file_in  = sys.argv[1]
file_out = sys.argv[2]
if not os.path.isfile( file_in ) :
   msg = f'cpp2py.py: file_in = {file_in} is not a file'
   sys.exit(msg)
if os.path.exists( file_out ) :
   msg = f'cpp2py.py: file_out = {file_out} exists. Replace it [y/n] ?'
   ch  = input(msg)
   if ch != 'y' :
      msg = 'cpp2py.py: Do not want to replace file above so aborting.'
      sys.exit(msg)
#
# file_data
file_obj  = open(file_in, 'r')
file_data = file_obj.read()
file_obj.close()
#
# cmpad::vector<type_name> var = { ... }
pattern = r'cmpad::vector<\w+> *(\w+) *= *{([^}]*)}'
replace = r'\1 = [\2]'
file_data = re.sub(pattern, replace, file_data)
#
# cmpad::vector<type_name> var ( expression )
pattern = r'cmpad::vector<\w+> *(\w+) *\(([^)]*)\)'
replace = r'\1 = (\2) * [0]'
file_data = re.sub(pattern, replace, file_data)
#
# assert( expressioon );
pattern = r'assert\((.*)\);'
replace = r'assert \1'
file_data = re.sub(pattern, replace, file_data)
#
# variable.size()
pattern = r'(\w+)[.]size\(\)'
replace = r'len(\1)'
file_data = re.sub(pattern, replace, file_data)
#
# Scalar variable(expression)
pattern = r'Scalar +(\w+)\((.*)\);'
replace = r'\1 = \2'
file_data = re.sub(pattern, replace, file_data)
#
# Scalar variable = expression
pattern = r'Scalar *(\w+) *=(.*);'
replace = r'\1 =\2'
file_data = re.sub(pattern, replace, file_data)
#
# //
pattern = r'//'
replace = r'#'
file_data = re.sub(pattern, replace, file_data)
#
# template <class Scalar>
# Scalar function_name(
pattern = r'template *< *class *\w+ *>( |\n)*\w+ *(\w+) *\('
replace = r'def \2('
file_data = re.sub(pattern, replace, file_data)
#
# for(type var = 0; var < upper; var++)
pattern = r'for\( *\w+ *(\w+) *= * 0; *\w+ *< *(\w+) *; *(\w|[+])+ *\)'
replace = r'for \1 in range(\2) :'
file_data = re.sub(pattern, replace, file_data)
#
# if( expression )
pattern = r'if\((.*)\)'
replace = r'if \1 :'
file_data = re.sub(pattern, replace, file_data)
#
# true
pattern = r'([^A-Za-z])true([^A-Za-x])'
replace = r'\1True\2'
file_data = re.sub(pattern, replace, file_data)
#
# cmpad::
pattern = r'cmpad::'
replace = r'cmpad.'
file_data = re.sub(pattern, replace, file_data)
#
# bool function_name(void)
pattern = r'bool *(\w+)\(void\)'
replace = r'def \1 () :'
file_data = re.sub(pattern, replace, file_data)
#
# {}
pattern = r'[{}]'
replace = r' '
file_data = re.sub(pattern, replace, file_data)
#
# delete
replace     = ''
delete_list = []
delete_list.append( r'\n# *ifndef CMPAD_[A-Z_]*_HPP' )
delete_list.append( r'\n# *define CMPAD_[A-Z_]*_HPP' )
delete_list.append( r'\n# *endif.*' )
delete_list.append( r'/[*](.|\n)*[*]/' )
delete_list.append( r'\n.*# BEGIN.*' )
delete_list.append( r'\n.*# END.*' )
delete_list.append( r'\n[#] *include.*' )
delete_list.append( r'const.*& *' )
delete_list.append( r'cmpad::.*& *' )
delete_list.append( r'size_t +' )
delete_list.append( r'int +' )
delete_list.append( r'bool +' )
delete_list.append( r'[;]' )
for pattern in delete_list :
   file_data = re.sub(pattern, replace, file_data)
#
#
# file_out
file_obj  = open(file_out, 'w')
file_obj.write(file_data)
file_obj.close()
#
print( 'cpp2py.py: OK' )
