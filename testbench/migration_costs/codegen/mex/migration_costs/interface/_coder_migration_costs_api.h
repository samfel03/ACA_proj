//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_migration_costs_api.h
//
// Code generation for function '_coder_migration_costs_api'
//

#pragma once

// Include files
#include "rtwtypes.h"
#include "covrt.h"
#include "emlrt.h"
#include "mex.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// Function Declarations
void MEXGlobalSyncInFunction(const emlrtStack *sp);

void MEXGlobalSyncOutFunction(boolean_T skipDirtyCheck);

void emlrt_synchGlobalsFromML(const emlrtStack *sp);

void emlrt_synchGlobalsToML(const emlrtStack *sp);

void migration_costs_api(const mxArray *const prhs[6], const mxArray **plhs);

// End of code generation (_coder_migration_costs_api.h)
