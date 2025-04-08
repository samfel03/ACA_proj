//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// migration_costs.h
//
// Code generation for function 'migration_costs'
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
void migration_costs(const emlrtStack *sp, real_T m2_i[10],
                     const real_T amen[10], const real_T prod[10],
                     const real_T pop[10], const real_T price_energy[10],
                     real_T tol_m2, real_T m2_f[10]);

// End of code generation (migration_costs.h)
