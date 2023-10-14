// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_ADOLC_GRADIENT_HPP
# define CMPAD_ADOLC_GRADIENT_HPP
/*
{xrst_begin adolc_gradient.hpp}
{xrst_spell
   obj
}

Calculate Gradient Using ADOL-C
###############################

Syntax
******
| |tab| ``# include <cmpad/adolc/gradient.hpp>``
| |tab| ``cmpad::adolc::gradient`` < *TemplateAlgo* > *grad*
| |tab| *g* = *grad* ( *x* )


Purpose
*******
This implements the :ref:`gradient-name` interface using ADOL-C.

TemplateAlgo
************
The class TemplateAlgo<Scalar> must be a derived class for
:ref:`fun_obj\<Scalar\> <cpp_fun_obj-name>` .

value_type
**********
The type cmpad::adolc::gradient<TemplateAlgo>::value_type is ``double`` ;
see :ref:`gradient@value_type` .

Example
*******
The file :ref:`xam_gradient_adolc.cpp-name`
contains an example and test using this class.

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end adolc_gradient.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_ADOLC

# include <type_traits>
# include <adolc/adolc.h>
# include <cmpad/gradient.hpp>

namespace cmpad { namespace adolc { // BEGIN cmpad::adolc namespace

// cmpad::adolc::gradient
template < template<class Scalar> class TemplateAlgo > class gradient
: public ::cmpad::gradient< TemplateAlgo<adouble> > {
private:
   //
   // option_
   option_t                      option_;
   //
   // algo_
   TemplateAlgo<adouble>         algo_;
   //
   // tag_
   int                           tag_;
   //
   // u_
   cmpad::vector<double>         u_;
   //
   // g_
   cmpad::vector<double>         g_;
//
public:
   // value_type
   typedef double value_type;
   // option
   const option_t& option(void) const override
   {  return option_; }
   // setup
   void setup(const option_t& option) override
   {  //
      // option_
      option_ = option;
      //
      // algo_
      algo_.setup(option);
      //
      // n
      size_t n = algo_.domain();
      //
      // m
      size_t m = algo_.range();
      //
      // tag_
      tag_ = 0;
      //
      // ax
      // independent variables
      int keep = 0;
      trace_on(tag_, keep);
      cmpad::vector<adouble> ax(n);
      for(size_t j = 0; j < n; ++j)
         ax[j] <<= 0.0;
      //
      // ay
      // dependent variable
      cmpad::vector<adouble> ay = algo_(ax);
      //
      // r_index
      size_t r_index = option_.r_index;
      //
      // create f : x -> y
      double f;
      ay[r_index] >>= f;
      trace_off();
      //
      // u_
      u_.resize(1);
      u_[0] = 1.0;
      //
      // g_
      g_.resize(n);
   }
   // domain
   size_t domain(void) const override
   {  return algo_.domain(); };
   //
   // operator
   const cmpad::vector<double>& operator()(
      const cmpad::vector<double>& x
   ) override
   {  assert( x.size() == algo_.domain() );
      int one  = 1;
      int n    = int( algo_.domain() );
      //
      // zos_forward
      int keep = 1; // keep this forward mode result
      double f;     // function result
      zos_forward(tag_, one, n, keep, x.data(), &f);
      //
      // fos_reverse
      fos_reverse(tag_, one, n, u_.data(), g_.data() );
      //
      return g_;
   }
};

} } // END cmpad::adolc namespace

# endif // CMPAD_HAS_ADOLC
// END C++
# endif
