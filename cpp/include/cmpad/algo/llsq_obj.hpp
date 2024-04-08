// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_ALGO_LLSQ_OBJ_HPP
# define CMPAD_ALGO_LLSQ_OBJ_HPP
/*
{xrst_begin_parent cpp_llsq_obj}

C++ Linear Least Squares Objective
##################################

Syntax
******
| |tab| ``# include <cmpad/algo/llsq_obj.hpp>``
| |tab| ``cmpad::llsq_obj < *Scalar* >`` *llsq*
| |tab| *llsq* . ``setup`` ( *option* )
| |tab| *obj* = *llsq* ( *x* )

Prototype
*********
{xrst_literal
   // BEGIN PROTOTYPE
   // END PROTOTYPE
}

Algorithm
*********
This is a :ref:`cpp_fun_obj-name` interface
to the :ref:`llsq_obj-name` algorithm .

Scalar
******
This is the type of the elements of *x* and *y* .

value_type
**********
This is the same type as *Scalar* ; see :ref:`cpp_fun_obj@value_type` .

Derivatives
***********
All of the C++ packages currently use this algorithm
to compute derivatives of the llsq_obj function.
Perhaps in the future, there will C++ package specific versions of the
algorithm that have vector operations in manner similar to
:ref:`py_llsq_obj-name` .

n_arg
*****
see :ref:`llsq_obj@option@n_arg` .

n_other
*******
see :ref:`llsq_obj@option@n_other` .

{xrst_toc_hidden after
   cpp/xam/llsq_obj.cpp
}

Example
*******
The file :ref:`xam_llsq_obj.cpp-name`
contains an example and test of ``llsq_obj`` .

Source Code
***********
:ref:`cpp_llsq_obj.hpp-name` is the source code for this algorithm.

{xrst_end cpp_llsq_obj}
------------------------------------------------------------------------------
{xrst_begin cpp_llsq_obj.hpp}


C++ llsq_obj: Source Code
#########################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end cpp_llsq_obj.hpp}
------------------------------------------------------------------------------
*/
// BEGIN C++
# include <cassert>
# include <cmpad/fun_obj.hpp>

namespace cmpad { // BEGIN cmpad namespace

// BEGIN PROTOTYPE
template <class Scalar> class llsq_obj : public fun_obj<Scalar>
// END PROTOTYPE
{
private:
   //
   // option_
   option_t option_;
   //
   // t_, q_, y_
   cmpad::vector<Scalar> t_, q_, y_;
   //
public:
   // value_type
   typedef Scalar value_type;
   //
   // option
   const option_t& option(void) const override
   {  return option_; }
   //
   // domain
   size_t domain(void) const override
   {  return option_.n_arg; }
   //
   // range
   size_t range(void) const override
   {  return 1; }
   //
   // setup
   void setup(const option_t& option) override
   {  //
      // n_arg, n_other
      assert( option.n_arg > 0 );
      assert( option.n_other > 0 );
      //
      // option_
      option_ = option;
      //
      // n_other
      size_t n_other = option.n_other;
      //
      // y_
      y_.resize(1);
      //
      // t_
      t_.resize(n_other);
      if( n_other == 1 )
         t_[0] = 0.0;
      else
      {  for(size_t j = 0; j < n_other; ++j)
            t_[j] = -1.0 + 2.0 * double(j) / double(n_other-1);
      }
      //
      // q_
      q_.resize(n_other);
      if( n_other == 1 )
         q_[0] = 0.0;
      else
      {  for(size_t j = 0; j < n_other; ++j)
            if( t_[j] == 0.0 )
               q_[j] = 0.0;
            else if( t_[j] < 0.0 )
               q_[j] = -1.0;
            else
               q_[j] = +1.0;
      }
   }
   //
   // operator
   const cmpad::vector<Scalar>& operator()(
      const cmpad::vector<Scalar>& x
   ) override
   {  //
      // n_arg, n_other
      size_t n_arg   = option_.n_arg;
      size_t n_other = option_.n_other;
      //
      // sumsq
      Scalar sumsq(0.0);
      for(size_t j = 0; j < n_other; ++j)
      {  Scalar model(0.0);
         Scalar tij(1.0);
         for(size_t i = 0; i < n_arg; ++i)
         {  model += x[i] * tij;
            tij   *= t_[j];
         }
         Scalar residual = model - q_[j];
         sumsq          += residual * residual;
      }
      //
      y_[0] = 0.5 * sumsq;
      //
      return y_;
   }
};

} // END cmapd namespace

// END C++
# endif
