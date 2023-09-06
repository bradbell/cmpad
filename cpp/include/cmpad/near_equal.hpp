// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_NEAR_EQUAL_HPP
# define CMPAD_NEAR_EQUAL_HPP

# include <cmath>
# include <iostream>
/*
{xrst_begin near_equal}
{xrst_spell
   std
   fabs
   operand
   operands
   rel
   vec
}

Check That Values are Nearly Equal
##################################

Prototype
*********
{xrst_literal
   // BEGIN PROTOTYPE
   // END PROTOTYPE
}

Nearly Equal
************
Checks if two values are nearly equal; i.e., if
{xrst_code cpp}
   std::fabs(x - y) <= abs_error
{xrst_code}
where the absolute error *abs_error* is defined below.

Type
****
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

abs_error
*********
We define the absolute error *abs_error* by
{xrst_literal
   // BEGIN ABS_ERROR
   // END ABS_ERROR
}

os
**
If the values are not nearly equal,
a messages is written to this stream describing the comparison failure.

{xrst_toc_hidden
   cpp/xam/near_equal.cpp
}
:ref:`xam_near_equal.cpp-name` contains an example and test of this routine.

{xrst_end near_equal}
*/
# include <cmpad/vector.hpp>

// BEGIN PROTOTYPE
namespace cmpad {
   template <class Type> bool near_equal(
      const Type&                x                                           ,
      const Type&                y                                           ,
      const Type                 rel_error                                   ,
      const cmpad::vector<Type>& vec       = cmpad::vector<Type>(0)          ,
      std::ostream&              os        = std::cerr                       )
// END PROTOTYPE
   {  // BEGIN ABS_ERROR
      Type scale = std::max( std::fabs(x), std::fabs(y) );
      for(size_t i = 0; i < vec.size(); ++i)
         scale = std::max( scale, std::fabs( vec[i] ) );
      Type min       = std::numeric_limits<Type>::min();
      Type abs_error = std::max( rel_error * scale , min );
      // END ABS_ERROR
      if( std::fabs(x - y) < abs_error )
         return true;
      os << "| " << x << " - " << y << " | > " << abs_error << "\n";
      return false;
   }

}

# endif
