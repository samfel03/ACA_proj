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
void b_xaxpy(signed int llvm_cbe_n, double llvm_cbe_a, double *llvm_cbe_x, signed int llvm_cbe_ix0, double *llvm_cbe_y, signed int llvm_cbe_iy0);
void c_xaxpy(signed int llvm_cbe_n, double llvm_cbe_a, double *llvm_cbe_x, signed int llvm_cbe_ix0, double *llvm_cbe_y, signed int llvm_cbe_iy0);
void xaxpy(signed int llvm_cbe_n, double llvm_cbe_a, signed int llvm_cbe_ix0, double *llvm_cbe_y, signed int llvm_cbe_iy0);


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

void b_xaxpy(signed int llvm_cbe_n, double llvm_cbe_a, double *llvm_cbe_x, signed int llvm_cbe_ix0, double *llvm_cbe_y, signed int llvm_cbe_iy0) {
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
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  unsigned int llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  unsigned int llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge1_count = 0;
  unsigned int llvm_cbe_storemerge1;
  unsigned int llvm_cbe_storemerge1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  unsigned int llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  unsigned int llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  unsigned long long llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  double *llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  double llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  double llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  unsigned long long llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  double *llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  double llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  double llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  unsigned int llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @b_xaxpy\n");
  if ((llvm_fcmp_oeq(llvm_cbe_a, 0x0p0))) {
    goto llvm_cbe_tmp__15;
  } else {
    goto llvm_cbe_tmp__16;
  }

llvm_cbe_tmp__16:
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = add nsw i32 %%n, -1, !dbg !4 for 0x%I64xth hint within @b_xaxpy  --> \n", ++aesl_llvm_cbe_16_count);
  llvm_cbe_tmp__1 = (unsigned int )((unsigned int )(llvm_cbe_n&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__1&4294967295ull)));
  if ((((signed int )llvm_cbe_tmp__1) < ((signed int )0u))) {
    goto llvm_cbe__2e_loopexit;
  } else {
    goto llvm_cbe__2e_lr_2e_ph;
  }

llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = add i32 %%iy0, -1, !dbg !6 for 0x%I64xth hint within @b_xaxpy  --> \n", ++aesl_llvm_cbe_26_count);
  llvm_cbe_tmp__2 = (unsigned int )((unsigned int )(llvm_cbe_iy0&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__2&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = add i32 %%ix0, -1, !dbg !5 for 0x%I64xth hint within @b_xaxpy  --> \n", ++aesl_llvm_cbe_27_count);
  llvm_cbe_tmp__3 = (unsigned int )((unsigned int )(llvm_cbe_ix0&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__3&4294967295ull)));
  llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__17;

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__17:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge1 = phi i32 [ 0, %%.lr.ph ], [ %%18, %%7  for 0x%I64xth hint within @b_xaxpy  --> \n", ++aesl_llvm_cbe_storemerge1_count);
  llvm_cbe_storemerge1 = (unsigned int )llvm_cbe_storemerge1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge1 = 0x%X",llvm_cbe_storemerge1);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__14);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = add i32 %%5, %%storemerge1, !dbg !6 for 0x%I64xth hint within @b_xaxpy  --> \n", ++aesl_llvm_cbe_29_count);
  llvm_cbe_tmp__4 = (unsigned int )((unsigned int )(llvm_cbe_tmp__2&4294967295ull)) + ((unsigned int )(llvm_cbe_storemerge1&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__4&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = add i32 %%6, %%storemerge1, !dbg !5 for 0x%I64xth hint within @b_xaxpy  --> \n", ++aesl_llvm_cbe_32_count);
  llvm_cbe_tmp__5 = (unsigned int )((unsigned int )(llvm_cbe_tmp__3&4294967295ull)) + ((unsigned int )(llvm_cbe_storemerge1&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__5&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = sext i32 %%9 to i64, !dbg !5 for 0x%I64xth hint within @b_xaxpy  --> \n", ++aesl_llvm_cbe_33_count);
  llvm_cbe_tmp__6 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__5);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds double* %%x, i64 %%10, !dbg !5 for 0x%I64xth hint within @b_xaxpy  --> \n", ++aesl_llvm_cbe_34_count);
  llvm_cbe_tmp__7 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__6))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__6));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = load double* %%11, align 8, !dbg !5 for 0x%I64xth hint within @b_xaxpy  --> \n", ++aesl_llvm_cbe_35_count);
  llvm_cbe_tmp__8 = (double )*llvm_cbe_tmp__7;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__8, *(long long*)(&llvm_cbe_tmp__8));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = fmul double %%12, %%a, !dbg !5 for 0x%I64xth hint within @b_xaxpy  --> \n", ++aesl_llvm_cbe_36_count);
  llvm_cbe_tmp__9 = (double )llvm_cbe_tmp__8 * llvm_cbe_a;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__9, *(long long*)(&llvm_cbe_tmp__9));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = sext i32 %%8 to i64, !dbg !5 for 0x%I64xth hint within @b_xaxpy  --> \n", ++aesl_llvm_cbe_37_count);
  llvm_cbe_tmp__10 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__10);
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = getelementptr inbounds double* %%y, i64 %%14, !dbg !5 for 0x%I64xth hint within @b_xaxpy  --> \n", ++aesl_llvm_cbe_38_count);
  llvm_cbe_tmp__11 = (double *)(&llvm_cbe_y[(((signed long long )llvm_cbe_tmp__10))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__10));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = load double* %%15, align 8, !dbg !5 for 0x%I64xth hint within @b_xaxpy  --> \n", ++aesl_llvm_cbe_39_count);
  llvm_cbe_tmp__12 = (double )*llvm_cbe_tmp__11;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__12, *(long long*)(&llvm_cbe_tmp__12));
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = fadd double %%16, %%13, !dbg !5 for 0x%I64xth hint within @b_xaxpy  --> \n", ++aesl_llvm_cbe_40_count);
  llvm_cbe_tmp__13 = (double )llvm_cbe_tmp__12 + llvm_cbe_tmp__9;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__13, *(long long*)(&llvm_cbe_tmp__13));
