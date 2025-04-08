//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// migration_costs_data.cpp
//
// Code generation for function 'migration_costs_data'
//

// Include files
#include "migration_costs_data.h"
#include "rt_nonfinite.h"

// Variable Definitions
emlrtCTX emlrtRootTLSGlobal{nullptr};

const volatile char_T *emlrtBreakCheckR2012bFlagVar{nullptr};

real_T theta;

real_T alpha;

real_T lambda;

real_T gamma1;

real_T ksi;

real_T mu;

real_T H[10];

real_T Omega;

real_T chi;

real_T trmult_reduced;

uint32_T theta_dirty;

uint32_T alpha_dirty;

uint32_T lambda_dirty;

uint32_T gamma1_dirty;

uint32_T ksi_dirty;

uint32_T mu_dirty;

uint32_T H_dirty;

uint32_T Omega_dirty;

uint32_T chi_dirty;

uint32_T trmult_reduced_dirty;

emlrtContext emlrtContextGlobal{
    true,                                                 // bFirstTime
    false,                                                // bInitialized
    131611U,                                              // fVersionInfo
    nullptr,                                              // fErrorFunction
    "migration_costs",                                    // fFunctionName
    nullptr,                                              // fRTCallStack
    false,                                                // bDebugMode
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, // fSigWrd
    nullptr                                               // fSigMem
};

covrtInstance emlrtCoverageInstance;

// End of code generation (migration_costs_data.cpp)
