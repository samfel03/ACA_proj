#include <cstdio>
#include "../common/definitions.h"
// #include "definitions.h"

extern "C"
{
    void runOnfpga(real tol, real *trmult_reduced, real *L, real L_exp,
                   real *uhat_i, real *R, real R_exp);
}
