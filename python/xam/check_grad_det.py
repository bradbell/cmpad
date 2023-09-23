import numpy
import cmpad

def near_equal(x, y, rel_error, vec) :
   scale = max( abs(x), abs(y) )
   for element in vec :
      scale = max(scale, abs(element) )
   tiny      = numpy.finfo(float).tiny
   abs_error = max(rel_error * scale, tiny)
   return abs(x - y) <= abs_error

def check_grad_det( grad_det ) :
   #
   # ok
   ok = True
   #
   # rel_error
   rel_error = 100. * numpy.finfo(float).eps
   #
   # ell
   for ell in [ 3, 4, 5] :
      # option
      option = {
         'n_arg'      : ell * ell       ,
         'time_setup' : bool( ell % 2 ) ,
      }
      #
      # grad_det
      grad_det.setup(option)
      #
      # x
      # values in the matrix in row major order
      x = numpy.random.uniform(0.0, 1.0, ell * ell)
      #
      # g
      g = grad_det(x)
      #
      # r, c
      # index values corresponding to computing determinat of entire matrix
      r = numpy.empty( ell+1, dtype=int )
      c = numpy.empty( ell+1, dtype=int )
      for i in range(ell) :
         r[i] = i+1
         c[i] = i+1
      r[ell] = 0
      c[ell] = 0
      #
      # i, j
      # for each row and column index in the matrix
      for i in range(ell) :
         for j in range(ell) :
            # r, c
            # minor with row i and column j removed
            if i == 0 :
               r[ell] = 1
            else :
               r[i-1] = i+1
            if j == 0 :
               c[ell] = 1
            else :
               c[j-1] = j+1
            #
            # det_minor
            # determinant of minor corresponding to (i, j) removed
            det_minor = cmpad.det_of_minor(x, ell, ell-1, r, c)
            #
            # check
            # derivative of determinant with respect matrix element (i, j)
            check = det_minor
            if (i + j) % 2 == 1 :
               check = - det_minor
            #
            # ok
            ok &= near_equal(g[ i * ell + j ], check, rel_error, x)
            #
            # r, c
            # restore to computing determinant of entire matrix
            if i == 0 :
               r[ell] = 0
            else :
               r[i-1] = i
            if j == 0 :
               c[ell] = 0
            else :
               c[j-1] = j
   return ok


