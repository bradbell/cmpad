// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_AUTODIFF_GRADIENT_HPP
# define CMPAD_AUTODIFF_GRADIENT_HPP
/*
{xrst_begin autodiff_gradient.hpp}
{xrst_spell
   obj
}

Calculate Gradient Using autodiff
#################################

Syntax
******
|  ``# include <cmpad/autodiff/gradient.hpp>``
|  ``cmpad::autodiff::gradient`` < *TemplateAlgo* > *grad*
|  *g* = *grad* ( *x* )


Purpose
*******
This implements the :ref:`gradient-name` interface using autodiff.

TemplateAlgo
************
The class TemplateAlgo<Scalar> must be a derived class for
:ref:`fun_obj\<Scalar\> <fun_obj-name>` .

value_type
**********
The type cmpad::autodiff::gradient<TemplateAlgo>::value_type is ``double`` ;
see :ref:`gradient@value_type` .

Example
*******
The file :ref:`xam_gradient_autodiff.cpp-name`
contains an example and test using this class.

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end autodiff_gradient.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_AUTODIFF

# include <autodiff/forward/real.hpp>
# include <autodiff/forward/real/eigen.hpp>
# include <cmpad/gradient.hpp>

namespace cmpad { namespace autodiff { // BEGIN cmpad::autodiff namespace

typedef ::autodiff::real          real;
typedef ::autodiff::VectorXreal   VectorXreal;

// gradient
template < template<class Scalar> class TemplateAlgo> class gradient
: public ::cmpad::gradient< TemplateAlgo<real> > {
private:
   //
   // option_
   option_t              option_;
   //
   // algo_
   TemplateAlgo<real>    algo_;
   //
   // ax_, ax_copy_
   VectorXreal           ax_;
   cmpad::vector<real>   ax_copy_;
   //
   // ay_
   cmpad::vector<real>   ay_;
   //
   // g_, g_copy_
   Eigen::VectorXd       g_;
   cmpad::vector<double> g_copy_;
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
      // forward mode computation of gradient
      real y;
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
