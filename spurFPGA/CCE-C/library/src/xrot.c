/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xrot.c
 *
 * Code generation for function 'xrot'
 *
 */

/* Include files */
#include "C:\Research\CU-Spur-Sean\spurFPGA\CCE-C\library\include\xrot.h"
#include "C:\Research\CU-Spur-Sean\spurFPGA\CCE-C\library\include\rt_nonfinite.h"

/* Function Definitions */
void xrot(double x[64], int ix0, int iy0, double c, double s)
{
  int k;
  for (k = 0; k < 8; k++) {
    double b_temp_tmp;
    double d_temp_tmp;
    int c_temp_tmp;
    int temp_tmp;
    temp_tmp = (iy0 + k) - 1;
    b_temp_tmp = x[temp_tmp];
    c_temp_tmp = (ix0 + k) - 1;
    d_temp_tmp = x[c_temp_tmp];
    x[temp_tmp] = c * b_temp_tmp - s * d_temp_tmp;
    x[c_temp_tmp] = c * d_temp_tmp + s * b_temp_tmp;
  }
}

/* End of code generation (xrot.c) */