if (AESL_DEBUG_TRACE)
printf("\n  store double %%17, double* %%15, align 8, !dbg !5 for 0x%I64xth hint within @b_xaxpy  --> \n", ++aesl_llvm_cbe_41_count);
  *llvm_cbe_tmp__11 = llvm_cbe_tmp__13;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__13);
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = add nsw i32 %%storemerge1, 1, !dbg !6 for 0x%I64xth hint within @b_xaxpy  --> \n", ++aesl_llvm_cbe_42_count);
  llvm_cbe_tmp__14 = (unsigned int )((unsigned int )(llvm_cbe_storemerge1&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__14&4294967295ull)));
  if (((llvm_cbe_tmp__14&4294967295U) == (llvm_cbe_n&4294967295U))) {
    goto llvm_cbe__2e_loopexit;
  } else {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__14;   /* for PHI node */
    goto llvm_cbe_tmp__17;
  }

  } while (1); /* end of syntactic loop '' */
llvm_cbe__2e_loopexit:
  goto llvm_cbe_tmp__15;

llvm_cbe_tmp__15:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @b_xaxpy}\n");
  return;
}


void c_xaxpy(signed int llvm_cbe_n, double llvm_cbe_a, double *llvm_cbe_x, signed int llvm_cbe_ix0, double *llvm_cbe_y, signed int llvm_cbe_iy0) {
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  unsigned int llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  unsigned int llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  unsigned int llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge1_count = 0;
  unsigned int llvm_cbe_storemerge1;
  unsigned int llvm_cbe_storemerge1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  unsigned int llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  unsigned int llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  unsigned long long llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  double *llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  double llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  double llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  unsigned long long llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  double *llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  double llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  double llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  unsigned int llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @c_xaxpy\n");
  if ((llvm_fcmp_oeq(llvm_cbe_a, 0x0p0))) {
    goto llvm_cbe_tmp__32;
  } else {
    goto llvm_cbe_tmp__33;
  }

llvm_cbe_tmp__33:
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = add nsw i32 %%n, -1, !dbg !4 for 0x%I64xth hint within @c_xaxpy  --> \n", ++aesl_llvm_cbe_66_count);
  llvm_cbe_tmp__18 = (unsigned int )((unsigned int )(llvm_cbe_n&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__18&4294967295ull)));
  if ((((signed int )llvm_cbe_tmp__18) < ((signed int )0u))) {
    goto llvm_cbe__2e_loopexit;
  } else {
    goto llvm_cbe__2e_lr_2e_ph;
  }

llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = add i32 %%iy0, -1, !dbg !6 for 0x%I64xth hint within @c_xaxpy  --> \n", ++aesl_llvm_cbe_76_count);
  llvm_cbe_tmp__19 = (unsigned int )((unsigned int )(llvm_cbe_iy0&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__19&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = add i32 %%ix0, -1, !dbg !5 for 0x%I64xth hint within @c_xaxpy  --> \n", ++aesl_llvm_cbe_77_count);
  llvm_cbe_tmp__20 = (unsigned int )((unsigned int )(llvm_cbe_ix0&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__20&4294967295ull)));
  llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__34;

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__34:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge1 = phi i32 [ 0, %%.lr.ph ], [ %%18, %%7  for 0x%I64xth hint within @c_xaxpy  --> \n", ++aesl_llvm_cbe_storemerge1_count);
  llvm_cbe_storemerge1 = (unsigned int )llvm_cbe_storemerge1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge1 = 0x%X",llvm_cbe_storemerge1);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__31);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = add i32 %%5, %%storemerge1, !dbg !6 for 0x%I64xth hint within @c_xaxpy  --> \n", ++aesl_llvm_cbe_79_count);
  llvm_cbe_tmp__21 = (unsigned int )((unsigned int )(llvm_cbe_tmp__19&4294967295ull)) + ((unsigned int )(llvm_cbe_storemerge1&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__21&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = add i32 %%6, %%storemerge1, !dbg !5 for 0x%I64xth hint within @c_xaxpy  --> \n", ++aesl_llvm_cbe_82_count);
  llvm_cbe_tmp__22 = (unsigned int )((unsigned int )(llvm_cbe_tmp__20&4294967295ull)) + ((unsigned int )(llvm_cbe_storemerge1&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__22&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = sext i32 %%9 to i64, !dbg !5 for 0x%I64xth hint within @c_xaxpy  --> \n", ++aesl_llvm_cbe_83_count);
  llvm_cbe_tmp__23 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__22);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__23);
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds double* %%x, i64 %%10, !dbg !5 for 0x%I64xth hint within @c_xaxpy  --> \n", ++aesl_llvm_cbe_84_count);
  llvm_cbe_tmp__24 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__23))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__23));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = load double* %%11, align 8, !dbg !5 for 0x%I64xth hint within @c_xaxpy  --> \n", ++aesl_llvm_cbe_85_count);
  llvm_cbe_tmp__25 = (double )*llvm_cbe_tmp__24;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__25, *(long long*)(&llvm_cbe_tmp__25));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = fmul double %%12, %%a, !dbg !5 for 0x%I64xth hint within @c_xaxpy  --> \n", ++aesl_llvm_cbe_86_count);
  llvm_cbe_tmp__26 = (double )llvm_cbe_tmp__25 * llvm_cbe_a;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__26, *(long long*)(&llvm_cbe_tmp__26));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = sext i32 %%8 to i64, !dbg !5 for 0x%I64xth hint within @c_xaxpy  --> \n", ++aesl_llvm_cbe_87_count);
  llvm_cbe_tmp__27 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__21);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__27);
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = getelementptr inbounds double* %%y, i64 %%14, !dbg !5 for 0x%I64xth hint within @c_xaxpy  --> \n", ++aesl_llvm_cbe_88_count);
  llvm_cbe_tmp__28 = (double *)(&llvm_cbe_y[(((signed long long )llvm_cbe_tmp__27))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__27));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = load double* %%15, align 8, !dbg !5 for 0x%I64xth hint within @c_xaxpy  --> \n", ++aesl_llvm_cbe_89_count);
  llvm_cbe_tmp__29 = (double )*llvm_cbe_tmp__28;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__29, *(long long*)(&llvm_cbe_tmp__29));
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = fadd double %%16, %%13, !dbg !5 for 0x%I64xth hint within @c_xaxpy  --> \n", ++aesl_llvm_cbe_90_count);
  llvm_cbe_tmp__30 = (double )llvm_cbe_tmp__29 + llvm_cbe_tmp__26;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__30, *(long long*)(&llvm_cbe_tmp__30));
