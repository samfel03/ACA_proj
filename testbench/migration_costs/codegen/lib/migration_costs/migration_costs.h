/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: migration_costs.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 11-May-2022 10:40:10
 */

#ifndef MIGRATION_COSTS_H
#define MIGRATION_COSTS_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void migration_costs(double m2_i[10], const double amen[10],
                            const double prod[10], const double pop[10],
                            const double price_energy[10], double tol_m2,
                            double m2_f[10]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for migration_costs.h
 *
 * [EOF]
 */
