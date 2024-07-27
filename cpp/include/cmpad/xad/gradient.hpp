// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_XAD_GRADIENT_HPP
# define CMPAD_XAD_GRADIENT_HPP
/*
{xrst_begin xad_gradient.hpp}

{xrst_template ,
   cpp/include/cmpad/gradient.xrst
   @Package@       , XAD
   @#######@       , ###
   @package@       , xad
   @not_cppad_jit@ , true
   @not_codi@      , true
}

{xrst_end xad_gradient.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_XAD
/*
2DO: Under Construction: This gradient does not yet pass its tests
*/

# include <XAD/XAD.hpp>
# include <cmpad/gradient.hpp>

namespace cmpad { namespace xad { // BEGIN cmpad::xad namespace

::xad::adj<double>::tape_type adj_tape;

// cmpad::xad::gradient_retape
template < template<class ADVector> class Algo > class gradient
: public
cmpad::gradient {
private:
   // mode
   typedef ::xad::adj<double> mode;
   //
   // ADScalar, ADVector
   typedef mode::active_type       ADScalar;
   typedef cmpad::vector<ADScalar> ADVector;
   //
   // option_
   option_t                        option_;
   //
   // algo_
   Algo<ADVector>                  algo_;
   //
   // ax_, ay_, az_
   ADVector                        ax_;
   ADVector                        ay_;
   ADScalar                        az_;
   //
   // g_
   cmpad::vector<double>           g_;
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
   //
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
      // ax_
      ax_.resize(n);
      //
      // ay_
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
   {  assert( x.size() == algo_.domain() );
      //
      // n, m
      int n    = int( algo_.domain() );
      int m    = int( algo_.range() );
      //
      // ax_
      // independent variable values
      for(size_t j = 0; j < n; ++j)
         ax_[j] = x[j];
      //
      // adj_tape
      adj_tape.clearAll();
      for(size_t j = 0; j < n; ++j)
         adj_tape.registerInput( ax_[j] );
      adj_tape.newRecording();
      //
      // az_
      // dependent variable
      ay_ = algo_(ax_);
      az_ = ay_[m-1];
      //
      // adj_tape
      adj_tape.registerOutput(az_);
      //
      // adj_tape, az_, ax_
      derivative(az_) = 1.0;
      adj_tape.computeAdjoints();
      //
      // g_
      for(size_t j = 0; j < n; ++j)
         g_[j] = derivative( ax_[j] );
      //
      return g_;
   }
};

} } // END cmpad::xad namespace

# endif // CMPAD_HAS_XAD
// END C++
# endif
