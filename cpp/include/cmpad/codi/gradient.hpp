// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_CODI_GRADIENT_HPP
# define CMPAD_CODI_GRADIENT_HPP
/*
{xrst_begin codi_gradient.hpp}

{xrst_template ,
   cpp/include/cmpad/gradient.xrst
   @Package@       , CODI
   @#######@       , ####
   @package@       , codi
   @not_cppad_jit@ , true
}

{xrst_end codi_gradient.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_CODI

# include <codi.hpp>
# include <cmpad/gradient.hpp>

namespace cmpad { namespace codi { // BEGIN cmpad::codi namespace

typedef ::codi::RealReverseVec<1> ADScalar;

// cmpad::codi::gradient
template < template<class ADVector> class TemplateAlgo > class gradient
: public
cmpad::gradient< TemplateAlgo< cmpad::vector<ADScalar> > > {
private:
   //
   // ADVector
   typedef cmpad::vector<ADScalar> ADVector;
   //
   // option_
   option_t                        option_;
   //
   // algo_
   TemplateAlgo<ADVector>          algo_;
   //
   // tape_
   ADScalar::Tape&                 tape_;
   //
   // ax_, ay_
   ADVector                        ax_;
   ADVector                        ay_;
   //
   // g_
   cmpad::vector<double>           g_;
//
public:
   gradient(void)
   : tape_ ( ADScalar::getTape() )
   { } 
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
      // ax
      // independent variable values
      for(size_t j = 0; j < n; ++j)
         ax_[j] = x[j];
      //
      // tape_
      tape_.setActive();
      for(size_t j = 0; j < n; ++j)
         tape_.registerInput( ax_[j] );
      //
      // az
      // dependent variable
      ay_      = algo_(ax_);
      ADScalar az = ay_[m-1];
      //
      // tape_
      tape_.registerOutput(az);
      tape_.setPassive();
      //
      // tape_, az, ax_
      az.gradient()[0] = 1.0;
      tape_.evaluate();
      //
      // g_
      for(size_t j = 0; j < n; ++j)
         g_[j] = ax_[j].getGradient()[0];
      //
      // clean tape and adjoints
      tape_.reset();
      //
      return g_;
   }
};

} } // END cmpad::codi namespace

# endif // CMPAD_HAS_CODI
// END C++
# endif
