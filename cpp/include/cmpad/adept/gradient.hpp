// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_ADEPT_GRADIENT_HPP
# define CMPAD_ADEPT_GRADIENT_HPP
/*
{xrst_begin adept_gradient.hpp}

{xrst_template ,
   cpp/include/cmpad/gradient.xrst
   @Package@       , Adept
   @#######@       , #####
   @package@       , adept
   @not_cppad_jit@ , true
}

{xrst_end adept_gradient.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_ADEPT

# include <adept.h>
# include <cmpad/gradient.hpp>

namespace cmpad { namespace adept { // BEGIN cmpad::adept namespace

// cmpad::adept::gradient
template < template<class ADVector> class Algo> class gradient
: public
::cmpad::gradient {
private:
   //
   // ADVector
   typedef typename cmpad::vector<::adept::adouble> ADVector;
   //
   // option_
   option_t                          option_;
   //
   // stack_
   ::adept::Stack*                   stack_;
   //
   // algo_
   Algo<ADVector>*                   algo_;
   //
   // g_
   cmpad::vector<double>             g_;
//
public:
   //
   // scalar_type
   typedef double scalar_type;
   //
   // vector_type
   typedef cmpad::vector<double> vector_type;
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
   // option
   const option_t& option(void) const override
   {  return option_; }
   //
   // setup
   void setup(const option_t& option) override
   {  //
      // option_
      option_ = option;
      //
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
      algo_ = new Algo<ADVector>();
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
      ADVector ax(n);
      for(size_t i = 0; i < n; ++i)
         ax[i] = x[i];
      //
      // stack
      stack_->new_recording();
      //
      // ay
      ADVector ay = (*algo_)(ax);
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
