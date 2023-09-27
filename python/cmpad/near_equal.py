# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
r'''
{xrst_begin py_near_equal}
{xrst_spell
   std
   fabs
   operand
   operands
   rel
   vec
}

Python: Check That Values are Nearly Equal
##########################################

Prototype
*********
{xrst_literal
   # BEGIN DEF
   # END DEF
}

Nearly Equal
************
Checks if two values are nearly equal; i.e., if
{xrst_code py}
   std::fabs(x - y) <= abs_error
{xrst_code}
where the absolute error *abs_error* is defined below.

Scalar
******
is the type of the operands we are checking.

x
*
is the left operand in the nearly equal check.

y
*
is the right operand in the nearly equal check.

rel_error
*********
is the relative error used during the comparison.

vec
***
This vector specifies extra values to include when scaling the relative error.
The default for this argument is an empty vector.

abs_error
*********
#. *scale* is the maximum of the absolute value of *x*, *y* ,
   and the elements of *vec*
#. *tiny* is the minimum positive normalized value of type *Scalar*
#. *abs_error* is maximum of *tiny* and *rel_error* times *scale* .

os
**
If the values are not nearly equal,
a messages is written to this stream describing the comparison failure.
The default for this argument is standard error.

{xrst_toc_hidden
   python/xam/near_equal.py
}
:ref:`xam_near_equal.py-name` contains an example and test of this routine.

{xrst_end py_near_equal}
'''
import numpy
import sys
# BEGIN DEF
def near_equal(x, y, rel_error, vec = [], os = sys.stderr ) :
   # END DEF
   scale = max( abs(x), abs(y) )
   for element in vec :
      scale = max(scale, abs(element) )
   tiny      = numpy.finfo(float).tiny
   abs_error = max(rel_error * scale, tiny)
   if abs(x - y) <= abs_error :
      return True
   os.write( f'|{x} - {y}| > {abs_error}' )
   return False
