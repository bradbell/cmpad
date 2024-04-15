# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023-24 Bradley M. Bell
# ---------------------------------------------------------------------------

# ---------------------------------------------------------------------------
# In this module

# BEGIN_SORT_THIS_LINE_PLUS_1
from .an_ode         import an_ode
from .csv_speed      import csv_speed
from .det_by_minor   import det_by_minor
from .det_of_minor   import det_of_minor
from .fun_speed      import fun_speed
from .llsq_obj       import llsq_obj
from .near_equal     import near_equal
from .runge_kutta    import runge_kutta
# END_SORT_THIS_LINE_MINUS_1

# ---------------------------------------------------------------------------
# Submodules
from . import torch
#
has_package = dict()
#
# autograd
has_package['autograd'] = True
try :
   from . import autograd
except :
   has_package['autograd'] = False
#
# cppad_py
has_package['cppad_py'] = True
try :
   from . import cppad_py
except :
   has_package['cppad_py'] = False
#
# jax
has_package['jax'] = True
try :
   from . import jax
except :
   has_package['jax'] = False
#
# torch
has_package['torch'] = True
try :
   from . import torch
except :
   has_package['torch'] = False
