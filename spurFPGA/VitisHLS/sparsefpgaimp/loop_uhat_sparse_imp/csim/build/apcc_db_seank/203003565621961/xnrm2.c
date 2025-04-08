/* Provide Declarations */
#include <stdarg.h>
#include <setjmp.h>
#include <limits.h>
#ifdef NEED_CBEAPINT
#include <autopilot_cbe.h>
#else
#define aesl_fopen fopen
#define aesl_freopen freopen
#define aesl_tmpfile tmpfile
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifdef __STRICT_ANSI__
#define inline __inline__
#define typeof __typeof__ 
#endif
#define __isoc99_fscanf fscanf
#define __isoc99_sscanf sscanf
#undef ferror
#undef feof
/* get a declaration for alloca */
#if defined(__CYGWIN__) || defined(__MINGW32__)
#define  alloca(x) __builtin_alloca((x))
#define _alloca(x) __builtin_alloca((x))
#elif defined(__APPLE__)
extern void *__builtin_alloca(unsigned long);
#define alloca(x) __builtin_alloca(x)
#define longjmp _longjmp
#define setjmp _setjmp
#elif defined(__sun__)
#if defined(__sparcv9)
extern void *__builtin_alloca(unsigned long);
#else
extern void *__builtin_alloca(unsigned int);
#endif
#define alloca(x) __builtin_alloca(x)
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__) || defined(__arm__)
#define alloca(x) __builtin_alloca(x)
#elif defined(_MSC_VER)
#define inline _inline
#define alloca(x) _alloca(x)
#else
#include <alloca.h>
#endif

#ifndef __GNUC__  /* Can only support "linkonce" vars with GCC */
#define __attribute__(X)
#endif

#if defined(__GNUC__) && defined(__APPLE_CC__)
#define __EXTERNAL_WEAK__ __attribute__((weak_import))
#elif defined(__GNUC__)
#define __EXTERNAL_WEAK__ __attribute__((weak))
#else
#define __EXTERNAL_WEAK__
#endif

#if defined(__GNUC__) && (defined(__APPLE_CC__) || defined(__CYGWIN__) || defined(__MINGW32__))
#define __ATTRIBUTE_WEAK__
#elif defined(__GNUC__)
#define __ATTRIBUTE_WEAK__ __attribute__((weak))
#else
#define __ATTRIBUTE_WEAK__
#endif

#if defined(__GNUC__)
#define __HIDDEN__ __attribute__((visibility("hidden")))
#endif

#ifdef __GNUC__
#define LLVM_NAN(NanStr)   __builtin_nan(NanStr)   /* Double */
#define LLVM_NANF(NanStr)  __builtin_nanf(NanStr)  /* Float */
#define LLVM_NANS(NanStr)  __builtin_nans(NanStr)  /* Double */
#define LLVM_NANSF(NanStr) __builtin_nansf(NanStr) /* Float */
#define LLVM_INF           __builtin_inf()         /* Double */
#define LLVM_INFF          __builtin_inff()        /* Float */
#define LLVM_PREFETCH(addr,rw,locality) __builtin_prefetch(addr,rw,locality)
#define __ATTRIBUTE_CTOR__ __attribute__((constructor))
#define __ATTRIBUTE_DTOR__ __attribute__((destructor))
#define LLVM_ASM           __asm__
#else
#define LLVM_NAN(NanStr)   ((double)0.0)           /* Double */
#define LLVM_NANF(NanStr)  0.0F                    /* Float */
#define LLVM_NANS(NanStr)  ((double)0.0)           /* Double */
#define LLVM_NANSF(NanStr) 0.0F                    /* Float */
#define LLVM_INF           ((double)0.0)           /* Double */
#define LLVM_INFF          0.0F                    /* Float */
#define LLVM_PREFETCH(addr,rw,locality)            /* PREFETCH */
#define __ATTRIBUTE_CTOR__
#define __ATTRIBUTE_DTOR__
#define LLVM_ASM(X)
#endif

#if __GNUC__ < 4 /* Old GCC's, or compilers not GCC */ 
#define __builtin_stack_save() 0   /* not implemented */
#define __builtin_stack_restore(X) /* noop */
#endif

