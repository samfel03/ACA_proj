/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xaxpy.c
 *
 * Code generation for function 'xaxpy'
 *
 */

/* Include files */
#include "xaxpy.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void b_xaxpy(int n, double a, const double x[64], int ix0, double y[8], int iy0)
{
  int k;
  if (!(a == 0.0)) {
    int i;
    i = n - 1;
    for (k = 0; k <= i; k++) {
      int i1;
      i1 = (iy0 + k) - 1;
      y[i1] += a * x[(ix0 + k) - 1];
    }
  }
}

void c_xaxpy(int n, double a, const double x[8], int ix0, double y[64], int iy0)
{
  int k;
  if (!(a == 0.0)) {
    int i;
    i = n - 1;
    for (k = 0; k <= i; k++) {
      int i1;
      i1 = (iy0 + k) - 1;
      y[i1] += a * x[(ix0 + k) - 1];
    }
  }
}

void xaxpy(int n, double a, int ix0, double y[64], int iy0)
{
  int k;
  if (!(a == 0.0)) {
    int i;
    i = n - 1;
    for (k = 0; k <= i; k++) {
      int i1;
      i1 = (iy0 + k) - 1;
      y[i1] += a * y[(ix0 + k) - 1];
    }
  }
}

/* End of code generation (xaxpy.c) */
