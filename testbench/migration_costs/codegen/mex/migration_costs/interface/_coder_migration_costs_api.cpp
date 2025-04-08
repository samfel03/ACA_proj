//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// _coder_migration_costs_api.cpp
//
// Code generation for function '_coder_migration_costs_api'
//

// Include files
#include "_coder_migration_costs_api.h"
#include "migration_costs.h"
#include "migration_costs_data.h"
#include "rt_nonfinite.h"

// Function Declarations
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *m2_i,
                                   const char_T *identifier))[10];

static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[10];

static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[10]);

static const mxArray *b_emlrt_marshallOut(const real_T u[10]);

static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[10];

static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_theta,
                               const char_T *identifier);

static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_H,
                             const char_T *identifier, real_T y[10]);

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, real_T y[10]);

static const mxArray *emlrt_marshallOut(const real_T u[10]);

static const mxArray *emlrt_marshallOut(const real_T u);

// Function Definitions
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *m2_i,
                                   const char_T *identifier))[10]
{
  emlrtMsgIdentifier thisId;
  real_T(*y)[10];
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(m2_i), &thisId);
  emlrtDestroyArray(&m2_i);
  return y;
}

static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                   const emlrtMsgIdentifier *parentId))[10]
{
  real_T(*y)[10];
  y = d_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                               const emlrtMsgIdentifier *msgId, real_T ret[10])
{
  static const int32_T dims{10};
  real_T(*r)[10];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 1U, (void *)&dims);
  r = (real_T(*)[10])emlrtMxGetData(src);
  for (int32_T i{0}; i < 10; i++) {
    ret[i] = (*r)[i];
  }
  emlrtDestroyArray(&src);
}

static const mxArray *b_emlrt_marshallOut(const real_T u[10])
{
  static const int32_T i{0};
  static const int32_T i1{10};
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m, &i1, 1);
  emlrtAssign(&y, m);
  return y;
}

static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims{0};
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 0U, (void *)&dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                   const emlrtMsgIdentifier *msgId))[10]
{
  static const int32_T dims{10};
  real_T(*ret)[10];
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 1U, (void *)&dims);
  ret = (real_T(*)[10])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_theta,
                               const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  y = emlrt_marshallIn(sp, emlrtAlias(b_theta), &thisId);
  emlrtDestroyArray(&b_theta);
  return y;
}

static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                               const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *b_H,
                             const char_T *identifier, real_T y[10])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = const_cast<const char_T *>(identifier);
  thisId.fParent = nullptr;
  thisId.bParentIsCell = false;
  emlrt_marshallIn(sp, emlrtAlias(b_H), &thisId, y);
  emlrtDestroyArray(&b_H);
}

static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                             const emlrtMsgIdentifier *parentId, real_T y[10])
{
  b_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

static const mxArray *emlrt_marshallOut(const real_T u[10])
{
  static const int32_T i{10};
  const mxArray *m;
  const mxArray *y;
  real_T *pData;
  y = nullptr;
  m = emlrtCreateNumericArray(1, (const void *)&i, mxDOUBLE_CLASS, mxREAL);
  pData = emlrtMxGetPr(m);
  for (int32_T b_i{0}; b_i < 10; b_i++) {
    pData[b_i] = u[b_i];
  }
  emlrtAssign(&y, m);
  return y;
}

static const mxArray *emlrt_marshallOut(const real_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = nullptr;
  m = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m);
  return y;
}