#if __GNUC__ && __LP64__ /* 128-bit integer types */
typedef int __attribute__((mode(TI))) llvmInt128;
typedef unsigned __attribute__((mode(TI))) llvmUInt128;
#endif

#define CODE_FOR_MAIN() /* Any target-specific code for main()*/

#ifndef __cplusplus
typedef unsigned char bool;
#endif


/* Support for floating point constants */
typedef unsigned long long ConstantDoubleTy;
typedef unsigned int        ConstantFloatTy;
typedef struct { unsigned long long f1; unsigned short f2; unsigned short pad[3]; } ConstantFP80Ty;
typedef struct { unsigned long long f1; unsigned long long f2; } ConstantFP128Ty;


/* Global Declarations */
/* Helper union for bitcasts */
typedef union {
  unsigned int Int32;
  unsigned long long Int64;
  float Float;
  double Double;
} llvmBitCastUnion;

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
double b_xnrm2(signed int llvm_cbe_n, double *llvm_cbe_x, signed int llvm_cbe_ix0);
double xnrm2(signed int llvm_cbe_n, double *llvm_cbe_x, signed int llvm_cbe_ix0);


/* Function Bodies */
static inline int llvm_fcmp_ord(double X, double Y) { return X == X && Y == Y; }
static inline int llvm_fcmp_uno(double X, double Y) { return X != X || Y != Y; }
static inline int llvm_fcmp_ueq(double X, double Y) { return X == Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_une(double X, double Y) { return X != Y; }
static inline int llvm_fcmp_ult(double X, double Y) { return X <  Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_ugt(double X, double Y) { return X >  Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_ule(double X, double Y) { return X <= Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_uge(double X, double Y) { return X >= Y || llvm_fcmp_uno(X, Y); }
static inline int llvm_fcmp_oeq(double X, double Y) { return X == Y ; }
static inline int llvm_fcmp_one(double X, double Y) { return X != Y && llvm_fcmp_ord(X, Y); }
static inline int llvm_fcmp_olt(double X, double Y) { return X <  Y ; }
static inline int llvm_fcmp_ogt(double X, double Y) { return X >  Y ; }
static inline int llvm_fcmp_ole(double X, double Y) { return X <= Y ; }
static inline int llvm_fcmp_oge(double X, double Y) { return X >= Y ; }

double b_xnrm2(signed int llvm_cbe_n, double *llvm_cbe_x, signed int llvm_cbe_ix0) {
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;
  static  unsigned long long aesl_llvm_cbe_5_count = 0;
  static  unsigned long long aesl_llvm_cbe_6_count = 0;
  static  unsigned long long aesl_llvm_cbe_7_count = 0;
  static  unsigned long long aesl_llvm_cbe_8_count = 0;
  static  unsigned long long aesl_llvm_cbe_9_count = 0;
  static  unsigned long long aesl_llvm_cbe_10_count = 0;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  unsigned int llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  unsigned int llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge2_count = 0;
  unsigned int llvm_cbe_storemerge2;
  unsigned int llvm_cbe_storemerge2__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  double llvm_cbe_tmp__3;
  double llvm_cbe_tmp__3__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  double llvm_cbe_tmp__4;
  double llvm_cbe_tmp__4__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  unsigned int llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  unsigned long long llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  double *llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  double llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  double llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  double llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  double llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  double llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  double llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  double llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  double llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  double llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  double llvm_cbe_tmp__17;
  double llvm_cbe_tmp__17__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  double llvm_cbe_tmp__18;
  double llvm_cbe_tmp__18__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  unsigned int llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa1_count = 0;
  double llvm_cbe__2e_lcssa1;
  double llvm_cbe__2e_lcssa1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa_count = 0;
  double llvm_cbe__2e_lcssa;
  double llvm_cbe__2e_lcssa__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  double llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  double llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @b_xnrm2\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = add i32 %%n, -1, !dbg !6 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_16_count);
  llvm_cbe_tmp__1 = (unsigned int )((unsigned int )(llvm_cbe_n&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__1&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = add i32 %%1, %%ix0, !dbg !6 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_17_count);
  llvm_cbe_tmp__2 = (unsigned int )((unsigned int )(llvm_cbe_tmp__1&4294967295ull)) + ((unsigned int )(llvm_cbe_ix0&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__2&4294967295ull)));
  if ((((signed int )llvm_cbe_tmp__2) < ((signed int )llvm_cbe_ix0))) {
    llvm_cbe__2e_lcssa1__PHI_TEMPORARY = (double )0x1p-563;   /* for PHI node */
    llvm_cbe__2e_lcssa__PHI_TEMPORARY = (double )0x0p0;   /* for PHI node */
    goto llvm_cbe__2e__crit_edge;
  } else {
    llvm_cbe_storemerge2__PHI_TEMPORARY = (unsigned int )llvm_cbe_ix0;   /* for PHI node */
    llvm_cbe_tmp__3__PHI_TEMPORARY = (double )0x1p-563;   /* for PHI node */
    llvm_cbe_tmp__4__PHI_TEMPORARY = (double )0x0p0;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  }

  do {     /* Syntactic loop '.lr.ph' to make GCC happy */
llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge2 = phi i32 [ %%24, %%21 ], [ %%ix0, %%0  for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_storemerge2_count);
  llvm_cbe_storemerge2 = (unsigned int )llvm_cbe_storemerge2__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge2 = 0x%X",llvm_cbe_storemerge2);
printf("\n = 0x%X",llvm_cbe_tmp__19);
printf("\nix0 = 0x%X",llvm_cbe_ix0);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = phi double [ %%23, %%21 ], [ 0x1CC0000000000000, %%0  for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_27_count);
  llvm_cbe_tmp__3 = (double )llvm_cbe_tmp__3__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %lf",llvm_cbe_tmp__3);
printf("\n = %lf",llvm_cbe_tmp__18);
printf("\n = %lf",0x1p-563);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = phi double [ %%22, %%21 ], [ 0.000000e+00, %%0  for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_28_count);
  llvm_cbe_tmp__4 = (double )llvm_cbe_tmp__4__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %lf",llvm_cbe_tmp__4);
printf("\n = %lf",llvm_cbe_tmp__17);
printf("\n = %lf",0x0p0);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = add nsw i32 %%storemerge2, -1, !dbg !3 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_29_count);
  llvm_cbe_tmp__5 = (unsigned int )((unsigned int )(llvm_cbe_storemerge2&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__5&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = sext i32 %%6 to i64, !dbg !3 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_30_count);
  llvm_cbe_tmp__6 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__5);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds double* %%x, i64 %%7, !dbg !3 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_31_count);
  llvm_cbe_tmp__7 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__6))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__6));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load double* %%8, align 8, !dbg !3 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_32_count);
  llvm_cbe_tmp__8 = (double )*llvm_cbe_tmp__7;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__8, *(long long*)(&llvm_cbe_tmp__8));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = tail call double @fabs(double %%9) nounwind, !dbg !3 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_33_count);
  llvm_cbe_tmp__9 = (double ) /*tail*/ fabs(llvm_cbe_tmp__8);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__8, *(long long*)(&llvm_cbe_tmp__8));
