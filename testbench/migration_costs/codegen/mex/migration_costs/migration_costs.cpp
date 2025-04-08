//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// migration_costs.cpp
//
// Code generation for function 'migration_costs'
//

// Include files
#include "migration_costs.h"
#include "migration_costs_data.h"
#include "power.h"
#include "rt_nonfinite.h"
#include "sumMatrixIncludeNaN.h"
#include "mwmathutil.h"

// Variable Definitions
static emlrtRSInfo emlrtRSI{
    35,                // lineNo
    "migration_costs", // fcnName
    "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/testbench/"
    "migration_costs/migration_costs.m" // pathName
};

static emlrtRSInfo b_emlrtRSI{
    36,                // lineNo
    "migration_costs", // fcnName
    "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/testbench/"
    "migration_costs/migration_costs.m" // pathName
};

static emlrtRSInfo c_emlrtRSI{
    37,                // lineNo
    "migration_costs", // fcnName
    "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/testbench/"
    "migration_costs/migration_costs.m" // pathName
};

static emlrtRSInfo d_emlrtRSI{
    38,                // lineNo
    "migration_costs", // fcnName
    "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/testbench/"
    "migration_costs/migration_costs.m" // pathName
};

static emlrtRSInfo e_emlrtRSI{
    41,                // lineNo
    "migration_costs", // fcnName
    "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/testbench/"
    "migration_costs/migration_costs.m" // pathName
};

static emlrtRSInfo f_emlrtRSI{
    42,                // lineNo
    "migration_costs", // fcnName
    "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/testbench/"
    "migration_costs/migration_costs.m" // pathName
};

static emlrtRSInfo g_emlrtRSI{
    43,                // lineNo
    "migration_costs", // fcnName
    "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/testbench/"
    "migration_costs/migration_costs.m" // pathName
};

static emlrtRSInfo h_emlrtRSI{
    44,                // lineNo
    "migration_costs", // fcnName
    "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/testbench/"
    "migration_costs/migration_costs.m" // pathName
};

static emlrtRSInfo i_emlrtRSI{
    45,                // lineNo
    "migration_costs", // fcnName
    "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/testbench/"
    "migration_costs/migration_costs.m" // pathName
};

static emlrtRSInfo j_emlrtRSI{
    49,                // lineNo
    "migration_costs", // fcnName
    "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/testbench/"
    "migration_costs/migration_costs.m" // pathName
};

static emlrtRSInfo k_emlrtRSI{
    50,                // lineNo
    "migration_costs", // fcnName
    "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/testbench/"
    "migration_costs/migration_costs.m" // pathName
};

// Function Definitions
void migration_costs(const emlrtStack *sp, real_T m2_i[10],
                     const real_T amen[10], const real_T prod[10],
                     const real_T pop[10], const real_T price_energy[10],
                     real_T tol_m2, real_T m2_f[10])
{
  emlrtStack st;
  real_T ML[10];
  real_T MR[10];
  real_T dv[10];
  real_T dv1[10];
  real_T dv2[10];
  real_T rhs[10];
  real_T c_tmp;
  real_T denom;
  real_T denom2;
  real_T flatL;
  real_T squ;
  int32_T idx;
  int32_T k;
  st.prev = sp;
  st.tls = sp->tls;
  covrtLogFcn(&emlrtCoverageInstance, 0, 0);
  covrtLogBasicBlock(&emlrtCoverageInstance, 0, 0);
  //  Function that computes the migration costs, as displayed in
  //  Supplementary Materials Section F.5
  //  Inputs:
  //    m2_i: guess for the migration cost function
  //    amen, prod, pop, price_emi: cell-level amenities, productivity,
  //    population to be matched andenergy price.
  //    tol_m2: tolerance for the error
  //  Output:
  //    m2_f: solution for the migration cost function
  //  Pre-computed quantities
  denom = 2.0 * theta + 1.0;
  denom2 = theta + 1.0;
  squ = (alpha - 1.0) + ((lambda + gamma1 / ksi) - (1.0 - mu)) * theta;
  flatL = lambda - squ / denom;
  squ = (1.0 - lambda * theta) + (theta + 1.0) * squ / denom;
  //  Compute terms outside the integral of equation (91)
  st.site = &emlrtRSI;
  coder::power(&st, prod, 1.0 / denom2, ML);
  st.site = &b_emlrtRSI;
  coder::power(&st, H, -Omega - 1.0 / denom2, rhs);
  st.site = &c_emlrtRSI;
  coder::power(&st, pop, -flatL * denom / denom2 - Omega, dv);
  st.site = &d_emlrtRSI;
  coder::power(&st, price_energy, -theta * mu * (1.0 - chi) / denom2, dv1);
  for (idx = 0; idx < 10; idx++) {
    ML[idx] = amen[idx] * ML[idx] * rhs[idx] * dv[idx] * dv1[idx];
  }
  //  Compute terms inside the integral of equation (91)
  c_tmp = theta * theta;
  st.site = &e_emlrtRSI;
  coder::power(&st, amen, c_tmp / denom, MR);
  st.site = &f_emlrtRSI;
  coder::power(&st, prod, (theta + 1.0) / denom, rhs);
  st.site = &g_emlrtRSI;
  coder::power(&st, H, theta * (1.0 - theta * Omega) / denom, dv);
  st.site = &h_emlrtRSI;
  coder::power(&st, pop, squ - c_tmp * Omega / denom, dv1);
  st.site = &i_emlrtRSI;
  coder::power(&st, price_energy,
               -theta * (theta + 1.0) * mu * (1.0 - chi) / denom, dv2);
  for (idx = 0; idx < 10; idx++) {
    MR[idx] = MR[idx] * rhs[idx] * dv[idx] * dv1[idx] * dv2[idx];
  }
  squ = tol_m2 + 1.0;
  while (covrtLogWhile(&emlrtCoverageInstance, 0, 0, 0, squ >= tol_m2)) {
    covrtLogBasicBlock(&emlrtCoverageInstance, 0, 1);
    st.site = &j_emlrtRSI;
    coder::power(&st, m2_i, -c_tmp / denom, rhs);
    for (idx = 0; idx < 10; idx++) {
      rhs[idx] = trmult_reduced * (MR[idx] * rhs[idx]);
    }
    st.site = &k_emlrtRSI;
    coder::power(&st, rhs, denom / (theta * denom2), m2_f);
    for (k = 0; k < 10; k++) {
      flatL = ML[k] * m2_f[k];
      m2_f[k] = flatL;
      squ = flatL - m2_i[k];
      rhs[k] = squ * squ;
      m2_i[k] = flatL;
    }
    squ = coder::sumColumnB(rhs);
    if (*emlrtBreakCheckR2012bFlagVar != 0) {
      emlrtBreakCheckR2012b((emlrtCTX)sp);
    }
  }
  covrtLogBasicBlock(&emlrtCoverageInstance, 0, 2);
  //  Normalize m2 such that minimum equals one
  if (!muDoubleScalarIsNaN(m2_i[0])) {
    idx = 1;
  } else {
    boolean_T exitg1;
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 11)) {
      if (!muDoubleScalarIsNaN(m2_i[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (idx == 0) {
    squ = m2_i[0];
  } else {
    squ = m2_i[idx - 1];
    idx++;
    for (k = idx; k < 11; k++) {
      flatL = m2_i[k - 1];
      if (squ > flatL) {
        squ = flatL;
      }
    }
  }
  for (idx = 0; idx < 10; idx++) {
    m2_f[idx] = m2_i[idx] / squ;
  }
}

// End of code generation (migration_costs.cpp)
