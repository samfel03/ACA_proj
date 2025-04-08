/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xdotc.c
 *
 * Code generation for function 'xdotc'
 *
 */

/* Include files */
#include "C:\Research\CU-Spur-Sean\spurFPGA\CCE-C\library\include\xdotc.h"
#include "C:\Research\CU-Spur-Sean\spurFPGA\CCE-C\library\include\rt_nonfinite.h"

/* Function Definitions */
double xdotc(int n, const double x[64], int ix0, const double y[64], int iy0)
{
  double d;
  int k;
  d = 0.0;
  for (k = 0; k < n; k++) {
    d += x[(ix0 + k) - 1] * y[(iy0 + k) - 1];
  }
  return d;
}

/* End of code generation (xdotc.c) */