printf("\nReturn  = %lf",llvm_cbe_tmp__9);
}
  if ((llvm_fcmp_ogt(llvm_cbe_tmp__9, llvm_cbe_tmp__3))) {
    goto llvm_cbe_tmp__22;
  } else {
    goto llvm_cbe_tmp__23;
  }

llvm_cbe_tmp__24:
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = phi double [ %%16, %%12 ], [ %%20, %%17  for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_69_count);
  llvm_cbe_tmp__17 = (double )llvm_cbe_tmp__17__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %lf",llvm_cbe_tmp__17);
printf("\n = %lf",llvm_cbe_tmp__13);
printf("\n = %lf",llvm_cbe_tmp__16);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = phi double [ %%10, %%12 ], [ %%4, %%17  for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_70_count);
  llvm_cbe_tmp__18 = (double )llvm_cbe_tmp__18__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %lf",llvm_cbe_tmp__18);
printf("\n = %lf",llvm_cbe_tmp__9);
printf("\n = %lf",llvm_cbe_tmp__3);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = add nsw i32 %%storemerge2, 1, !dbg !6 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_71_count);
  llvm_cbe_tmp__19 = (unsigned int )((unsigned int )(llvm_cbe_storemerge2&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__19&4294967295ull)));
  if ((((signed int )llvm_cbe_tmp__19) > ((signed int )llvm_cbe_tmp__2))) {
    llvm_cbe__2e_lcssa1__PHI_TEMPORARY = (double )llvm_cbe_tmp__18;   /* for PHI node */
    llvm_cbe__2e_lcssa__PHI_TEMPORARY = (double )llvm_cbe_tmp__17;   /* for PHI node */
    goto llvm_cbe__2e__crit_edge;
  } else {
    llvm_cbe_storemerge2__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__19;   /* for PHI node */
    llvm_cbe_tmp__3__PHI_TEMPORARY = (double )llvm_cbe_tmp__18;   /* for PHI node */
    llvm_cbe_tmp__4__PHI_TEMPORARY = (double )llvm_cbe_tmp__17;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  }

