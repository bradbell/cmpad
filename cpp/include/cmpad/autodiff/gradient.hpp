// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_AUTODIFF_GRADIENT_HPP
# define CMPAD_AUTODIFF_GRADIENT_HPP
/*
{xrst_begin autodiff_gradient.hpp}

{xrst_template ,
   cpp/include/cmpad/gradient.xrst
   @Package@       , autodiff
   @#######@       , ########
   @package@       , autodiff
   @not_cppad_jit@ , true
   @not_codi@      , true
}

{xrst_end autodiff_gradient.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_AUTODIFF

# include <autodiff/forward/real.hpp>
# include <autodiff/forward/real/eigen.hpp>
# include <cmpad/gradient.hpp>

namespace cmpad { namespace autodiff { // BEGIN cmpad::autodiff namespace


// gradient
template < template<class ADVector> class Algo> class gradient
: public
cmpad::gradient {
private:
   //
   // ADVector
   typedef ::autodiff::VectorXreal ADVector;
   //
   // option_
   option_t                option_;
   //
   // algo_
   Algo<ADVector>          algo_;
   //
   // ax_, ay_
   ADVector                ax_;
   ADVector                ay_;
   //
   // g_, g_copy_
   Eigen::VectorXd         g_;
   cmpad::vector<double>   g_copy_;
   //
   // y_
   ::autodiff::real        y_;
public:
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
      // n, m
      size_t n = algo_.domain();
      size_t m = algo_.range();
      //
      // ax_
      ax_.resize(n);
      //
      // ay_
      ay_.resize(m);
      //
      // g_, g_copy_
      g_.resize(n);
      g_copy_.resize(n);
   }
   // domain
   size_t domain(void) const override
   {  return algo_.domain(); };
   //
   // operator
   const cmpad::vector<double>& operator()(
      const cmpad::vector<double>& x
   ) override
   {  // ax_
      for(size_t j = 0; j < domain(); ++j)
         ax_[j] = x[j];
      //
      auto f = [&](const ADVector& ax)
      {  size_t m = algo_.range();
         ay_ = algo_(ax_);
         return ay_[m-1];
      };
      //
      // forward mode computation of gradient
      g_ = ::autodiff::gradient(f, wrt(ax_), at(ax_), y_);
      //
      // g_
      for(size_t j = 0; j < domain(); ++j)
         g_copy_[j] = g_[j];
      //
      return g_copy_;
   }
};

} } // END cmpad::autodiff namespace

# endif // CMPAD_HAS_AUTODIFF
// END C++
# endif
