/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_call_rcond_mex.h
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 28-May-2022 18:13:52
 */

#ifndef _CODER_CALL_RCOND_MEX_H
#define _CODER_CALL_RCOND_MEX_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS(void);

void unsafe_call_rcond_mexFunction(int32_T nlhs, mxArray *plhs[1], int32_T nrhs,
                                   const mxArray *prhs[1]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_call_rcond_mex.h
 *
 * [EOF]
 */