llvm_cbe_tmp__22:
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = fdiv double %%4, %%10, !dbg !5 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_41_count);
  llvm_cbe_tmp__10 = (double )llvm_cbe_tmp__3 / llvm_cbe_tmp__9;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__10, *(long long*)(&llvm_cbe_tmp__10));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = fmul double %%5, %%13, !dbg !4 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_44_count);
  llvm_cbe_tmp__11 = (double )llvm_cbe_tmp__4 * llvm_cbe_tmp__10;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__11, *(long long*)(&llvm_cbe_tmp__11));
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = fmul double %%14, %%13, !dbg !4 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_46_count);
  llvm_cbe_tmp__12 = (double )llvm_cbe_tmp__11 * llvm_cbe_tmp__10;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__12, *(long long*)(&llvm_cbe_tmp__12));
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = fadd double %%15, 1.000000e+00, !dbg !4 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_47_count);
  llvm_cbe_tmp__13 = (double )llvm_cbe_tmp__12 + 0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__13, *(long long*)(&llvm_cbe_tmp__13));
  llvm_cbe_tmp__17__PHI_TEMPORARY = (double )llvm_cbe_tmp__13;   /* for PHI node */
  llvm_cbe_tmp__18__PHI_TEMPORARY = (double )llvm_cbe_tmp__9;   /* for PHI node */
  goto llvm_cbe_tmp__24;

llvm_cbe_tmp__23:
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = fdiv double %%10, %%4, !dbg !5 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_58_count);
  llvm_cbe_tmp__14 = (double )llvm_cbe_tmp__9 / llvm_cbe_tmp__3;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__14, *(long long*)(&llvm_cbe_tmp__14));
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = fmul double %%18, %%18, !dbg !4 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_62_count);
  llvm_cbe_tmp__15 = (double )llvm_cbe_tmp__14 * llvm_cbe_tmp__14;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__15, *(long long*)(&llvm_cbe_tmp__15));
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = fadd double %%5, %%19, !dbg !4 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_63_count);
  llvm_cbe_tmp__16 = (double )llvm_cbe_tmp__4 + llvm_cbe_tmp__15;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__16, *(long long*)(&llvm_cbe_tmp__16));
  llvm_cbe_tmp__17__PHI_TEMPORARY = (double )llvm_cbe_tmp__16;   /* for PHI node */
  llvm_cbe_tmp__18__PHI_TEMPORARY = (double )llvm_cbe_tmp__3;   /* for PHI node */
  goto llvm_cbe_tmp__24;

  } while (1); /* end of syntactic loop '.lr.ph' */
llvm_cbe__2e__crit_edge:
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa1 = phi double [ 0x1CC0000000000000, %%0 ], [ %%23, %%21  for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe__2e_lcssa1_count);
  llvm_cbe__2e_lcssa1 = (double )llvm_cbe__2e_lcssa1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa1 = %lf",llvm_cbe__2e_lcssa1);
printf("\n = %lf",0x1p-563);
printf("\n = %lf",llvm_cbe_tmp__18);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa = phi double [ 0.000000e+00, %%0 ], [ %%22, %%21  for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe__2e_lcssa_count);
  llvm_cbe__2e_lcssa = (double )llvm_cbe__2e_lcssa__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa = %lf",llvm_cbe__2e_lcssa);
