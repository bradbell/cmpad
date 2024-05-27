// SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
// SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
// SPDX-FileContributor: 2023-24 Bradley M. Bell
// ---------------------------------------------------------------------------
/*
{xrst_begin xam_fun_obj_vec.cpp}

Example and Test of fun_obj_vec
###############################
{xrst_literal
   // BEGIN C++
   // END C++
}

{xrst_end xam_fun_obj_vec.cpp}
*/
// BEGIN C++
# include <cassert>
# include <iostream>
# include <cmpad/vector.hpp>
# include <cmpad/fun_obj_vec.hpp>
# include <cmpad/option_t.hpp>

namespace {
   //
   // Vector
   typedef cmpad::vector<float> Vector;
   //
   // my_fun_obj_vec
   class my_fun_obj_vec : public cmpad::fun_obj_vec<Vector> {
   private:
      //
      // y_
      Vector y_;
      //
      // option_
      cmpad::option_t option_;
      //
   public:
      //
      // value_type
      typedef Vector::value_type value_type;
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
      const Vector& operator()(const Vector& x) override
      {  assert( x.size() == 1 );
         y_[0] = x[0] * x[0];
         return y_;
      }
   };
}

bool xam_fun_obj_vec(void)
{  //
   // ok
   bool ok = true;
   //
   // option
   // option is not used by this example
   cmpad::option_t option;
   //
   // my_fun
   my_fun_obj_vec my_fun;
   my_fun.setup(option);
   //
   // x
   Vector x = { 2.0 };
   //
   // y
   const Vector& y = my_fun(x);
   //
   // ok
   ok &= y[0] == x[0] * x[0];
   //
   return ok;
}
// END C++
