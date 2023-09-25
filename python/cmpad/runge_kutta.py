# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------





def runge_kutta(fun, yi, tf, ns) :
   #
   # two, six
   two = float(2.0)
   six = float(6.0)
   # n
   n = len(yi)
   #
   # h
   h = tf / float(ns)
   #
   # i_step, yf
   yf = yi
   for i_step in range(ns) :
      #
      # k1
      k1 = fun(yf)
      #
      # k2
      y_tmp = n * [0.0]
      for i in range(n) :
         y_tmp[i] = yf[i] + h * k1[i] / two
      k2 = fun(y_tmp)
      #
      # k3
      for i in range(n) :
         y_tmp[i] = yf[i] + h * k2[i] / two
      k3 = fun(y_tmp)
      #
      # k4
      for i in range(n) :
         y_tmp[i] = yf[i] + h * k3[i]
      k4 = fun(y_tmp)
      #
      # yf
      for i in range(n) :
         yf[i] = yf[i] + h * (k1[i] + two * k2[i] + two * k3[i] + k4[i]) / six
   #
   return yf

