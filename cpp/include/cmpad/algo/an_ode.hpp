// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_ALGO_AN_ODE_HPP
# define CMPAD_ALGO_AN_ODE_HPP
/*
{xrst_begin_parent cpp_an_ode_vec}
{xrst_spell
   kutta
   runge
   yf
}

Use C++ Runge-Kutta Method to Solve an ODE
##########################################

{xrst_template ,
   cpp/include/cmpad/algo/template.xrst
   $algo_name$      , an_ode
   $obj_name$       , ode
   $********$       , ***
}

n_arg
*****
see :ref:`an_ode@option@n_arg` .

n_other
=======
see :ref:`an_ode@option@n_other` .

x
*
This is the :ref:`an_ode@ODE@Parameter Vector` that appears in the ODE.

yf
**
The return value *yf* is :math:`y(t)` at :math:`t = 2` .

{xrst_toc_hidden after
   cpp/xam/an_ode.cpp
   cpp/include/cmpad/algo/runge_kutta.hpp
}
Example
*******
:ref:`xam_an_ode_vec.cpp-name` contains an example and test of ``an_ode_vec`` .

Source Code
***********
:ref:`an_ode_vec.hpp-name` displays the source code for this algorithm.

{xrst_end cpp_an_ode_vec}
------------------------------------------------------------------------------
{xrst_begin an_ode_vec.hpp}

an_ode_vec: Source Code
#######################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end an_ode_vec.hpp}
*/
// BEGIN C++
# include <cassert>
# include <cmpad/fun_obj.hpp>
# include <cmpad/algo/runge_kutta.hpp>

namespace cmpad { // BEGIN cmpad namespace

// an_ode_fun
template <class Vector> class an_ode_fun_vec
{
private:
   // x_
   Vector x_;
public:
   //
   // operator
   Vector operator()(const Vector& y) const
   {  size_t n = y.size();
      assert( x_.size() == n );
      Vector dy(n);
      dy[0] = x_[0];
      for(size_t i = 1; i < n; ++i)
         dy[i] = x_[i] * y[i-1];
      return dy;
   }
   //
   // set_x
   void set_x(const Vector& x)
   {  x_ = x;
   }
};

// BEGIN CLASS_DECLARE
template <class Vector> class an_ode_vec : public fun_obj_vec<Vector>
// END CLASS_DECLARE
{
private:
   // option_
   option_t option_;
   //
   // zero_
   Vector zero_;
   //
   // yf_
   Vector yf_;
   //
   // fun_
   an_ode_fun_vec<Vector> fun_;
public:
   // scalar type
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
   {  return option_.n_arg; }
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
      // zero_
      zero_.resize(option.n_arg);
      for(size_t i = 0; i < zero_.size(); ++i)
         zero_[i] = scalar_type(0.0);
      //
      // yf_
      yf_.resize(option.n_arg);
   }
   //
   // operator
   const Vector& operator()(const Vector& x) override
   {  //
      // x
      assert( x.size() == domain() );
      fun_.set_x(x);
      //
      // tf
      scalar_type tf = scalar_type(2.0);
      //
      // ns
      size_t ns = option_.n_other;
      //
      // yf
      const Vector& yi = zero_;
      yf_ = cmpad::runge_kutta(fun_, yi, tf, ns);
      assert( yf_.size() == domain() );
      //
      return yf_;
   }
};

}  // END cmpad namespace

// END C++
# endif
