// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin xam_fun_obj.cpp}

Example and Test of fun_obj
###########################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end xam_fun_obj.cpp}
*/
// BEGIN C++
# include <cassert>
# include <iostream>
# include <cmpad/fun_obj.hpp>
# include <cmpad/option_t.hpp>

namespace {

   // my_fun_obj
   class my_fun_obj : public cmpad::fun_obj<float> {
   private:
      //
      // y_
      cmpad::vector<float> y_;
      //
      // option_
      cmpad::option_t option_;
      //
   public:
      //
      // value_type
      typedef float value_type;
      //
      // setup
      void setup(const cmpad::option_t& option) override
      {  y_.resize(1);
         option_ = option;
      }
      const cmpad::option_t& option(void) const override
      {  return option_;
      }
      // domain
      size_t domain(void) const override
      {  return 1;
      }
      // range
      size_t range(void) const override
      {  return 1;
      }
      // operator()
      const cmpad::vector<float>& operator()(
         const cmpad::vector<float>& x
      ) override
      {  assert( x.size() == 1 );
         y_[0] = x[0] * x[0];
         return y_;
      }
   };
}

bool xam_fun_obj(void)
{  //
   // ok
   bool ok = true;
   //
   // option
   // option is not used by this example
   cmpad::option_t option;
   //
   // my_fun_obj
   my_fun_obj my_fun;
   my_fun.setup(option);
   //
   // x
   cmpad::vector<float> x = { 2.0 };
   //
   // y
   const cmpad::vector<float>& y = my_fun(x);
   //
   // ok
   ok &= y[0] == x[0] * x[0];
   //
   return ok;
}
// END C++
