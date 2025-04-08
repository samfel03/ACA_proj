//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// power.cpp
//
// Code generation for function 'power'
//

// Include files
#include "power.h"
#include "migration_costs_data.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"

// Variable Definitions
static emlrtRSInfo l_emlrtRSI{
    71,      // lineNo
    "power", // fcnName
    "/Applications/MATLAB_R2021b.app/toolbox/eml/lib/matlab/ops/power.m" // pathName
};

static emlrtRTEInfo emlrtRTEI{
    82,         // lineNo
    5,          // colNo
    "fltpower", // fName
    "/Applications/MATLAB_R2021b.app/toolbox/eml/lib/matlab/ops/power.m" // pName
};

// Function Definitions
namespace coder {
void power(const emlrtStack *sp, const real_T a[10], real_T b, real_T y[10])
{
  emlrtStack st;
  int32_T k;
  boolean_T p;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &l_emlrtRSI;
  if ((!muDoubleScalarIsNaN(b)) && (muDoubleScalarFloor(b) != b)) {
    p = false;
    for (k = 0; k < 10; k++) {
      if (p || (a[k] < 0.0)) {
        p = true;
      }
    }
  } else {
    p = false;
  }
  if (p) {
    emlrtErrorWithMessageIdR2018a(&st, &emlrtRTEI,
                                  "Coder:toolbox:power_domainError",
                                  "Coder:toolbox:power_domainError", 0);
  }
  for (k = 0; k < 10; k++) {
    y[k] = muDoubleScalarPower(a[k], b);
  }
}

} // namespace coder

// End of code generation (power.cpp)
