/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_call_rcond_api.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 28-May-2022 18:13:52
 */

#ifndef _CODER_CALL_RCOND_API_H
#define _CODER_CALL_RCOND_API_H

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
real_T call_rcond(real_T X[73410624]);

void call_rcond_api(const mxArray *prhs, const mxArray **plhs);

void call_rcond_atexit(void);

void call_rcond_initialize(void);

void call_rcond_terminate(void);

void call_rcond_xil_shutdown(void);

void call_rcond_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_call_rcond_api.h
 *
 * [EOF]
 */
