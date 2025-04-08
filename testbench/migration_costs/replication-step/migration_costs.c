/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: migration_costs.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 11-May-2022 10:40:10
 */

/* Include Files */
#include "migration_costs.h"
#include "migration_costs_data.h"
#include "migration_costs_initialize.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static double rt_powd_snf(double u0, double u1);

/* Function Definitions */
/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_powd_snf(double u0, double u1)
{
  double d;
  double d1;
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    d = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }
  return y;
}

/*
 * Function that computes the migration costs, as displayed in
 *  Supplementary Materials Section F.5
 *  Inputs:
 *    m2_i: guess for the migration cost function
 *    amen, prod, pop, price_emi: cell-level amenities, productivity,
 *    population to be matched andenergy price.
 *    tol_m2: tolerance for the error
 *  Output:
 *    m2_f: solution for the migration cost function
 *
 * Arguments    : double m2_i[10]
 *                const double amen[10]
 *                const double prod[10]
 *                const double pop[10]
 *                const double price_energy[10]
 *                double tol_m2
 *                double m2_f[10]
 * Return Type  : void
 */
void migration_costs(double m2_i[10], const double amen[10],
                     const double prod[10], const double pop[10],
                     const double price_energy[10], double tol_m2,
                     double m2_f[10])
{
  double ML[10];
  double MR[10];
  double y[10];
  double b;
  double b_b;
  double b_b_tmp;
  double b_tmp;
  double c_b;
  double d;
  double d1;
  double d2;
  double d3;
  double d_b;
  double denom;
  double e_b;
  double f_b;
  double g_b;
  double h_b;
  double i_b;
  double squ;
  int idx;
  int k;
  boolean_T exitg1;
  if (!isInitialized_migration_costs) {
    migration_costs_initialize();
  }
  /*  Pre-computed quantities */
  denom = 2.0 * theta + 1.0;
  squ = (alpha - 1.0) + ((lambda + gamma1 / ksi) - (1.0 - mu)) * theta;
  /*  Compute terms outside the integral of equation (91) */
  b_tmp = 1.0 / (theta + 1.0);
  b = -Omega - b_tmp;
  b_b = -(lambda - squ / denom) * denom / (theta + 1.0) - Omega;
  c_b = -theta * mu * (1.0 - chi) / (theta + 1.0);
  /*  Compute terms inside the integral of equation (91) */
  b_b_tmp = theta * theta;
  d_b = b_b_tmp / denom;
  e_b = (theta + 1.0) / denom;
  f_b = theta * (1.0 - theta * Omega) / denom;
  squ = ((1.0 - lambda * theta) + (theta + 1.0) * squ / denom) -
        b_b_tmp * Omega / denom;
  g_b = -theta * (theta + 1.0) * mu * (1.0 - chi) / denom;
  for (k = 0; k < 10; k++) {
    d = amen[k];
    d1 = prod[k];
    d2 = pop[k];
    d3 = price_energy[k];
    ML[k] = d * rt_powd_snf(d1, b_tmp) * rt_powd_snf(H[k], b) *
            rt_powd_snf(d2, b_b) * rt_powd_snf(d3, c_b);
    MR[k] = rt_powd_snf(d, d_b) * rt_powd_snf(d1, e_b) *
            rt_powd_snf(H[k], f_b) * rt_powd_snf(d2, squ) *
            rt_powd_snf(d3, g_b);
  }
  squ = tol_m2 + 1.0;
  if (squ >= tol_m2) {
    h_b = -b_b_tmp / denom;
    i_b = denom / (theta * (theta + 1.0));
  }
  squ = tol_m2 + 1.0;
  while (squ >= tol_m2) {
    for (k = 0; k < 10; k++) {
      d = m2_i[k];
      d1 = ML[k] *
           rt_powd_snf(trmult_reduced * (MR[k] * rt_powd_snf(d, h_b)), i_b);
      m2_f[k] = d1;
      d = d1 - d;
      m2_i[k] = d;
      y[k] = d * d;
    }
    squ = y[0];
    for (k = 0; k < 9; k++) {
      squ += y[k + 1];
    }
    memcpy(&m2_i[0], &m2_f[0], 10U * sizeof(double));
  }
  /*  Normalize m2 such that minimum equals one */
  if (!rtIsNaN(m2_i[0])) {
    idx = 1;
  } else {
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 11)) {
      if (!rtIsNaN(m2_i[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (idx == 0) {
    squ = m2_i[0];
  } else {
    squ = m2_i[idx - 1];
    idx++;
    for (k = idx; k < 11; k++) {
      d = m2_i[k - 1];
      if (squ > d) {
        squ = d;
      }
    }
  }
  for (idx = 0; idx < 10; idx++) {
    m2_f[idx] = m2_i[idx] / squ;
  }
}

/*
 * File trailer for migration_costs.c
 *
 * [EOF]
 */
