/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: call_rcond.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 28-May-2022 18:13:52
 */

/* Include Files */
#include "call_rcond.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * RCOND
 *
 * Arguments    : const double X[73410624]
 * Return Type  : double
 */
double call_rcond(const double X[73410624])
{
  static double A[73410624];
  double x[8568];
  double Y;
  double ainvnm;
  double normA;
  double s;
  double smax;
  int b_i;
  int b_j;
  int b_tmp;
  int exitg2;
  int i;
  int iter;
  int iy;
  int j;
  int jA;
  int jjA;
  int jp1j;
  int kase;
  boolean_T exitg1;
  boolean_T p;
  Y = 0.0;
  normA = 0.0;
  j = 0;
  exitg1 = false;
  while ((!exitg1) && (j < 8568)) {
    s = 0.0;
    for (i = 0; i < 8568; i++) {
      s += fabs(X[i + 8568 * j]);
    }
    if (rtIsNaN(s)) {
      normA = rtNaN;
      exitg1 = true;
    } else {
      if (s > normA) {
        normA = s;
      }
      j++;
    }
  }
  if (!(normA == 0.0)) {
    memcpy(&A[0], &X[0], 73410624U * sizeof(double));
    for (j = 0; j < 8567; j++) {
      iter = 8566 - j;
      b_tmp = j * 8569;
      jp1j = b_tmp + 2;
      iy = 8568 - j;
      jjA = 0;
      smax = fabs(A[b_tmp]);
      for (jA = 2; jA <= iy; jA++) {
        s = fabs(A[(b_tmp + jA) - 1]);
        if (s > smax) {
          jjA = jA - 1;
          smax = s;
        }
      }
      if (A[b_tmp + jjA] != 0.0) {
        if (jjA != 0) {
          iy = j + jjA;
          for (jA = 0; jA < 8568; jA++) {
            jjA = j + jA * 8568;
            s = A[jjA];
            kase = iy + jA * 8568;
            A[jjA] = A[kase];
            A[kase] = s;
          }
        }
        b_i = (b_tmp - j) + 8568;
        for (i = jp1j; i <= b_i; i++) {
          A[i - 1] /= A[b_tmp];
        }
      }
      jA = b_tmp;
      for (b_j = 0; b_j <= iter; b_j++) {
        s = A[(b_tmp + b_j * 8568) + 8568];
        if (s != 0.0) {
          b_i = jA + 8570;
          jjA = (jA - j) + 17136;
          for (iy = b_i; iy <= jjA; iy++) {
            A[iy - 1] += A[((b_tmp + iy) - jA) - 8569] * -s;
          }
        }
        jA += 8568;
      }
    }
    jA = 8567;
    do {
      exitg2 = 0;
      if (jA + 1 > 0) {
        if (A[jA + 8568 * jA] == 0.0) {
          exitg2 = 1;
        } else {
          jA--;
        }
      } else {
        ainvnm = 0.0;
        iter = 2;
        kase = 1;
        jp1j = 1;
        j = 0;
        for (i = 0; i < 8568; i++) {
          x[i] = 0.00011671335200746966;
        }
        while (kase != 0) {
          if (kase == 1) {
            for (b_j = 0; b_j < 8568; b_j++) {
              jjA = b_j + b_j * 8568;
              b_i = 8566 - b_j;
              for (i = 0; i <= b_i; i++) {
                iy = (b_j + i) + 1;
                x[iy] -= x[b_j] * A[(jjA + i) + 1];
              }
            }
            for (b_j = 8567; b_j >= 0; b_j--) {
              jjA = b_j + b_j * 8568;
              x[b_j] /= A[jjA];
              for (i = 0; i < b_j; i++) {
                iy = (b_j - i) - 1;
                x[iy] -= x[b_j] * A[(jjA - i) - 1];
              }
            }
          } else {
            for (b_j = 0; b_j < 8568; b_j++) {
              jA = b_j * 8568;
              s = x[b_j];
              for (i = 0; i < b_j; i++) {
                s -= A[jA + i] * x[i];
              }
              x[b_j] = s / A[jA + b_j];
            }
            for (b_j = 8567; b_j >= 0; b_j--) {
              jA = b_j * 8568;
              s = x[b_j];
              b_i = b_j + 2;
              for (i = 8568; i >= b_i; i--) {
                s -= A[(jA + i) - 1] * x[i - 1];
              }
              x[b_j] = s;
            }
          }
          if (jp1j == 1) {
            ainvnm = 0.0;
            for (jA = 0; jA < 8568; jA++) {
              ainvnm += fabs(x[jA]);
            }
            if ((!rtIsInf(ainvnm)) && (!rtIsNaN(ainvnm))) {
              for (jA = 0; jA < 8568; jA++) {
                s = x[jA];
                smax = fabs(s);
                if (smax > 2.2250738585072014E-308) {
                  s /= smax;
                  x[jA] = s;
                } else {
                  x[jA] = 1.0;
                }
              }
              kase = 2;
              jp1j = 2;
            } else {
              kase = 0;
            }
          } else if (jp1j == 2) {
            j = 0;
            smax = fabs(x[0]);
            for (jA = 0; jA < 8567; jA++) {
              s = fabs(x[jA + 1]);
              if (!(s <= smax)) {
                j = jA + 1;
                smax = s;
              }
            }
            iter = 2;
            memset(&x[0], 0, 8568U * sizeof(double));
            x[j] = 1.0;
            kase = 1;
            jp1j = 3;
          } else if (jp1j == 3) {
            ainvnm = 0.0;
            for (jA = 0; jA < 8568; jA++) {
              ainvnm += fabs(x[jA]);
            }
            if (ainvnm <= x[0]) {
              s = 1.0;
              for (jA = 0; jA < 8568; jA++) {
                x[jA] = s * ((((double)jA + 1.0) - 1.0) / 8567.0 + 1.0);
                s = -s;
              }
              kase = 1;
              jp1j = 5;
            } else {
              for (jA = 0; jA < 8568; jA++) {
                s = x[jA];
                smax = fabs(s);
                if (smax > 2.2250738585072014E-308) {
                  s /= smax;
                  x[jA] = s;
                } else {
                  x[jA] = 1.0;
                }
              }
              kase = 2;
              jp1j = 4;
            }
          } else if (jp1j == 4) {
            iy = j;
            j = 0;
            smax = fabs(x[0]);
            for (jA = 0; jA < 8567; jA++) {
              s = fabs(x[jA + 1]);
              if (!(s <= smax)) {
                j = jA + 1;
                smax = s;
              }
            }
            if ((fabs(x[iy]) != fabs(x[j])) && (iter <= 5)) {
              iter++;
              memset(&x[0], 0, 8568U * sizeof(double));
              x[j] = 1.0;
              kase = 1;
              jp1j = 3;
            } else {
              s = 1.0;
              for (jA = 0; jA < 8568; jA++) {
                x[jA] = s * ((((double)jA + 1.0) - 1.0) / 8567.0 + 1.0);
                s = -s;
              }
              kase = 1;
              jp1j = 5;
            }
          } else if (jp1j == 5) {
            s = 0.0;
            for (jA = 0; jA < 8568; jA++) {
              s += fabs(x[jA]);
            }
            s = 2.0 * s / 3.0 / 8568.0;
            if (s > ainvnm) {
              ainvnm = s;
            }
            kase = 0;
          }
        }
        if (ainvnm != 0.0) {
          Y = 1.0 / ainvnm / normA;
        }
        if (rtIsNaN(Y)) {
          p = false;
          for (jA = 0; jA < 73410624; jA++) {
            if (p || rtIsNaN(A[jA])) {
              p = true;
            }
          }
          if (!p) {
            Y = 0.0;
          }
        }
        exitg2 = 1;
      }
    } while (exitg2 == 0);
  }
  return Y;
}

/*
 * File trailer for call_rcond.c
 *
 * [EOF]
 */
