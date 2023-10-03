// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_CLAD_GRADIENT_HPP
# define CMPAD_CLAD_GRADIENT_HPP
/*
{xrst_begin clad_gradient.hpp}
{xrst_spell
   obj
}

Calculate Gradient Using clad
#############################

Under Construction
******************
One or more of the correctness tests that uses this gradient calculation
are currently failing.

Syntax
******
|  ``# include <cmpad/clad/gradient.hpp>``
|  ``cmpad::clad::gradient`` < *TemplateAlgo* > *grad*
|  *g* = *grad* ( *x* )


Purpose
*******
This implements the :ref:`gradient-name` interface using clad.

TemplateAlgo
************
The class TemplateAlgo<Scalar> must be a derived class for
:ref:`fun_obj\<Scalar\> <fun_obj-name>` .

value_type
**********
The type cmpad::clad::gradient<TemplateAlgo>::value_type is ``double`` ;
see :ref:`gradient@value_type` .

Example
*******
The file :ref:`xam_gradient_clad.cpp-name`
contains an example and test using this class.

Source Code
***********
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end clad_gradient.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_CLAD

# include <clad/Differentiator/Differentiator.h>
# include <cmpad/gradient.hpp>

namespace cmpad { namespace clad { // BEGIN cmpad::clad namespace

// cmpad::clad::gradient
template < template<class Scalar> class TemplateAlgo> class gradient
: public ::cmpad::gradient< TemplateAlgo<double> > {
private:
   // clad_fun
   struct clad_fun {
      // n_
      size_t n_;
      //
      // algo_
      TemplateAlgo<double>*   algo_ptr_;
      //
      // setup
      void setup(size_t n, TemplateAlgo<double>* algo_ptr)
      {  n_        = n; 
         algo_ptr_ = algo_ptr;
      }
      //
      // operator()
      double operator()(const double* x)
      {  cmpad::vector<double> vx(n_);
         for(size_t j = 0; j < n_; ++j)
            vx[j] = x[j];
         cmpad::vector<double> vy = (*algo_ptr_)(vx);
         size_t m = vy.size();
         return vy[m-1];
      }
   };
   //
   // option_
   option_t                   option_;
   //
   // algo_
   TemplateAlgo<double>       algo_;
   //
   // g_
   cmpad::vector<double>      g_;
   //
   // f_
   clad_fun                   f_;
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
      // n
      size_t n = algo_.domain();
      //
      // m
      size_t m = algo_.range();
      //
      // f_
      f_.setup(n, &algo_);
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
   {  //
      // n
      size_t n = algo_.domain();
      //  
      // f_dx
      auto f_dx = ::clad::gradient(f_);
      //
      // g_,  g_ref
      for(size_t j = 0; j < n; ++j)
         g_[j] = 0.0;
      ::clad::array_ref<double> g_ref(g_.data(), n);
      //
      // g, g_ref
      clad_fun not_used;
      not_used.setup(n, &algo_);
      f_dx.execute(x.data(), &not_used, g_ref);
      //
      return g_;
   }
};

} } // END cmpad::clad namespace

# endif // CMPAD_HAS_CLAD
// END C++
# endif
