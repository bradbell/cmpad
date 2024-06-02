// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_ADEPT_GRADIENT_VEC_HPP
# define CMPAD_ADEPT_GRADIENT_VEC_HPP
/*
{xrst_begin adept_gradient_vec.hpp}

{xrst_template ,
   cpp/include/cmpad/gradient_vec.xrst
   @Package@       , Adept
   @#######@       , #####
   @package@       , adept
   @not_cppad_jit@ , true
}

{xrst_end adept_gradient_vec.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_ADEPT

# include <adept.h>
# include <cmpad/gradient_vec.hpp>

namespace cmpad { namespace adept { // BEGIN cmpad::adept namespace

// cmpad::adept::gradient_vec
template < template<class Vector> class TemplateAlgo> class gradient_vec
: public
::cmpad::gradient_vec< TemplateAlgo< cmpad::vector<::adept::adouble> > > {
private:
   //
   // Vector
   typedef typename cmpad::vector<::adept::adouble> Vector;
   //
   // option_
   option_t                          option_;
   //
   // stack_
   ::adept::Stack*                   stack_;
   //
   // algo_
   TemplateAlgo<Vector>*             algo_;
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
   gradient_vec(void)
   : stack_(nullptr)
   , algo_(nullptr)
   { }
   //
   ~gradient_vec(void)
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
      algo_ = new TemplateAlgo<Vector>();
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
      Vector ax(n);
      for(size_t i = 0; i < n; ++i)
         ax[i] = x[i];
      //
      // stack
      stack_->new_recording();
      //
      // ay
      Vector ay = (*algo_)(ax);
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