printf("\n = %lf",0x0p0);
printf("\n = %lf",llvm_cbe_tmp__17);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = tail call double @sqrt(double %%.lcssa) nounwind readnone, !dbg !5 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_78_count);
  llvm_cbe_tmp__20 = (double ) /*tail*/ sqrt(llvm_cbe__2e_lcssa);
if (AESL_DEBUG_TRACE) {
printf("\nArgument .lcssa = %lf,  0x%llx",llvm_cbe__2e_lcssa, *(long long*)(&llvm_cbe__2e_lcssa));
printf("\nReturn  = %lf",llvm_cbe_tmp__20);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = fmul double %%.lcssa1, %%26, !dbg !5 for 0x%I64xth hint within @b_xnrm2  --> \n", ++aesl_llvm_cbe_79_count);
  llvm_cbe_tmp__21 = (double )llvm_cbe__2e_lcssa1 * llvm_cbe_tmp__20;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__21, *(long long*)(&llvm_cbe_tmp__21));
  if (AESL_DEBUG_TRACE)
      printf("\nEND @b_xnrm2}\n");
  return llvm_cbe_tmp__21;
}


double xnrm2(signed int llvm_cbe_n, double *llvm_cbe_x, signed int llvm_cbe_ix0) {
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  unsigned int llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  unsigned int llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge2_count = 0;
  unsigned int llvm_cbe_storemerge2;
  unsigned int llvm_cbe_storemerge2__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  double llvm_cbe_tmp__27;
  double llvm_cbe_tmp__27__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  double llvm_cbe_tmp__28;
  double llvm_cbe_tmp__28__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  unsigned int llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  unsigned long long llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  double *llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  double llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  double llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  double llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  double llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  double llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  double llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  double llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  double llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  double llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  double llvm_cbe_tmp__41;
  double llvm_cbe_tmp__41__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  double llvm_cbe_tmp__42;
  double llvm_cbe_tmp__42__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  unsigned int llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa1_count = 0;
  double llvm_cbe__2e_lcssa1;
  double llvm_cbe__2e_lcssa1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe__2e_lcssa_count = 0;
  double llvm_cbe__2e_lcssa;
  double llvm_cbe__2e_lcssa__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  double llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  double llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @xnrm2\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = add i32 %%n, -1, !dbg !6 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_96_count);
  llvm_cbe_tmp__25 = (unsigned int )((unsigned int )(llvm_cbe_n&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__25&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = add i32 %%1, %%ix0, !dbg !6 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_97_count);
  llvm_cbe_tmp__26 = (unsigned int )((unsigned int )(llvm_cbe_tmp__25&4294967295ull)) + ((unsigned int )(llvm_cbe_ix0&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__26&4294967295ull)));
  if ((((signed int )llvm_cbe_tmp__26) < ((signed int )llvm_cbe_ix0))) {
    llvm_cbe__2e_lcssa1__PHI_TEMPORARY = (double )0x1p-563;   /* for PHI node */
    llvm_cbe__2e_lcssa__PHI_TEMPORARY = (double )0x0p0;   /* for PHI node */
    goto llvm_cbe__2e__crit_edge;
  } else {
    llvm_cbe_storemerge2__PHI_TEMPORARY = (unsigned int )llvm_cbe_ix0;   /* for PHI node */
    llvm_cbe_tmp__27__PHI_TEMPORARY = (double )0x1p-563;   /* for PHI node */
    llvm_cbe_tmp__28__PHI_TEMPORARY = (double )0x0p0;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  }

  do {     /* Syntactic loop '.lr.ph' to make GCC happy */
llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge2 = phi i32 [ %%24, %%21 ], [ %%ix0, %%0  for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_storemerge2_count);
  llvm_cbe_storemerge2 = (unsigned int )llvm_cbe_storemerge2__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge2 = 0x%X",llvm_cbe_storemerge2);
printf("\n = 0x%X",llvm_cbe_tmp__43);
printf("\nix0 = 0x%X",llvm_cbe_ix0);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = phi double [ %%23, %%21 ], [ 0x1CC0000000000000, %%0  for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_107_count);
  llvm_cbe_tmp__27 = (double )llvm_cbe_tmp__27__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %lf",llvm_cbe_tmp__27);
printf("\n = %lf",llvm_cbe_tmp__42);
printf("\n = %lf",0x1p-563);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = phi double [ %%22, %%21 ], [ 0.000000e+00, %%0  for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_108_count);
  llvm_cbe_tmp__28 = (double )llvm_cbe_tmp__28__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %lf",llvm_cbe_tmp__28);
printf("\n = %lf",llvm_cbe_tmp__41);
printf("\n = %lf",0x0p0);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = add nsw i32 %%storemerge2, -1, !dbg !3 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_109_count);
  llvm_cbe_tmp__29 = (unsigned int )((unsigned int )(llvm_cbe_storemerge2&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__29&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = sext i32 %%6 to i64, !dbg !3 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_110_count);
  llvm_cbe_tmp__30 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__29);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__30);
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = getelementptr inbounds double* %%x, i64 %%7, !dbg !3 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_111_count);
  llvm_cbe_tmp__31 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__30))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__30));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = load double* %%8, align 8, !dbg !3 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_112_count);
  llvm_cbe_tmp__32 = (double )*llvm_cbe_tmp__31;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__32, *(long long*)(&llvm_cbe_tmp__32));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = tail call double @fabs(double %%9) nounwind, !dbg !3 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_113_count);
  llvm_cbe_tmp__33 = (double ) /*tail*/ fabs(llvm_cbe_tmp__32);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__32, *(long long*)(&llvm_cbe_tmp__32));
