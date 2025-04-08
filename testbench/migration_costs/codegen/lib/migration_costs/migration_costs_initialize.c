/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: migration_costs_initialize.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 11-May-2022 10:40:10
 */

/* Include Files */
#include "migration_costs_initialize.h"
#include "migration_costs_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void migration_costs_initialize(void)
{
  int i;
  trmult_reduced = 1.0;
  chi = 4.0;
  Omega = 0.5;
  for (i = 0; i < 10; i++) {
    H[i] = 1.0;
  }
  mu = 0.8;
  ksi = 125.0;
  gamma1 = 0.319;
  lambda = 0.32;
  alpha = 0.06;
  theta = 6.5;
  isInitialized_migration_costs = true;
}

/*
 * File trailer for migration_costs_initialize.c
 *
 * [EOF]
 */
