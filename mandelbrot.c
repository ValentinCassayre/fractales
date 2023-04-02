#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct complex
{
    float real;
    float imag;
};
typedef struct complex Complex;

int *full_mandelbrot(float *xl, float *yl, int X, int Y, int N)
{
    int *mandelbrot(float *x, float *y, int X, int Y, int N);
    float *linspace(float *limits, int size);

    float *x = linspace(xl, X);
    float *y = linspace(yl, Y);

    return mandelbrot(x, y, X, Y, N);
}

int *mandelbrot(float *x, float *y, int X, int Y, int N)
{
    void product(Complex * z1, Complex * z2, Complex * z3);
    void sum(Complex * z1, Complex * z2, Complex * z3);
    void repr(Complex z);

    Complex *z = malloc((sizeof(Complex) * X) * Y);
    Complex *c = malloc((sizeof(Complex) * X) * Y);
    Complex t;
    int *iteration = malloc((sizeof(int) * X) * Y);

    int i, j, k;
    for (i = 0; i < X; i++)
    {
        for (j = 0; j < Y; j++)
        {
            (z + i * X + j)->real = 0;
            (z + i * X + j)->imag = 0;
            (c + i * X + j)->real = *(x + i);
            (c + i * X + j)->imag = *(y + j);
            *(iteration + i * X + j) = 0;
        }
    }

    for (k = 1; k <= N; k++)
    {
        for (i = 0; i < X; i++)
        {
            for (j = 0; j < Y; j++)
            {
                if (isinf((z + i * X + j)->real) || isinf((z + i * X + j)->imag))
                {
                    if (*(iteration + i * X + j) == 0)
                    {
                        *(iteration + i * X + j) = k - 1;
                    }
                }
                else
                {
                    product(z + i * X + j, z + i * X + j, &t);
                    sum(&t, c + i * X + j, z + i * X + j);
                }
            }
        }
    }
    return iteration;
}

void product(Complex *z1, Complex *z2, Complex *z3)
{
    z3->real = (z1->real) * (z2->real) - (z1->imag) * (z2->imag);
    z3->imag = (z1->real) * (z2->imag) + (z1->imag) * (z2->real);
}

void sum(Complex *z1, Complex *z2, Complex *z3)
{
    z3->real = (z1->real) + (z2->real);
    z3->imag = (z1->imag) + (z2->imag);
}

void repr(Complex z)
{
    printf("%f + %fi", z.real, z.imag);
}

float *linspace(float *limits, int size)
{
    float *vector = malloc(sizeof(float) * size);
    int i;
    for (i = 0; i < size; i++)
    {
        vector[i] = *(limits) + (*(limits + 1) - *(limits)) * i * 1. / (size - 1);
    }
    return vector;
}

float *meshgrid(float *x, float *y, int X, int Y)
{
    float *grid = malloc(sizeof(float) * X * Y * 2);

    int i, j;
    for (i = 0; i < X; i++)
    {
        for (j = 0; j < Y; j++)
        {
            *(grid + i * X + j) = *(x + i);
            *(grid + X * Y + i * X + j) = *(y + j);
        }
    }

    return grid;
}

void freeptr(void *ptr)
{
    free(ptr);
}