// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_ADOLC_GRADIENT_HPP
# define CMPAD_ADOLC_GRADIENT_HPP
/*
{xrst_begin adolc_gradient.hpp}

{xrst_template ,
   cpp/include/cmpad/gradient.xrst
   @Package@       , ADOL-C
   @#######@       , ######
   @package@       , adolc
   @not_cppad_jit@ , true
   @not_codi@      , true
}

{xrst_end adolc_gradient.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_ADOLC

# include <adolc/adolc.h>
# include <cmpad/gradient.hpp>

namespace cmpad { namespace adolc { // BEGIN cmpad::adolc namespace

// cmpad::adolc::gradient
template < template<class ADVector> class Algo > class gradient
: public
cmpad::gradient {
private:
   //
   // ADVector
   typedef cmpad::vector<adouble> ADVector;
   //
   // option_
   option_t                      option_;
   //
   // algo_
   Algo<ADVector>                algo_;
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
   //
   // scalar_type
   typedef double scalar_type;
   //
   // vector_type
   typedef cmpad::vector<double> vector_type;
   //
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
      ADVector ax(n);
      for(size_t j = 0; j < n; ++j)
         ax[j] <<= 0.0;
      //
      // ay
      // dependent variable
      ADVector ay = algo_(ax);
      //
      // create f : x -> y
      double f;
      ay[m-1] >>= f;
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