if (AESL_DEBUG_TRACE)
printf("\n  store double %%17, double* %%15, align 8, !dbg !5 for 0x%I64xth hint within @c_xaxpy  --> \n", ++aesl_llvm_cbe_91_count);
  *llvm_cbe_tmp__28 = llvm_cbe_tmp__30;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__30);
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = add nsw i32 %%storemerge1, 1, !dbg !6 for 0x%I64xth hint within @c_xaxpy  --> \n", ++aesl_llvm_cbe_92_count);
  llvm_cbe_tmp__31 = (unsigned int )((unsigned int )(llvm_cbe_storemerge1&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__31&4294967295ull)));
  if (((llvm_cbe_tmp__31&4294967295U) == (llvm_cbe_n&4294967295U))) {
    goto llvm_cbe__2e_loopexit;
  } else {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__31;   /* for PHI node */
    goto llvm_cbe_tmp__34;
  }

  } while (1); /* end of syntactic loop '' */
llvm_cbe__2e_loopexit:
  goto llvm_cbe_tmp__32;

llvm_cbe_tmp__32:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @c_xaxpy}\n");
  return;
}


void xaxpy(signed int llvm_cbe_n, double llvm_cbe_a, signed int llvm_cbe_ix0, double *llvm_cbe_y, signed int llvm_cbe_iy0) {
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  unsigned int llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  unsigned int llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  unsigned int llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge1_count = 0;
  unsigned int llvm_cbe_storemerge1;
  unsigned int llvm_cbe_storemerge1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  unsigned int llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  unsigned int llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  unsigned long long llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  double *llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  double llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  double llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  unsigned long long llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  double *llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  double llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  double llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  unsigned int llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  static  unsigned long long aesl_llvm_cbe_exitcond_count = 0;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @xaxpy\n");
  if ((llvm_fcmp_oeq(llvm_cbe_a, 0x0p0))) {
    goto llvm_cbe_tmp__49;
  } else {
    goto llvm_cbe_tmp__50;
  }

llvm_cbe_tmp__50:
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = add nsw i32 %%n, -1, !dbg !4 for 0x%I64xth hint within @xaxpy  --> \n", ++aesl_llvm_cbe_115_count);
  llvm_cbe_tmp__35 = (unsigned int )((unsigned int )(llvm_cbe_n&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__35&4294967295ull)));
  if ((((signed int )llvm_cbe_tmp__35) < ((signed int )0u))) {
    goto llvm_cbe__2e_loopexit;
  } else {
    goto llvm_cbe__2e_lr_2e_ph;
  }

