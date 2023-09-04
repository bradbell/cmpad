// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_ADEPT_GRADIENT_HPP
# define CMPAD_ADEPT_GRADIENT_HPP
/*
{xrst_begin adept_gradient.hpp}
{xrst_spell
   obj
}

Calculate Gradient Using CppAD
##############################

Syntax
******
|  ``# include <cmpad/adept/gradient.hpp>``
|  ``cmpad::adept::gradient`` < *TemplateAlgo* > *grad*
|  *g* = *grad* ( *x* )


Purpose
*******
This implements the :ref:`gradient-name` interface using CppAD.

TemplateAlgo
************
The class TemplateAlgo<Scalar> must be a derived class for
:ref:`fun_obj\<Scalar\> <fun_obj-name>` .

value_type
**********
The type cmpad::adept::gradient<TemplateAlgo>::value_type is ``double`` ;
see :ref:`gradient@value_type` .

Example
*******
The file :ref:`xam_gradient_adept.cpp-name`
contains an example and test using this class.

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end adept_gradient.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_ADEPT

# include <adept.h>
# include <cmpad/gradient.hpp>

namespace cmpad { namespace adept { // BEGIN cmpad::adept namespace

// cmpad::adept::gradient
template < template<class Scalar> class TemplateAlgo> class gradient
: public ::cmpad::gradient< TemplateAlgo<::adept::adouble> > {
private:
   //
   // option_
   option_t                          option_;
   //
   // stack_
   ::adept::Stack*                   stack_;
   //
   // algo_
   TemplateAlgo<::adept::adouble>*   algo_;
   //
   // g_
   cmpad::vector<double>             g_;
//
public:
   //
   // default ctor
   gradient(void)
   : stack_(nullptr) 
   , algo_(nullptr)
   { }
   //
   ~gradient(void)
   {  if( algo_ != nullptr )
         delete algo_;
      if( stack_ != nullptr )
         delete stack_;
   }
   //
   // value_type
   typedef double value_type;
   // option
   const option_t& option(void) const override
   {  return option_; }
   // setup
   void setup(const option_t& option) override
   {  //
      // algo_
      if( algo_ != nullptr )
         delete algo_;
      //
      // stack_
      if( stack_ != nullptr )
         delete stack_;
      stack_ = new ::adept::Stack;
      //
      // algo_
      algo_ = new TemplateAlgo<::adept::adouble>();
      //
      // algo_
      algo_->setup(option);
      //
      // n
      size_t n = algo_->domain();
      //
      // g_
      g_.resize(n);
   }
   // domain
   size_t domain(void) const override
   {  return algo_->domain(); };
   //
   // operator
   const cmpad::vector<double>& operator()(
      const cmpad::vector<double>& x
   ) override
   {  // n
      size_t n = algo_->domain();
      //
      // m
      size_t m = algo_->range();
      //
      // ax
      cmpad::vector<::adept::adouble> ax(n);
      for(size_t i = 0; i < n; ++i)
         ax[i] = x[i];
      //
      // stack
      stack_->new_recording();
      //
      // ay
      cmpad::vector<::adept::adouble> ay = (*algo_)(ax); 
      assert( ay.size() == m );
      //
      // g_
      ay[m-1].set_gradient(1.0);
      stack_->compute_adjoint();
      for(size_t j = 0; j < n; ++j)
         g_[j] = ax[j].get_gradient();
      //
      return g_;
   }
};

} } // END cmpad::adept namespace

# endif // CMPAD_HAS_ADEPT
// END C++
# endif
