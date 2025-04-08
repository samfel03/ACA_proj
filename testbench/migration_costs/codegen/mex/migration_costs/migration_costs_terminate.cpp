//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// migration_costs_terminate.cpp
//
// Code generation for function 'migration_costs_terminate'
//

// Include files
#include "migration_costs_terminate.h"
#include "_coder_migration_costs_api.h"
#include "_coder_migration_costs_mex.h"
#include "migration_costs_data.h"
#include "rt_nonfinite.h"

// Function Definitions
void migration_costs_atexit()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrt_synchGlobalsFromML(&st);
  // Free instance data
  covrtFreeInstanceData(&emlrtCoverageInstance);
  emlrt_synchGlobalsToML(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void migration_costs_terminate()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

// End of code generation (migration_costs_terminate.cpp)