void MEXGlobalSyncInFunction(const emlrtStack *sp)
{
  const mxArray *tmp;
  // Marshall in global variables
  tmp = emlrtGetGlobalVariable((const char_T *)"theta");
  if (tmp != nullptr) {
    theta = emlrt_marshallIn(sp, tmp, "theta");
    theta_dirty = 0U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"alpha");
  if (tmp != nullptr) {
    alpha = emlrt_marshallIn(sp, tmp, "alpha");
    alpha_dirty = 0U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"lambda");
  if (tmp != nullptr) {
    lambda = emlrt_marshallIn(sp, tmp, "lambda");
    lambda_dirty = 0U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"gamma1");
  if (tmp != nullptr) {
    gamma1 = emlrt_marshallIn(sp, tmp, "gamma1");
    gamma1_dirty = 0U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"ksi");
  if (tmp != nullptr) {
    ksi = emlrt_marshallIn(sp, tmp, "ksi");
    ksi_dirty = 0U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"mu");
  if (tmp != nullptr) {
    mu = emlrt_marshallIn(sp, tmp, "mu");
    mu_dirty = 0U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"H");
  if (tmp != nullptr) {
    emlrt_marshallIn(sp, tmp, "H", H);
    H_dirty = 0U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"Omega");
  if (tmp != nullptr) {
    Omega = emlrt_marshallIn(sp, tmp, "Omega");
    Omega_dirty = 0U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"chi");
  if (tmp != nullptr) {
    chi = emlrt_marshallIn(sp, tmp, "chi");
    chi_dirty = 0U;
  }
  tmp = emlrtGetGlobalVariable((const char_T *)"trmult_reduced");
  if (tmp != nullptr) {
    trmult_reduced = emlrt_marshallIn(sp, tmp, "trmult_reduced");
    trmult_reduced_dirty = 0U;
  }
}

void MEXGlobalSyncOutFunction(boolean_T skipDirtyCheck)
{
  // Marshall out global variables
  if (skipDirtyCheck || (theta_dirty != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"theta", emlrt_marshallOut(theta));
  }
  if (skipDirtyCheck || (alpha_dirty != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"alpha", emlrt_marshallOut(alpha));
  }
  if (skipDirtyCheck || (lambda_dirty != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"lambda", emlrt_marshallOut(lambda));
  }
  if (skipDirtyCheck || (gamma1_dirty != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"gamma1", emlrt_marshallOut(gamma1));
  }
  if (skipDirtyCheck || (ksi_dirty != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"ksi", emlrt_marshallOut(ksi));
  }
  if (skipDirtyCheck || (mu_dirty != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"mu", emlrt_marshallOut(mu));
  }
  if (skipDirtyCheck || (H_dirty != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"H", emlrt_marshallOut(H));
  }
  if (skipDirtyCheck || (Omega_dirty != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"Omega", emlrt_marshallOut(Omega));
  }
  if (skipDirtyCheck || (chi_dirty != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"chi", emlrt_marshallOut(chi));
  }
  if (skipDirtyCheck || (trmult_reduced_dirty != 0U)) {
    emlrtPutGlobalVariable((const char_T *)"trmult_reduced",
                           emlrt_marshallOut(trmult_reduced));
  }
}

void emlrt_synchGlobalsFromML(const emlrtStack *sp)
{
  MEXGlobalSyncInFunction(sp);
  theta_dirty = 0U;
  alpha_dirty = 0U;
  lambda_dirty = 0U;
  gamma1_dirty = 0U;
  ksi_dirty = 0U;
  mu_dirty = 0U;
  H_dirty = 0U;
  Omega_dirty = 0U;
  chi_dirty = 0U;
  trmult_reduced_dirty = 0U;
}

void emlrt_synchGlobalsToML(const emlrtStack *)
{
  MEXGlobalSyncOutFunction(false);
}

void migration_costs_api(const mxArray *const prhs[6], const mxArray **plhs)
{
  emlrtStack st{
      nullptr, // site
      nullptr, // tls
      nullptr  // prev
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
  // Marshall function inputs
  m2_i = b_emlrt_marshallIn(&st, emlrtAlias(prhs_copy_idx_0), "m2_i");
  amen = b_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "amen");
  prod = b_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "prod");
  pop = b_emlrt_marshallIn(&st, emlrtAlias(prhs[3]), "pop");
  price_energy = b_emlrt_marshallIn(&st, emlrtAlias(prhs[4]), "price_energy");
  tol_m2 = emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "tol_m2");
  // Marshall in global variables
  MEXGlobalSyncInFunction(&st);
  // Invoke the target function
  migration_costs(&st, *m2_i, *amen, *prod, *pop, *price_energy, tol_m2, *m2_f);
  // Marshall out global variables
  MEXGlobalSyncOutFunction(true);
  // Marshall function outputs
  *plhs = b_emlrt_marshallOut(*m2_f);
}

// End of code generation (_coder_migration_costs_api.cpp)
