/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * svd.c
 *
 * Code generation for function 'svd'
 *
 */

/* Include files */
#include "svd.h"
#include "rt_nonfinite.h"
#include "xaxpy.h"
#include "xdotc.h"
#include "xnrm2.h"
#include "xrot.h"
#include "xrotg.h"
#include "xswap.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
void svd(const double A[64], double U[64], double s[8], double V[64])
{
  double Vf[64];
  double b_A[64];
  double b_s[8];
  double e[8];
  double work[8];
  double nrm;
  double rt;
  double sm;
  double snorm;
  double sqds;
  int ii;
  int iter;
  int jj;
  int k;
  int m;
  int q;
  int qjj;
  int qp1;
  int qp1jj;
  int qq;
  memcpy(&b_A[0], &A[0], 64U * sizeof(double));
  memset(&b_s[0], 0, 8U * sizeof(double));
  memset(&e[0], 0, 8U * sizeof(double));
  memset(&work[0], 0, 8U * sizeof(double));
  memset(&U[0], 0, 64U * sizeof(double));
  memset(&Vf[0], 0, 64U * sizeof(double));
  for (q = 0; q < 7; q++) {
    boolean_T apply_transform;
    qp1 = q + 2;
    iter = q << 3;
    qq = (q + iter) + 1;
    apply_transform = false;
    nrm = xnrm2(8 - q, b_A, qq);
    if (nrm > 0.0) {
      apply_transform = true;
      if (b_A[qq - 1] < 0.0) {
        nrm = -nrm;
      }
      b_s[q] = nrm;
      if (fabs(nrm) >= 1.0020841800044864E-292) {
        nrm = 1.0 / nrm;
        qjj = (qq - q) + 7;
        for (k = qq; k <= qjj; k++) {
          b_A[k - 1] *= nrm;
        }
      } else {
        qjj = (qq - q) + 7;
        for (k = qq; k <= qjj; k++) {
          b_A[k - 1] /= b_s[q];
        }
      }
      b_A[qq - 1]++;
      b_s[q] = -b_s[q];
    } else {
      b_s[q] = 0.0;
    }
    for (jj = qp1; jj < 9; jj++) {
      qjj = q + ((jj - 1) << 3);
      if (apply_transform) {
        xaxpy(8 - q, -(xdotc(8 - q, b_A, qq, b_A, qjj + 1) / b_A[q + (q << 3)]),
              qq, b_A, qjj + 1);
      }
      e[jj - 1] = b_A[qjj];
    }
    for (ii = q + 1; ii < 9; ii++) {
      qp1jj = (ii + iter) - 1;
      U[qp1jj] = b_A[qp1jj];
    }
    if (q + 1 <= 6) {
      nrm = b_xnrm2(7 - q, e, q + 2);
      if (nrm == 0.0) {
        e[q] = 0.0;
      } else {
        if (e[q + 1] < 0.0) {
          e[q] = -nrm;
        } else {
          e[q] = nrm;
        }
        nrm = e[q];
        if (fabs(e[q]) >= 1.0020841800044864E-292) {
          nrm = 1.0 / e[q];
          for (k = qp1; k < 9; k++) {
            e[k - 1] *= nrm;
          }
        } else {
          for (k = qp1; k < 9; k++) {
            e[k - 1] /= nrm;
          }
        }
        e[q + 1]++;
        e[q] = -e[q];
        for (ii = qp1; ii < 9; ii++) {
          work[ii - 1] = 0.0;
        }
        for (jj = qp1; jj < 9; jj++) {
          b_xaxpy(7 - q, e[jj - 1], b_A, (q + ((jj - 1) << 3)) + 2, work,
                  q + 2);
        }
        for (jj = qp1; jj < 9; jj++) {
          c_xaxpy(7 - q, -e[jj - 1] / e[q + 1], work, q + 2, b_A,
                  (q + ((jj - 1) << 3)) + 2);
        }
      }
      for (ii = qp1; ii < 9; ii++) {
        Vf[(ii + iter) - 1] = e[ii - 1];
      }
    }
  }
  m = 6;
  b_s[7] = b_A[63];
  e[6] = b_A[62];
  e[7] = 0.0;
  memset(&U[56], 0, 8U * sizeof(double));
  U[63] = 1.0;
  for (q = 6; q >= 0; q--) {
    qp1 = q + 2;
    iter = q << 3;
    qq = q + iter;
    if (b_s[q] != 0.0) {
      for (jj = qp1; jj < 9; jj++) {
        qjj = (q + ((jj - 1) << 3)) + 1;
        xaxpy(8 - q, -(xdotc(8 - q, U, qq + 1, U, qjj) / U[qq]), qq + 1, U,
              qjj);
      }
      for (ii = q + 1; ii < 9; ii++) {
        qp1jj = (ii + iter) - 1;
        U[qp1jj] = -U[qp1jj];
      }
      U[qq]++;
      for (ii = 0; ii < q; ii++) {
        U[ii + iter] = 0.0;
      }
    } else {
      memset(&U[iter], 0, 8U * sizeof(double));
      U[qq] = 1.0;
    }
  }
  for (q = 7; q >= 0; q--) {
    if ((q + 1 <= 6) && (e[q] != 0.0)) {
      qp1 = q + 2;
      qjj = (q + (q << 3)) + 2;
      for (jj = qp1; jj < 9; jj++) {
        qp1jj = (q + ((jj - 1) << 3)) + 2;
        xaxpy(7 - q, -(xdotc(7 - q, Vf, qjj, Vf, qp1jj) / Vf[qjj - 1]), qjj, Vf,
              qp1jj);
      }
    }
    memset(&Vf[q * 8], 0, 8U * sizeof(double));
    Vf[q + (q << 3)] = 1.0;
  }
  iter = 0;
  snorm = 0.0;
  for (q = 0; q < 8; q++) {
    nrm = b_s[q];
    if (nrm != 0.0) {
      rt = fabs(nrm);
      nrm /= rt;
      b_s[q] = rt;
      if (q + 1 < 8) {
        e[q] /= nrm;
      }
      qp1jj = q << 3;
      qjj = qp1jj + 8;
      for (k = qp1jj + 1; k <= qjj; k++) {
        U[k - 1] *= nrm;
      }
    }
    if (q + 1 < 8) {
      nrm = e[q];
      if (nrm != 0.0) {
        rt = fabs(nrm);
        nrm = rt / nrm;
        e[q] = rt;
        b_s[q + 1] *= nrm;
        qp1jj = (q + 1) << 3;
        qjj = qp1jj + 8;
        for (k = qp1jj + 1; k <= qjj; k++) {
          Vf[k - 1] *= nrm;
        }
      }
    }
    snorm = fmax(snorm, fmax(fabs(b_s[q]), fabs(e[q])));
  }
  while ((m + 2 > 0) && (iter < 75)) {
    boolean_T exitg1;
    jj = m + 1;
    ii = m + 1;
    exitg1 = false;
    while (!(exitg1 || (ii == 0))) {
      nrm = fabs(e[ii - 1]);
      if ((nrm <=
           2.2204460492503131E-16 * (fabs(b_s[ii - 1]) + fabs(b_s[ii]))) ||
          (nrm <= 1.0020841800044864E-292) ||
          ((iter > 20) && (nrm <= 2.2204460492503131E-16 * snorm))) {
        e[ii - 1] = 0.0;
        exitg1 = true;
      } else {
        ii--;
      }
    }
    if (ii == m + 1) {
      qjj = 4;
    } else {
      qp1jj = m + 2;
      qjj = m + 2;
      exitg1 = false;
      while ((!exitg1) && (qjj >= ii)) {
        qp1jj = qjj;
        if (qjj == ii) {
          exitg1 = true;
        } else {
          nrm = 0.0;
          if (qjj < m + 2) {
            nrm = fabs(e[qjj - 1]);
          }
          if (qjj > ii + 1) {
            nrm += fabs(e[qjj - 2]);
          }
          rt = fabs(b_s[qjj - 1]);
          if ((rt <= 2.2204460492503131E-16 * nrm) ||
              (rt <= 1.0020841800044864E-292)) {
            b_s[qjj - 1] = 0.0;
            exitg1 = true;
          } else {
            qjj--;
          }
        }
      }
      if (qp1jj == ii) {
        qjj = 3;
      } else if (qp1jj == m + 2) {
        qjj = 1;
      } else {
        qjj = 2;
        ii = qp1jj;
      }
    }
    switch (qjj) {
    case 1: {
      rt = e[m];
      e[m] = 0.0;
      for (k = jj; k >= ii + 1; k--) {
        xrotg(&b_s[k - 1], &rt, &sm, &sqds);
        if (k > ii + 1) {
          double b;
          b = e[k - 2];
          rt = -sqds * b;
          e[k - 2] = b * sm;
        }
        xrot(Vf, ((k - 1) << 3) + 1, ((m + 1) << 3) + 1, sm, sqds);
      }
    } break;
    case 2: {
      rt = e[ii - 1];
      e[ii - 1] = 0.0;
      for (k = ii + 1; k <= m + 2; k++) {
        double b;
        xrotg(&b_s[k - 1], &rt, &sm, &sqds);
        b = e[k - 1];
        rt = -sqds * b;
        e[k - 1] = b * sm;
        xrot(U, ((k - 1) << 3) + 1, ((ii - 1) << 3) + 1, sm, sqds);
      }
    } break;
    case 3: {
      double b;
      double scale;
      nrm = b_s[m + 1];
      scale = fmax(
          fmax(fmax(fmax(fabs(nrm), fabs(b_s[m])), fabs(e[m])), fabs(b_s[ii])),
          fabs(e[ii]));
      sm = nrm / scale;
      nrm = b_s[m] / scale;
      rt = e[m] / scale;
      sqds = b_s[ii] / scale;
      b = ((nrm + sm) * (nrm - sm) + rt * rt) / 2.0;
      nrm = sm * rt;
      nrm *= nrm;
      if ((b != 0.0) || (nrm != 0.0)) {
        rt = sqrt(b * b + nrm);
        if (b < 0.0) {
          rt = -rt;
        }
        rt = nrm / (b + rt);
      } else {
        rt = 0.0;
      }
      rt += (sqds + sm) * (sqds - sm);
      nrm = sqds * (e[ii] / scale);
      for (k = ii + 1; k <= jj; k++) {
        xrotg(&rt, &nrm, &sm, &sqds);
        if (k > ii + 1) {
          e[k - 2] = rt;
        }
        nrm = e[k - 1];
        b = b_s[k - 1];
        e[k - 1] = sm * nrm - sqds * b;
        rt = sqds * b_s[k];
        b_s[k] *= sm;
        xrot(Vf, ((k - 1) << 3) + 1, (k << 3) + 1, sm, sqds);
        b_s[k - 1] = sm * b + sqds * nrm;
        xrotg(&b_s[k - 1], &rt, &sm, &sqds);
        rt = sm * e[k - 1] + sqds * b_s[k];
        b_s[k] = -sqds * e[k - 1] + sm * b_s[k];
        nrm = sqds * e[k];
        e[k] *= sm;
        xrot(U, ((k - 1) << 3) + 1, (k << 3) + 1, sm, sqds);
      }
      e[m] = rt;
      iter++;
    } break;
    default:
      if (b_s[ii] < 0.0) {
        b_s[ii] = -b_s[ii];
        qp1jj = ii << 3;
        qjj = qp1jj + 8;
        for (k = qp1jj + 1; k <= qjj; k++) {
          Vf[k - 1] = -Vf[k - 1];
        }
      }
      qp1 = ii + 1;
      while ((ii + 1 < 8) && (b_s[ii] < b_s[qp1])) {
        rt = b_s[ii];
        b_s[ii] = b_s[qp1];
        b_s[qp1] = rt;
        xswap(Vf, (ii << 3) + 1, ((ii + 1) << 3) + 1);
        xswap(U, (ii << 3) + 1, ((ii + 1) << 3) + 1);
        ii = qp1;
        qp1++;
      }
      iter = 0;
      m--;
      break;
    }
  }
  for (k = 0; k < 8; k++) {
    s[k] = b_s[k];
    memcpy(&V[k * 8], &Vf[k * 8], 8U * sizeof(double));
  }
}

/* End of code generation (svd.c) */
