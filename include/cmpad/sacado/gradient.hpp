// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_SACADO_GRADIENT_HPP
# define CMPAD_SACADO_GRADIENT_HPP
/*
{xrst_begin sacado_gradient.hpp}
{xrst_spell
   dvar
   sacado
}

Calculate Gradient Using Sacado
###############################

Syntax
******
| ``# include <cmpad/sacado/gradient.hpp>``
|  ``cmpad::sacado::gradient`` < *Algo* > *grad*
|  *g* = *grad* ( *x* )


Purpose
*******
This implements the :ref:`gradient-name` interface using Sacado.

value_type
**********
The type *Algo*\ ::\ ``value_type`` must be
``Sacado::Rad::ADvar<double>`` .

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

{xrst_end sacado_gradient.hpp}
*/
// BEGIN C++
# include <cmpad/gradient.hpp>
# include <Sacado.hpp>

namespace cmpad { namespace sacado { // BEGIN cmpad::sacado namespace

// gradient
template <class Algo> class gradient : public ::cmpad::gradient<Algo> {
   static_assert(
      std::is_same<
         typename Algo::value_type,
         Sacado::Rad::ADvar<double>
      >::value ,
      "in cmpad::adolc<Algo>, Algo::value_type != Sacado::Rad::ADVar<double>"
   );
private:
   //
   // option_
   option_t option_;
   //
   // algo_
   Algo algo_;
   //
   // ax_
   cmpad::vector< Sacado::Rad::ADvar<double> > ax_;
   //
   // ay_
   cmpad::vector< Sacado::Rad::ADvar<double> > ay_;
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
      // n, m
      size_t n = algo_.domain();
      size_t m = algo_.range();
      //
      // ax_
      ax_.resize(n);
      //
      // ay_
      assert( m == 1 );
      ay_.resize(m);
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
   {  // ax_
      for(size_t j = 0; j < domain(); ++j)
         ax_[j] = x[j];
      //
      // ay_
      ay_ = algo_(ax_);
      //
      // reverse mode computation of gradient for last computed value
      Sacado::Rad::ADvar<double>::Gradcomp();
      //
      // g_
      for(size_t j = 0; j < domain(); ++j)
         g_[j] = ax_[j].adj();
      //
      return g_;
   }
};

} } // END cmpad::cppad namespace
// END C++
# endif
