gcc -c -Wall -Werror -fPIC `python-config --cflags` mandelbrot.c
gcc -shared -o mandelbrot.so mandelbrot.o `python-config --ldflags`
python3 mandelbrot.py