llvm_cbe__2e_lr_2e_ph:
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = add i32 %%iy0, -1, !dbg !6 for 0x%I64xth hint within @xaxpy  --> \n", ++aesl_llvm_cbe_125_count);
  llvm_cbe_tmp__36 = (unsigned int )((unsigned int )(llvm_cbe_iy0&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__36&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = add i32 %%ix0, -1, !dbg !5 for 0x%I64xth hint within @xaxpy  --> \n", ++aesl_llvm_cbe_126_count);
  llvm_cbe_tmp__37 = (unsigned int )((unsigned int )(llvm_cbe_ix0&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__37&4294967295ull)));
  llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )0u;   /* for PHI node */
  goto llvm_cbe_tmp__51;

  do {     /* Syntactic loop '' to make GCC happy */
llvm_cbe_tmp__51:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge1 = phi i32 [ 0, %%.lr.ph ], [ %%18, %%7  for 0x%I64xth hint within @xaxpy  --> \n", ++aesl_llvm_cbe_storemerge1_count);
  llvm_cbe_storemerge1 = (unsigned int )llvm_cbe_storemerge1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge1 = 0x%X",llvm_cbe_storemerge1);
printf("\n = 0x%X",0u);
printf("\n = 0x%X",llvm_cbe_tmp__48);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = add i32 %%5, %%storemerge1, !dbg !6 for 0x%I64xth hint within @xaxpy  --> \n", ++aesl_llvm_cbe_128_count);
  llvm_cbe_tmp__38 = (unsigned int )((unsigned int )(llvm_cbe_tmp__36&4294967295ull)) + ((unsigned int )(llvm_cbe_storemerge1&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__38&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = add i32 %%6, %%storemerge1, !dbg !5 for 0x%I64xth hint within @xaxpy  --> \n", ++aesl_llvm_cbe_131_count);
  llvm_cbe_tmp__39 = (unsigned int )((unsigned int )(llvm_cbe_tmp__37&4294967295ull)) + ((unsigned int )(llvm_cbe_storemerge1&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__39&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = sext i32 %%9 to i64, !dbg !5 for 0x%I64xth hint within @xaxpy  --> \n", ++aesl_llvm_cbe_132_count);
  llvm_cbe_tmp__40 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__39);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__40);
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = getelementptr inbounds double* %%y, i64 %%10, !dbg !5 for 0x%I64xth hint within @xaxpy  --> \n", ++aesl_llvm_cbe_133_count);
  llvm_cbe_tmp__41 = (double *)(&llvm_cbe_y[(((signed long long )llvm_cbe_tmp__40))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__40));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = load double* %%11, align 8, !dbg !5 for 0x%I64xth hint within @xaxpy  --> \n", ++aesl_llvm_cbe_134_count);
  llvm_cbe_tmp__42 = (double )*llvm_cbe_tmp__41;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__42, *(long long*)(&llvm_cbe_tmp__42));
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = fmul double %%12, %%a, !dbg !5 for 0x%I64xth hint within @xaxpy  --> \n", ++aesl_llvm_cbe_135_count);
  llvm_cbe_tmp__43 = (double )llvm_cbe_tmp__42 * llvm_cbe_a;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__43, *(long long*)(&llvm_cbe_tmp__43));
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = sext i32 %%8 to i64, !dbg !5 for 0x%I64xth hint within @xaxpy  --> \n", ++aesl_llvm_cbe_136_count);
  llvm_cbe_tmp__44 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__38);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__44);
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = getelementptr inbounds double* %%y, i64 %%14, !dbg !5 for 0x%I64xth hint within @xaxpy  --> \n", ++aesl_llvm_cbe_137_count);
  llvm_cbe_tmp__45 = (double *)(&llvm_cbe_y[(((signed long long )llvm_cbe_tmp__44))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__44));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = load double* %%15, align 8, !dbg !5 for 0x%I64xth hint within @xaxpy  --> \n", ++aesl_llvm_cbe_138_count);
  llvm_cbe_tmp__46 = (double )*llvm_cbe_tmp__45;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__46, *(long long*)(&llvm_cbe_tmp__46));
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = fadd double %%16, %%13, !dbg !5 for 0x%I64xth hint within @xaxpy  --> \n", ++aesl_llvm_cbe_139_count);
  llvm_cbe_tmp__47 = (double )llvm_cbe_tmp__46 + llvm_cbe_tmp__43;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__47, *(long long*)(&llvm_cbe_tmp__47));
if (AESL_DEBUG_TRACE)
printf("\n  store double %%17, double* %%15, align 8, !dbg !5 for 0x%I64xth hint within @xaxpy  --> \n", ++aesl_llvm_cbe_140_count);
  *llvm_cbe_tmp__45 = llvm_cbe_tmp__47;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = add nsw i32 %%storemerge1, 1, !dbg !6 for 0x%I64xth hint within @xaxpy  --> \n", ++aesl_llvm_cbe_141_count);
  llvm_cbe_tmp__48 = (unsigned int )((unsigned int )(llvm_cbe_storemerge1&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__48&4294967295ull)));
  if (((llvm_cbe_tmp__48&4294967295U) == (llvm_cbe_n&4294967295U))) {
    goto llvm_cbe__2e_loopexit;
  } else {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (unsigned int )llvm_cbe_tmp__48;   /* for PHI node */
    goto llvm_cbe_tmp__51;
  }

  } while (1); /* end of syntactic loop '' */
llvm_cbe__2e_loopexit:
  goto llvm_cbe_tmp__49;

llvm_cbe_tmp__49:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @xaxpy}\n");
  return;
}

