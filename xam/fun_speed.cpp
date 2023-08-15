// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
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
# include <iostream>
# include <cmpad/fun_speed.hpp>
# include <cmpad/fun_obj.hpp>
# include <cmpad/option_t.hpp>

namespace {

   // my_fun_obj
   class my_fun_obj : public cmpad::fun_obj<double> {
   private:
      // size_
      size_t size_;
      //
      // option_
      cmpad::option_t option_;
      //
      // y_
      cmpad::vector<double> y_;
   public:
      //
      // value_type
      typedef double value_type;
      //
      // setup
      void setup(const cmpad::option_t& option) override
      {  size_   = option.size; 
         option_ = option;
         y_.resize(1);
      }
      const cmpad::option_t& option(void) const override
      {  return option_;
      }
      // domain
      size_t domain(void) const override
      {  return size_; 
      }
      // range  
      size_t range(void) const override
      {  return 1; 
      }
      // operator()
      const cmpad::vector<double>& operator()(
         const cmpad::vector<double>& x
      ) override
      {  assert( x.size() == size_ );
         double sum = 0.0;
         for(const double& xi : x)
            sum += xi;
         y_[0] = sum;
         return y_;
      }
   };
}

bool xam_fun_speed(void)
{  //
   // ok
   bool ok = true;
   //
   // time_min
   double time_min = 0.1;
   //
   // my_fun_obj
   my_fun_obj my_fun;
   //
   // option_one
   cmpad::option_t option_one;
   option_one.size       = 1000;
   option_one.time_setup = false;
   //
   // rate_one
   double rate_one = cmpad::fun_speed(my_fun, option_one, time_min);
   //
   // option_two
   cmpad::option_t option_two;
   option_two.size       = 2 * option_one.size;
   option_two.time_setup = false;
   //
   // rate_two
   double rate_two = cmpad::fun_speed(my_fun, option_two, time_min);
   //
   // ok
   double ratio = rate_one / rate_two;
   ok &= 1.8 < ratio && ratio < 2.2;
   //
   return ok;
}
// END C++
