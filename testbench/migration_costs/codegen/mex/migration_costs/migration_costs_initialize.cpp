//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// migration_costs_initialize.cpp
//
// Code generation for function 'migration_costs_initialize'
//

// Include files
#include "migration_costs_initialize.h"
#include "_coder_migration_costs_api.h"
#include "_coder_migration_costs_mex.h"
#include "migration_costs_data.h"
#include "rt_nonfinite.h"

// Function Declarations
static void migration_costs_once(const emlrtStack *sp);

// Function Definitions
static void migration_costs_once(const emlrtStack *sp)
{
  mex_InitInfAndNan();
  trmult_reduced = 1.0;
  trmult_reduced_dirty = 1U;
  chi = 4.0;
  chi_dirty = 1U;
  Omega = 0.5;
  Omega_dirty = 1U;
  for (int32_T i{0}; i < 10; i++) {
    H[i] = 1.0;
  }
  H_dirty = 1U;
  mu = 0.8;
  mu_dirty = 1U;
  ksi = 125.0;
  ksi_dirty = 1U;
  gamma1 = 0.319;
  gamma1_dirty = 1U;
  lambda = 0.32;
  lambda_dirty = 1U;
  alpha = 0.06;
  alpha_dirty = 1U;
  theta = 6.5;
  theta_dirty = 1U;
  // Allocate instance data
  covrtAllocateInstanceData(&emlrtCoverageInstance);
  // Initialize Coverage Information
  covrtScriptInit(&emlrtCoverageInstance,
                  "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/"
                  "testbench/migration_costs/migration_costs.m",
                  0U, 1U, 3U, 0U, 0U, 0U, 0U, 0U, 1U, 0U, 0U);
  // Initialize Function Information
  covrtFcnInit(&emlrtCoverageInstance, 0U, 0U, "migration_costs", 10, -1, 1561);
  // Initialize Basic Block Information
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 1U, 1333, -1, 1482);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 2U, 1532, -1, 1556);
  covrtBasicBlockInit(&emlrtCoverageInstance, 0U, 0U, 630, -1, 1302);
  // Initialize If Information
  // Initialize MCDC Information
  // Initialize For Information
  // Initialize While Information
  covrtWhileInit(&emlrtCoverageInstance, 0U, 0U, 1303, 1327, 1486);
  // Initialize Switch Information
  // Start callback for coverage engine
  covrtScriptStart(&emlrtCoverageInstance, 0U);
  emlrtSetGlobalSyncFcn((emlrtCTX)sp, (void *)&emlrt_synchGlobalsToML);
}

void migration_costs_initialize()
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
  };
  mexFunctionCreateRootTLS();
  emlrtBreakCheckR2012bFlagVar = emlrtGetBreakCheckFlagAddressR2012b();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, nullptr);
  emlrtEnterRtStackR2012b(&st);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    migration_costs_once(&st);
  }
}

// End of code generation (migration_costs_initialize.cpp)
