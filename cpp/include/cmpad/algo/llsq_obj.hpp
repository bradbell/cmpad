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

{xrst_template ,
   cpp/include/cmpad/algo/template.xrst
   $algo_name$      , llsq_obj
   $obj_name$       , llsq
   $********$       , ****
}


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
   // BEGIN TEMPLATE_CLASS
   // END TEMPLATE_CLASS
}

{xrst_end cpp_llsq_obj.hpp}
------------------------------------------------------------------------------
{xrst_begin valvector_llsq_obj.hpp}


C++ valvector Special Version of llsq_obj
#########################################
{xrst_literal
   // BEGIN VALVECTOR_SPECIALIZATION
   // END VALVECTOR_SPECIALIZATION
}

{xrst_end valvector_llsq_obj.hpp}
*/
// ----------------------------------------------------------------------------
// BEGIN TEMPLATE_CLASS
// ----------------------------------------------------------------------------
# include <cassert>
# include <cmpad/fun_obj.hpp>
//
# include <cmpad/vector.hpp>
# include <cmpad/cppad/cppad.hpp>

namespace cmpad { // BEGIN cmpad namespace

// BEGIN CLASS_DECLARE
template <class Vector> class llsq_obj : public fun_obj<Vector>
// END CLASS_DECLARE
{
private:
   //
   // option_
   option_t option_;
   //
   // t_, q_, y_
   Vector t_, q_, y_;
   //
public:
   // scalar_type
   typedef typename Vector::value_type scalar_type;
   //
   // vector_type
   typedef Vector vector_type;
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
   const Vector& operator()(const Vector& x) override
   {  //
      // n_arg, n_other
      size_t n_arg   = option_.n_arg;
      size_t n_other = option_.n_other;
      //
      // sumsq
      scalar_type sumsq(0.0);
      for(size_t j = 0; j < n_other; ++j)
      {  scalar_type model(0.0);
         scalar_type tij(1.0);
         for(size_t i = 0; i < n_arg; ++i)
         {  model += x[i] * tij;
            tij   *= t_[j];
         }
         scalar_type residual = model - q_[j];
         sumsq               += residual * residual;
      }
      //
      // y_
      y_[0] = 0.5 * sumsq;
      //
      return y_;
   }
};

} // END cmapd namespace
// END TEMPLATE_CLASS
// ----------------------------------------------------------------------------
// BEGIN VALVECTOR_SPECIALIZATION
// ----------------------------------------------------------------------------
namespace cmpad { // BEGIN cmpad namespace

template <>
class llsq_obj  < cmpad::vector< CppAD::AD<valvector> > >
: public fun_obj< cmpad::vector< CppAD::AD<valvector> > >
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

// END VALVECTOR_SPECIALIZATION
# endif
