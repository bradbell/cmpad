#! /usr/bin/env python3
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
import sys
import re
import difflib
#
# program
program = 'sort_file.py'
#
# begin_str, end_str
begin_str     = r'BEGIN_SORT_THIS_LINE_PLUS_([1-9])'
end_str       = r'END_SORT_THIS_LINE_MINUS_([1-9])'
#
# begin_pattern, end_pattern
begin_pattern = re.compile( begin_str )
end_pattern   = re.compile( end_str )
#
# sort_file
def sort_file(file_name) :
   #
   # file_data
   file_obj  = open(file_name, 'r')
   file_data = file_obj.read()
   file_obj.close()
   #
   # change
   change = False
   #
   # start
   start = 0
   #
   # m_begin
   m_begin = begin_pattern.search(file_data, start)
   if m_begin == None :
      msg = f'{program}: file_name = {file_name}\n'
      msg += 'Cannot find ' + begin_str
      assert False, msg
   while m_begin != None :
      #
      # start
      start = m_begin.end()
      #
      # m_end
      m_end = end_pattern.search(file_data, start)
      if m_end == None :
         line = file_data.count('\n', 0, start)
         msg  = f'{program}: file_name = {file_name}: line = {line}:\n'
         msg  += 'Cannot find matching ' + end_str
         assert False, msg
      #
      # plus, minus
      plus = int( m_begin.group(1) )
      minus = int( m_end.group(1) )
      #
      # before
      before = file_data[: m_begin.start()]
      #
      # after
      after  = file_data[m_end.end() :]
      #
      # between
      between = file_data[ m_begin.start() : m_end.end() ]
      #
      # between_lines
      between_lines = between.splitlines(keepends = True)
      #
      # line_start, line_end
      line_start = plus
      line_end   = len(between_lines) - minus
      #
      # sorted_lines
      sorted_lines = between_lines[line_start : line_end]
      sorted_lines = sorted( sorted_lines )
      #
      # sorted_lines
      sorted_lines = \
         between_lines[: line_start] + sorted_lines + between_lines[line_end :]
      #
      # sorted_between
      sorted_between = ''.join(sorted_lines)
      #
      # change
      if sorted_between != between :
         change = True
         #
         # diff
         fromfile = f'{file_name}: before'
         tofile   = f'{file_name}: after'
         diff = difflib.unified_diff(
            between_lines, sorted_lines, fromfile=fromfile, tofile=tofile
         )
         sys.stdout.writelines(diff)
         print('\n')
      #
      # file_data
      file_data = before + sorted_between + after
      #
      # start
      start = m_end.end()
      #
      # m_begin
      m_begin = begin_pattern.search(file_data, start)
   #
   # file_name
   if change :
      file_obj = open(file_name, 'w')
      file_obj.write( file_data )
      file_obj.close()
#
# main
def main() :
   #
   # n_file
   n_file = len(sys.argv) - 1
   if n_file != 1 :
      usage   = f'{program} file_name\n'
      usage  += 'There is no output if original file is sorted.\n'
      usage  += 'Otherwise this program sorts the file and outputs '
      usage  += 'the difference.'
      sys.exit(usage)
   #
   sort_file( sys.argv[1] )
#
main()
