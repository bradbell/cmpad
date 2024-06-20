// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_CPPAD_LLSQ_OBJ_HPP
# define CMPAD_CPPAD_LLSQ_OBJ_HPP
/*
{xrst_begin_parent cppad_llsq_obj}
{xrst_spell
   typedef
   valvector
}

C++ CppAD Special Linear Least Squares Objective
################################################
This is a CppAD specific versions of the llsq_obj
algorithm that has vector operations in manner similar to
:ref:`py_llsq_obj-name` .

Syntax
******
| |tab| ``# include <cmpad/cppad/llsq_obj.hpp>``
| |tab| ``cmpad::cppad::llsq_obj`` *llsq*
| |tab| *llsq* . ``setup`` ( *option* )
| |tab| *y* = *llsq* ( *x* )

Class Declaration
*****************
{xrst_literal
   // BEGIN CLASS_DECLARE
   // END CLASS_DECLARE
}

Algo
****
This is an :ref:`cpp_fun_obj-name` interface
to the :ref:`llsq_obj-name` Algorithm .
We use *Algo* for the type of this algorithm; i.e.,

| |tab| ``typedef cmpad::cppad::llsq_obj`` *Algo*

scalar_type
***********
The type ``cmpad::cppad::llsq_obj::scalar_type`` is
``CppAD::AD<valvector>`` .
This is the type of the elements of the vectors passed
when *llsq* is used as a function object.
This definition is useful when *Algo* is a template parameter.

vector_type
***********
The type ``cmpad::cppad::llsq_obj::vector_type`` is
``cmpad::vector`` < *scalar_type* > (where *scalar_type* is define above) .
This is the type of the vectors passed
when *llsq* is used as a function object.
This definition is useful when *Algo* is a template parameter.

llsq
****
The object *llsq* is a :ref:`cpp_fun_obj@fun`
that computes the function corresponding to the llsq_obj algorithm.

n_arg
*****
see :ref:`llsq_obj@option@n_arg` .

n_other
*******
see :ref:`llsq_obj@option@n_other` .

{xrst_toc_hidden after
   cpp/xam/cppad/llsq_obj.cpp
}

Example
*******
The file :ref:`xam_cppad_llsq_obj.cpp-name`
contains an example and test of ``llsq_obj`` .

Source Code
***********
:ref:`cppad_llsq_obj.hpp-name` is the source code for this algorithm.

{xrst_end cppad_llsq_obj}
------------------------------------------------------------------------------
{xrst_begin cppad_llsq_obj.hpp}


C++ llsq_obj: CppAD Special Source Code
#######################################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end cppad_llsq_obj.hpp}
------------------------------------------------------------------------------
*/
// BEGIN C++
# include <cassert>
# include <cmpad/fun_obj.hpp>
# include <cmpad/vector.hpp>
# include <cmpad/algo/llsq_obj.hpp>
# include <cmpad/cppad/cppad.hpp>

namespace cmpad {

// BEGIN CLASS_DECLARE
template <>
class llsq_obj  < cmpad::vector< CppAD::AD<valvector> > >
: public fun_obj< cmpad::vector< CppAD::AD<valvector> > >
// END CLASS_DECLARE
{
public:
   // scalar_type
   typedef typename CppAD::AD<valvector>  scalar_type;
   //
   // vector_type
   typedef cmpad::vector<scalar_type>      vector_type;
private:
   //
   // asum
   valvector_ad_sum asum;
   //
   // option_
   option_t option_;
   //
   // ay_
   vector_type ay_;
   //
   // t_, q_
   valvector t_, q_;
   //
public:
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
      // ay_
      ay_.resize(1);
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
   const vector_type& operator()(const vector_type& ax) override
   {  //
      // n_arg, n_other
      size_t n_arg   = option_.n_arg;
      size_t n_other = option_.n_other;
      //
      // sumsq
      scalar_type amodel = valvector(0.0);
      valvector   ti     = valvector(1.0);
      for(size_t i = 0; i < n_arg; ++i)
      {  amodel += ax[i] * ti;
         ti     *= t_;
      }
      scalar_type aresidual = amodel - q_;
      scalar_type asquare   = aresidual * aresidual;
      //
      // ay_
      scalar_type asumsq;
      asum(asquare, asumsq);
      ay_[0] = valvector(0.5) * asumsq;
      //
      return ay_;
   }
};

} // END cmapd namespace

// END C++
# endif
