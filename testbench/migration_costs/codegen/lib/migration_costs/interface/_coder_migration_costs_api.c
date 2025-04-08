/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_migration_costs_api.c
 *
 * MATLAB Coder version            : 5.3
 * C/C++ source code generated on  : 11-May-2022 10:40:10
 */

/* Include Files */
#include "_coder_migration_costs_api.h"
#include "_coder_migration_costs_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;

static real_T theta;

static uint32_T theta_guard;

static real_T alpha;

static uint32_T alpha_guard;

static real_T lambda;

static uint32_T lambda_guard;

static real_T gamma1;

static uint32_T gamma1_guard;

static real_T ksi;

static uint32_T ksi_guard;

static real_T mu;

static uint32_T mu_guard;

static real_T H[10];

static uint32_T H_guard;

static real_T Omega;

static uint32_T Omega_guard;

static real_T chi;

static uint32_T chi_guard;

static real_T trmult_reduced;

static uint32_T trmult_reduced_guard;

emlrtContext emlrtContextGlobal = {
    true,                                                 /* bFirstTime */
    false,                                                /* bInitialized */
    131611U,                                              /* fVersionInfo */
    NULL,                                                 /* fErrorFunction */
    "migration_costs",                                    /* fFunctionName */
    NULL,                                                 /* fRTCallStack */
    false,                                                /* bDebugMode */
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, /* fSigWrd */
    NULL                                                  /* fSigMem */
};

/* Function Declarations */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId);

static const mxArray *b_emlrt_marshallOut(const real_T u[10]);

static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_H,
                               const char_T *identifier, real_T y[10]);

static const mxArray *c_emlrt_marshallOut(const real_T u[10]);

static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId,
                               real_T y[10]);

static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *m2_i,
                                   const char_T *identifier))[10];

static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_theta,
                               const char_T *identifier);

static const mxArray *emlrt_marshallOut(const real_T u);

static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[10];

static real_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[10]);

static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[10];

static void migration_costs_once(void);

/* Function Definitions */
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = g_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const real_T u[10]
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const real_T u[10])
{
  static const int32_T i = 10;
  const mxArray *m;
  const mxArray *y;
  real_T *pData;
  int32_T b_i;
  y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  for (b_i = 0; b_i < 10; b_i++) {
    pData[b_i] = u[b_i];
  }
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *b_H
 *                const char_T *identifier
 *                real_T y[10]
 * Return Type  : void
 */
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_H,
                               const char_T *identifier, real_T y[10])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(sp, emlrtAlias(b_H), &thisId, y);
  emlrtDestroyArray(&b_H);
}

/*
 * Arguments    : const real_T u[10]
 * Return Type  : const mxArray *
 */
static const mxArray *c_emlrt_marshallOut(const real_T u[10])
{
  static const int32_T i = 0;
  static const int32_T i1 = 10;
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &i1, 1);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real_T y[10]
 * Return Type  : void
 */
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId, real_T y[10])
{
  h_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *m2_i
 *                const char_T *identifier
 * Return Type  : real_T (*)[10]
 */
static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *m2_i,
                                   const char_T *identifier))[10]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[10];
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(sp, emlrtAlias(m2_i), &thisId);
  emlrtDestroyArray(&m2_i);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *b_theta
 *                const char_T *identifier
 * Return Type  : real_T
 */
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_theta,
                               const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(b_theta), &thisId);
  emlrtDestroyArray(&b_theta);
  return y;
}

/*
 * Arguments    : const real_T u
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[10]
 */
