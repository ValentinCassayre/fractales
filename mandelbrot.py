import matplotlib.pyplot as plt

import ctypes

N = 100

x0 = -2
x1 = 0.5
y0 = -1.5
y1 = 1.5
X = 1000
Y = 1000

lib_c = ctypes.CDLL('./mandelbrot.so')

lib_c.linspace.argtype = (ctypes.POINTER(ctypes.c_float * 2), ctypes.c_int)
lib_c.linspace.restype = ctypes.POINTER(ctypes.c_float)

xptr = lib_c.linspace((ctypes.c_float * 2)(x0, x1), X)
yptr = lib_c.linspace((ctypes.c_float * 2)(y0, y1), Y)

lib_c.meshgrid.argtype = (ctypes.POINTER(ctypes.c_float * X), ctypes.POINTER(ctypes.c_float * Y), ctypes.c_int, ctypes.c_int)
lib_c.meshgrid.restype = ctypes.POINTER(ctypes.c_float * X * Y * 2)

gridptr = lib_c.meshgrid(xptr, yptr, X, Y)
xv, yv = gridptr.contents

lib_c.mandelbrot.argtype = (ctypes.POINTER(ctypes.c_float * X), ctypes.POINTER(ctypes.c_float * Y), ctypes.c_int, ctypes.c_int, ctypes.c_int)
lib_c.mandelbrot.restype = ctypes.POINTER(ctypes.c_int * X * Y)

lib_c.freeptr.argtype = ctypes.c_void_p
lib_c.freeptr.restype = None

darrayptr = lib_c.mandelbrot(xptr, yptr, X, Y, N)
iteration = darrayptr.contents

fig, ax = plt.subplots()
plt.pcolor(xv, yv, iteration, cmap='jet')
ax.set_frame_on(False)
plt.axis('off')
plt.axis([x0,x1,y0,y1])
plt.axis('equal')
ax.set_aspect('equal')
#plt.show()
plt.savefig('mandelbrot.png')

lib_c.freeptr(darrayptr)