printf("\nReturn  = %lf",llvm_cbe_tmp__33);
}
  if ((llvm_fcmp_ogt(llvm_cbe_tmp__33, llvm_cbe_tmp__27))) {
    goto llvm_cbe_tmp__46;
  } else {
    goto llvm_cbe_tmp__47;
  }

llvm_cbe_tmp__48:
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = phi double [ %%16, %%12 ], [ %%20, %%17  for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_149_count);
  llvm_cbe_tmp__41 = (double )llvm_cbe_tmp__41__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %lf",llvm_cbe_tmp__41);
printf("\n = %lf",llvm_cbe_tmp__37);
printf("\n = %lf",llvm_cbe_tmp__40);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = phi double [ %%10, %%12 ], [ %%4, %%17  for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_150_count);
  llvm_cbe_tmp__42 = (double )llvm_cbe_tmp__42__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %lf",llvm_cbe_tmp__42);
printf("\n = %lf",llvm_cbe_tmp__33);
printf("\n = %lf",llvm_cbe_tmp__27);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = add nsw i32 %%storemerge2, 1, !dbg !6 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_151_count);
  llvm_cbe_tmp__43 = (unsigned int )((unsigned int )(llvm_cbe_storemerge2&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__43&4294967295ull)));
  if ((((signed int )llvm_cbe_tmp__43) > ((signed int )llvm_cbe_tmp__26))) {
    llvm_cbe__2e_lcssa1__PHI_TEMPORARY = (double )llvm_cbe_tmp__42;   /* for PHI node */
    llvm_cbe__2e_lcssa__PHI_TEMPORARY = (double )llvm_cbe_tmp__41;   /* for PHI node */
    goto llvm_cbe__2e__crit_edge;
  } else {
    llvm_cbe_storemerge2__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__43;   /* for PHI node */
    llvm_cbe_tmp__27__PHI_TEMPORARY = (double )llvm_cbe_tmp__42;   /* for PHI node */
    llvm_cbe_tmp__28__PHI_TEMPORARY = (double )llvm_cbe_tmp__41;   /* for PHI node */
    goto llvm_cbe__2e_lr_2e_ph;
  }

