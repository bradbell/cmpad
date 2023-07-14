# include <cmpad/det_by_minor.hpp>
# include <cmpad/cppad/gradient.hpp>

namespace {
   template <class Grad_Det>
   void check_grad_det(void)
   {  //
      // vector_type
      typedef typename Grad_Det::vector_type vector_type;
      // n
      size_t n = 3;
      //
      // grad_det
      Grad_Det grad_det;
      grad_det.setup(n);
      //
      // x
      // values in the matrix in row major order
      vector_type x = {
         1., 2., 3.,
         4., 5., 6.,
         7., 8., 10.
      };
      //
      // g
      vector_type g = grad_det(x);
      //
      BOOST_CHECK( g[ 0 * n + 0] == + (5.*10. - 6.*8.) );
      BOOST_CHECK( g[ 0 * n + 1] == - (4.*10. - 6.*7.) );
      BOOST_CHECK( g[ 0 * n + 2] == + (4.*8.  - 5.*7.) );
      //
      BOOST_CHECK( g[ 1 * n + 0] == - (2.*10. - 3.*8.) );
      BOOST_CHECK( g[ 1 * n + 1] == + (1.*10. - 3.*7.) );
      BOOST_CHECK( g[ 1 * n + 2] == - (1.*8.  - 2.*7.) );
      //
      BOOST_CHECK( g[ 2 * n + 0] == + (2.*6.  - 3.*5.) );
      BOOST_CHECK( g[ 2 * n + 1] == - (1.*6.  - 3.*4.) );
      BOOST_CHECK( g[ 2 * n + 2] == + (1.*5.  - 2.*4.) );
   }
}

BOOST_AUTO_TEST_CASE(cppad_gradient)
{  //
   // check_grad_det
   typedef cmpad::det_by_minor< CppAD::AD<double> > Algo;
   check_grad_det< cmpad::cppad::gradient<Algo> >();
}
