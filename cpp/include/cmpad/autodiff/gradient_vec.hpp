// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_AUTODIFF_GRADIENT_VEC_HPP
# define CMPAD_AUTODIFF_GRADIENT_VEC_HPP
/*
{xrst_begin autodiff_gradient_vec.hpp}

{xrst_template ,
   cpp/include/cmpad/gradient_vec.xrst
   @Package@       , autodiff
   @#######@       , ########
   @package@       , autodiff
   @not_cppad_jit@ , true
}

{xrst_end autodiff_gradient_vec.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_AUTODIFF

# include <autodiff/forward/real.hpp>
# include <autodiff/forward/real/eigen.hpp>
# include <cmpad/gradient_vec.hpp>

namespace cmpad { namespace autodiff { // BEGIN cmpad::autodiff namespace

typedef ::autodiff::real          real;
typedef ::autodiff::VectorXreal   VectorXreal;

// gradient_vec
template < template<class Vector> class TemplateAlgo> class gradient_vec
: public
cmpad::gradient_vec< TemplateAlgo< cmpad::vector<::autodiff::real> > > {
private:
   //
   // Vector
   typedef cmpad::vector<::autodiff::real> Vector;
   //
   // option_
   option_t              option_;
   //
   // algo_
   TemplateAlgo<Vector>  algo_;
   //
   // ax_, ax_copy_
   VectorXreal           ax_;
   Vector                ax_copy_;
   //
   // ay_
   Vector                 ay_;
   //
   // g_, g_copy_
   Eigen::VectorXd       g_;
   cmpad::vector<double> g_copy_;
   //
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
      // ax_, ax_copy_
      ax_.resize(n);
      ax_copy_.resize(n);
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
      auto f = [&](const VectorXreal& ax)
      {  size_t m = algo_.range();
         for(int i = 0; i < ax.size(); ++i)
            ax_copy_[i] = ax[i];
         ay_ = algo_(ax_copy_);
         return ay_[m-1];
      };
      //
      // forward mode computation of gradient_vec
      ::autodiff::real y;
      g_ = ::autodiff::gradient(f, wrt(ax_), at(ax_), y);
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