llvm_cbe_tmp__46:
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = fdiv double %%4, %%10, !dbg !5 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_121_count);
  llvm_cbe_tmp__34 = (double )llvm_cbe_tmp__27 / llvm_cbe_tmp__33;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__34, *(long long*)(&llvm_cbe_tmp__34));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = fmul double %%5, %%13, !dbg !4 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_124_count);
  llvm_cbe_tmp__35 = (double )llvm_cbe_tmp__28 * llvm_cbe_tmp__34;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__35, *(long long*)(&llvm_cbe_tmp__35));
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = fmul double %%14, %%13, !dbg !4 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_126_count);
  llvm_cbe_tmp__36 = (double )llvm_cbe_tmp__35 * llvm_cbe_tmp__34;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__36, *(long long*)(&llvm_cbe_tmp__36));
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = fadd double %%15, 1.000000e+00, !dbg !4 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_127_count);
  llvm_cbe_tmp__37 = (double )llvm_cbe_tmp__36 + 0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__37, *(long long*)(&llvm_cbe_tmp__37));
  llvm_cbe_tmp__41__PHI_TEMPORARY = (double )llvm_cbe_tmp__37;   /* for PHI node */
  llvm_cbe_tmp__42__PHI_TEMPORARY = (double )llvm_cbe_tmp__33;   /* for PHI node */
  goto llvm_cbe_tmp__48;

llvm_cbe_tmp__47:
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = fdiv double %%10, %%4, !dbg !5 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_138_count);
  llvm_cbe_tmp__38 = (double )llvm_cbe_tmp__33 / llvm_cbe_tmp__27;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__38, *(long long*)(&llvm_cbe_tmp__38));
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = fmul double %%18, %%18, !dbg !4 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_142_count);
  llvm_cbe_tmp__39 = (double )llvm_cbe_tmp__38 * llvm_cbe_tmp__38;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__39, *(long long*)(&llvm_cbe_tmp__39));
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = fadd double %%5, %%19, !dbg !4 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_143_count);
  llvm_cbe_tmp__40 = (double )llvm_cbe_tmp__28 + llvm_cbe_tmp__39;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__40, *(long long*)(&llvm_cbe_tmp__40));
  llvm_cbe_tmp__41__PHI_TEMPORARY = (double )llvm_cbe_tmp__40;   /* for PHI node */
  llvm_cbe_tmp__42__PHI_TEMPORARY = (double )llvm_cbe_tmp__27;   /* for PHI node */
  goto llvm_cbe_tmp__48;

  } while (1); /* end of syntactic loop '.lr.ph' */
llvm_cbe__2e__crit_edge:
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa1 = phi double [ 0x1CC0000000000000, %%0 ], [ %%23, %%21  for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe__2e_lcssa1_count);
  llvm_cbe__2e_lcssa1 = (double )llvm_cbe__2e_lcssa1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa1 = %lf",llvm_cbe__2e_lcssa1);
printf("\n = %lf",0x1p-563);
printf("\n = %lf",llvm_cbe_tmp__42);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%.lcssa = phi double [ 0.000000e+00, %%0 ], [ %%22, %%21  for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe__2e_lcssa_count);
  llvm_cbe__2e_lcssa = (double )llvm_cbe__2e_lcssa__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n.lcssa = %lf",llvm_cbe__2e_lcssa);
printf("\n = %lf",0x0p0);
printf("\n = %lf",llvm_cbe_tmp__41);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = tail call double @sqrt(double %%.lcssa) nounwind readnone, !dbg !5 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_158_count);
  llvm_cbe_tmp__44 = (double ) /*tail*/ sqrt(llvm_cbe__2e_lcssa);
if (AESL_DEBUG_TRACE) {
printf("\nArgument .lcssa = %lf,  0x%llx",llvm_cbe__2e_lcssa, *(long long*)(&llvm_cbe__2e_lcssa));
printf("\nReturn  = %lf",llvm_cbe_tmp__44);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = fmul double %%.lcssa1, %%26, !dbg !5 for 0x%I64xth hint within @xnrm2  --> \n", ++aesl_llvm_cbe_159_count);
  llvm_cbe_tmp__45 = (double )llvm_cbe__2e_lcssa1 * llvm_cbe_tmp__44;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__45, *(long long*)(&llvm_cbe_tmp__45));
  if (AESL_DEBUG_TRACE)
      printf("\nEND @xnrm2}\n");
  return llvm_cbe_tmp__45;
}

