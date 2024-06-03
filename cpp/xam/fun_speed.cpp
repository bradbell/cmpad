// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin xam_fun_speed.cpp}

Example and Test of fun_speed
#############################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end xam_fun_speed.cpp}
*/
// BEGIN C++
# include <cassert>
# include <iostream>
# include <cmpad/fun_speed.hpp>
# include <cmpad/fun_obj.hpp>
# include <cmpad/option_t.hpp>

namespace { // BEGIN_EMPTY_NAMESPACE

   // my_fun_obj
   class my_fun_obj : public cmpad::fun_obj_vec< cmpad::vector<double> > {
   private:
      // size_
      size_t n_arg_;
      //
      // option_
      cmpad::option_t option_;
      //
      // y_
      cmpad::vector<double> y_;
   public:
      //
      // scalar_type
      typedef double scalar_type;
      //
      // setup
      void setup(const cmpad::option_t& option) override
      {  n_arg_   = option.n_arg;
         option_ = option;
         y_.resize(1);
      }
      const cmpad::option_t& option(void) const override
      {  return option_;
      }
      // domain
      size_t domain(void) const override
      {  return n_arg_;
      }
      // range
      size_t range(void) const override
      {  return 1;
      }
      // operator()
      const cmpad::vector<double>& operator()(
         const cmpad::vector<double>& x
      ) override
      {  assert( x.size() == n_arg_ );
         double sum = 0.0;
         for(const double& xi : x)
            sum += xi;
         y_[0] = sum;
         return y_;
      }
   };

   // run_test
   bool run_test(size_t try_index)
   {  //
      // ok
      bool ok = true;
      //
      // min_time
      double min_time = 0.1;
      //
      // my_fun
      my_fun_obj my_fun;
      //
      // option_one
      cmpad::option_t option_one;
      option_one.n_arg       = 1000;
      option_one.time_setup = false;
      //
      // rate_one
      double rate_one = cmpad::fun_speed(my_fun, option_one, min_time);
      //
      // option_two
      cmpad::option_t option_two;
      option_two.n_arg       = 2 * option_one.n_arg;
      option_two.time_setup = false;
      //
      // rate_two
      double rate_two = cmpad::fun_speed(my_fun, option_two, min_time);
      //
      // ok
      double ratio = rate_one / rate_two;
      ok &= 1.7 < ratio && ratio < 2.3;
      if( (! ok) && 0 < try_index )
      {  std::cout << "fun_speed: try_index = " << try_index << ", ";
         std::cout << "ratio = " << ratio << "\n";
      }
      //
      return ok;
   }
} // END_EMPTY_NAMESPACE

bool xam_fun_speed(void)
{  size_t try_index = 0;
   bool ok          = run_test(try_index);
   if( ! ok )
   {  // try again (maybe system was doing other things during rate test)
      try_index += 1;
      ok = run_test(try_index);
   }
   return ok;
}

// END C++
