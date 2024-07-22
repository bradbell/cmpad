// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
# ifndef CMPAD_CODI_GRADIENT_HPP
# define CMPAD_CODI_GRADIENT_HPP
/*
{xrst_begin codi_gradient.hpp}
{xrst_spell
   retape
   onetape
   Co
   Di
}

{xrst_template ,
   cpp/include/cmpad/gradient.xrst
   @Package@       , CoDiPack
   @#######@       , ########
   @package@       , codi
   @not_cppad_jit@ , true
   @not_codi@      , false
}

{xrst_end codi_gradient.hpp}
*/
// BEGIN C++
# if CMPAD_HAS_CODI

# include <codi.hpp>
# include <cmpad/gradient.hpp>

namespace cmpad { namespace codi { // BEGIN cmpad::codi namespace

// ---------------------------------------------------------------------------
// cmpad::codi::gradient_retape
template < template<class ADVector> class Algo > class gradient_retape
: public
cmpad::gradient {
private:
   //
   // ADScalar, ADVector
   typedef ::codi::RealReverseVec<1> ADScalar;
   typedef cmpad::vector<ADScalar>   ADVector;
   //
   // option_
   option_t                        option_;
   //
   // algo_
   Algo<ADVector>                  algo_;
   //
   // tape_
   ADScalar::Tape&                 tape_;
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
   gradient_retape(void)
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
      // az_
      // dependent variable
      ay_ = algo_(ax_);
      az_ = ay_[m-1];
      //
      // tape_
      tape_.registerOutput(az_);
      tape_.setPassive();
      //
      // tape_, az_, ax_
      az_.gradient()[0] = 1.0;
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
// ---------------------------------------------------------------------------
// cmpad::codi::gradient_onetape
template < template<class ADVector> class Algo > class gradient_onetape
: public
cmpad::gradient {
private:
   //
   // ADScalar, ADVector
   typedef ::codi::RealReversePrimal ADScalar;
   typedef cmpad::vector<ADScalar>   ADVector;
   //
   // option_
   option_t                         option_;
   //
   // algo_
   Algo<ADVector>                   algo_;
   //
   // tape_
   ADScalar::Tape&                  tape_;
   //
   // ax_, ay_, az_
   ADVector                         ax_;
   ADVector                         ay_;
   ADScalar                         az_;
   //
   // g_
   cmpad::vector<double>            g_;
//
public:
   // constructor
   gradient_onetape(void)
   : tape_ ( ADScalar::getTape() )
   { }
   // destructor
   ~gradient_onetape(void)
   {  tape_.reset(); }
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
      //
      // ax
      // independent variable values
      for(size_t j = 0; j < n; ++j)
         ax_[j] = 0.0;
      //
      // tape_
      tape_.reset();
      tape_.setActive();
      for(size_t j = 0; j < n; ++j)
         tape_.registerInput( ax_[j] );
      //
      // az_
      // dependent variable
      ay_ = algo_(ax_);
      az_ = ay_[m-1];
      //
      // tape_
      tape_.registerOutput(az_);
      tape_.setPassive();
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
      //
      // tape_, az_, ax_
      tape_.clearAdjoints();
      for(size_t j = 0; j < n; ++j)
         tape_.setPrimal(ax_[j].getIdentifier(), x[j] );
      tape_.evaluatePrimal();
      //
      az_.setGradient(1.0);
      tape_.evaluate();
      //
      // g_
      for(size_t j = 0; j < n; ++j)
         g_[j] = ax_[j].getGradient();
      //
      return g_;
   }
};
// ---------------------------------------------------------------------------
// cmpad::codi::gradient
template < template<class ADVector> class Algo > class gradient
: public
cmpad::gradient {
private:
   //
   // retape_
   gradient_retape<Algo>  retape_;
   //
   // onetape_
   gradient_onetape<Algo> onetape_;
   //
   // time_setup_
   bool                   time_setup_;
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
   {  const option_t* result_ptr = nullptr;
      if( time_setup_ )
         result_ptr = &(retape_.option());
      else
         result_ptr = &(onetape_.option());
      return *result_ptr;
   }
   //
   // setup
   void setup(const option_t& option) override
   {  //
      // time_setup_
      time_setup_ = option.time_setup;
      //
      // retape_, one_tape_
      if( time_setup_ )
         retape_.setup(option);
      else
         onetape_.setup(option);
   }
   // domain
   size_t domain(void) const override
   {  size_t result;
      if( time_setup_ )
         result = retape_.domain();
      else
         result = onetape_.domain();
      return result;
   }
   //
   // operator
   const cmpad::vector<double>& operator()(
      const cmpad::vector<double>& x
   ) override
   {  const cmpad::vector<double>* result_ptr = nullptr;
      if( time_setup_ )
         result_ptr = &( retape_(x) );
      else
         result_ptr = &( onetape_(x) );
      return *result_ptr;
   }
};

} } // END cmpad::codi namespace

# endif // CMPAD_HAS_CODI
// END C++
# endif