static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[10]
{
  real_T(*y)[10];
  y = i_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
static real_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 0U, (void *)&dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real_T ret[10]
 * Return Type  : void
 */
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[10])
{
  static const int32_T dims = 10;
  real_T(*r)[10];
  int32_T i;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 1U, (void *)&dims);
  r = (real_T(*)[10])emlrtMxGetData(src);
  for (i = 0; i < 10; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[10]
 */
static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[10]
{
  static const int32_T dims = 10;
  real_T(*ret)[10];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 1U, (void *)&dims);
  ret = (real_T(*)[10])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void migration_costs_once(void)
{
  trmult_reduced_guard = 0U;
  chi_guard = 0U;
  Omega_guard = 0U;
  H_guard = 0U;
  mu_guard = 0U;
  ksi_guard = 0U;
  gamma1_guard = 0U;
  lambda_guard = 0U;
  alpha_guard = 0U;
  theta_guard = 0U;
}

/*
 * Arguments    : const emlrtStack *sp
 * Return Type  : void
 */
void MEXGlobalSyncInFunction(const emlrtStack *sp)
{
  const mxArray *tmp;
  /* Marshall in global variables */
  tmp = emlrtGetGlobalVariable((const char_T *)"theta");
  if (tmp != NULL) {
    theta = emlrt_marshallIn(sp, tmp, "theta");
    theta_guard = 1U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"alpha");
  if (tmp != NULL) {
    alpha = emlrt_marshallIn(sp, tmp, "alpha");
    alpha_guard = 1U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"lambda");
  if (tmp != NULL) {
    lambda = emlrt_marshallIn(sp, tmp, "lambda");
    lambda_guard = 1U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"gamma1");
  if (tmp != NULL) {
    gamma1 = emlrt_marshallIn(sp, tmp, "gamma1");
    gamma1_guard = 1U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"ksi");
  if (tmp != NULL) {
    ksi = emlrt_marshallIn(sp, tmp, "ksi");
    ksi_guard = 1U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"mu");
  if (tmp != NULL) {
    mu = emlrt_marshallIn(sp, tmp, "mu");
    mu_guard = 1U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"H");
  if (tmp != NULL) {
    c_emlrt_marshallIn(sp, tmp, "H", H);
    H_guard = 1U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"Omega");
  if (tmp != NULL) {
    Omega = emlrt_marshallIn(sp, tmp, "Omega");
    Omega_guard = 1U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"chi");
  if (tmp != NULL) {
    chi = emlrt_marshallIn(sp, tmp, "chi");
    chi_guard = 1U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"trmult_reduced");
  if (tmp != NULL) {
    trmult_reduced = emlrt_marshallIn(sp, tmp, "trmult_reduced");
    trmult_reduced_guard = 1U;
  }
}

/*
 * Arguments    : boolean_T skipDirtyCheck
 * Return Type  : void
 */
void MEXGlobalSyncOutFunction(boolean_T skipDirtyCheck)
{
  /* Marshall out global variables */
  if (skipDirtyCheck || (theta_guard != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"theta", emlrt_marshallOut(theta));
  }
  if (skipDirtyCheck || (alpha_guard != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"alpha", emlrt_marshallOut(alpha));
  }
  if (skipDirtyCheck || (lambda_guard != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"lambda", emlrt_marshallOut(lambda));
  }
  if (skipDirtyCheck || (gamma1_guard != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"gamma1", emlrt_marshallOut(gamma1));
  }
  if (skipDirtyCheck || (ksi_guard != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"ksi", emlrt_marshallOut(ksi));
  }
  if (skipDirtyCheck || (mu_guard != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"mu", emlrt_marshallOut(mu));
  }
  if (skipDirtyCheck || (H_guard != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"H", b_emlrt_marshallOut(H));
  }
  if (skipDirtyCheck || (Omega_guard != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"Omega", emlrt_marshallOut(Omega));
  }
  if (skipDirtyCheck || (chi_guard != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"chi", emlrt_marshallOut(chi));
  }
  if (skipDirtyCheck || (trmult_reduced_guard != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"trmult_reduced",
                           emlrt_marshallOut(trmult_reduced));
  }
}

/*
 * Arguments    : const mxArray * const prhs[6]
 *                const mxArray **plhs
 * Return Type  : void
 */
void migration_costs_api(const mxArray *const prhs[6], const mxArray **plhs)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  const mxArray *prhs_copy_idx_0;
  real_T(*amen)[10];
  real_T(*m2_f)[10];
  real_T(*m2_i)[10];
  real_T(*pop)[10];
  real_T(*price_energy)[10];
  real_T(*prod)[10];
  real_T tol_m2;
  st.tls = emlrtRootTLSGlobal;
  m2_f = (real_T(*)[10])mxMalloc(sizeof(real_T[10]));
  prhs_copy_idx_0 = emlrtProtectR2012b(prhs[0], 0, false, -1);
  /* Marshall function inputs */
  m2_i = e_emlrt_marshallIn(&st, emlrtAlias(prhs_copy_idx_0), "m2_i");
  amen = e_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "amen");
  prod = e_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "prod");
  pop = e_emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "pop");
  price_energy = e_emlrt_marshallIn(&st, emlrtAlias(prhs[4]), "price_energy");
  tol_m2 = emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "tol_m2");
  /* Marshall in global variables */
  MEXGlobalSyncInFunction(&st);
  /* Invoke the target function */
  migration_costs(*m2_i, *amen, *prod, *pop, *price_energy, tol_m2, *m2_f);
  /* Marshall out global variables */
  MEXGlobalSyncOutFunction(true);
  /* Marshall function outputs */
  *plhs = c_emlrt_marshallOut(*m2_f);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void migration_costs_atexit(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  migration_costs_xil_terminate();
  migration_costs_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void migration_costs_initialize(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  if (emlrtFirstTimeR2012b(emlrtRootTLSGlobal)) {
    migration_costs_once();
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void migration_costs_terminate(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_migration_costs_api.c
 *
 * [EOF]
 */
