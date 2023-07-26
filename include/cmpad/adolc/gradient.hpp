// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_ADOLC_GRADIENT_HPP
# define CMPAD_ADOLC_GRADIENT_HPP
/*
{xrst_begin adolc_gradient.hpp}
{xrst_spell
   adolc
}

Calculate Gradient Using ADOL-C
###############################

Syntax
******
| ``# include <cmpad/adolc/gradient.hpp>``
|  ``cmpad::adolc::gradient`` < *Algo* > *grad*
|  *g* = *grad* ( *x* )


Purpose
*******
This implements the :ref:`gradient-name` interface using ADOL-C.

Example
*******
The file :ref:`gradient.cpp-name`
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
# include <cmpad/gradient.hpp>
# include <adolc/adolc.h>

namespace cmpad { namespace adolc { // BEGIN cmpad::adolc namespace

// gradient
template <class Algo> class gradient : public ::cmpad::gradient<Algo> {
private:
   //
   // option_
   option_t option_;
   //
   // algo_
   Algo algo_;
   //
   // tag_
   int tag_;
   //
   // u_
   cmpad::vector<double> u_;
   //
   // g_
   cmpad::vector<double> g_;
//
public:
   // option
   const option_t& option(void) const override
   {  return option_; }
   // setup
   void setup(const option_t& option) override
   {  //
      // algo_
      algo_.setup(option);
      //
      // n
      size_t n = algo_.domain();
      //
      // m
      size_t m = algo_.range();
      assert( m == 1 );
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
      // create f : x -> y
      double f;
      ay[0] >>= f;
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
      int m    = int( algo_.range() );
      int n    = int( algo_.domain() );
      //
      // zos_forward
      int keep = 1; // keep this forward mode result
      double f;     // function result
      zos_forward(tag_, m, n, keep, x.data(), &f);
      //
      // fos_reverse
      fos_reverse(tag_, m, n, u_.data(), g_.data() );
      //
      return g_;
   }
};

} } // END cmpad::cppad namespace
// END C++
# endif
