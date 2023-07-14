# ifndef CMPAD_CPPAD_GRADIENT_HPP
# define CMPAD_CPPAD_GRADIENT_HPP
# include <boost/test/unit_test.hpp>
# include <cppad/cppad.hpp>

namespace cmpad { namespace cppad { // BEGIN cmpad::cppad namespace

// BEGIN_CLASS
template <class Algo> class gradient {
// END CLASS
//
public:
   // vector_type
   typedef CppAD::vector<double> vector_type;
//
private:
   // algo_
   Algo algo_;
   // w_
   vector_type w_;
   // tape_
   CppAD::ADFun<double>  tape_;
//
public:
   //
   // BEGIN SETUP
   void setup(size_t n)
   // END SETUP
   {  //
      // algo_
      algo_.setup(n);
      //
      // w_
      w_.resize(1);
      w_[0] = 1.0;
      //
      // tape_
      CppAD::vector< CppAD::AD<double> > ax(n * n);
      for(size_t i = 0; i < n * n; ++i)
         ax[i] = 0.;
      CppAD::Independent(ax);
      CppAD::vector< CppAD::AD<double> > ay(1);
      ay[0] = algo_(ax);
      tape_.Dependent(ax, ay);
   }
   //
   // BEGIN OPERATOR
   vector_type operator()(const vector_type& x)
   // END OPERATOR
   {  tape_.Forward(0, x);
      return tape_.Reverse(1, w_);
   }
};

} } // END cmpad::cppad namespace
# endif
