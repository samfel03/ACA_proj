/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_migration_costs_api.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 11-May-2022 10:40:10
 */

#ifndef _CODER_MIGRATION_COSTS_API_H
#define _CODER_MIGRATION_COSTS_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void MEXGlobalSyncInFunction(const emlrtStack *sp);

void MEXGlobalSyncOutFunction(boolean_T skipDirtyCheck);

void migration_costs(real_T m2_i[10], real_T amen[10], real_T prod[10],
                     real_T pop[10], real_T price_energy[10], real_T tol_m2,
                     real_T m2_f[10]);

void migration_costs_api(const mxArray *const prhs[6], const mxArray **plhs);

void migration_costs_atexit(void);

void migration_costs_initialize(void);

void migration_costs_terminate(void);

void migration_costs_xil_shutdown(void);

void migration_costs_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_migration_costs_api.h
 *
 * [EOF]
 */
