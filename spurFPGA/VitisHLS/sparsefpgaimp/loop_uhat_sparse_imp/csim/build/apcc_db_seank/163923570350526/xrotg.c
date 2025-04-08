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
void xrotg(double *llvm_cbe_a, double *llvm_cbe_b, double *llvm_cbe_c, double *llvm_cbe_s);


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

void xrotg(double *llvm_cbe_a, double *llvm_cbe_b, double *llvm_cbe_c, double *llvm_cbe_s) {
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
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  double llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  double llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  double llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  double llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  double llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  double llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  double llvm_cbe_tmp__7;
  double llvm_cbe_tmp__7__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  double llvm_cbe_tmp__8;
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
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  double llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  double llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  double llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  double llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  double llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  double llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  double llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  double llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  double llvm_cbe_tmp__17;
  double llvm_cbe_tmp__17__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  double llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  double llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  double llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  double llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  double llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  double llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  static  unsigned long long aesl_llvm_cbe_storemerge1_count = 0;
  double llvm_cbe_storemerge1;
  double llvm_cbe_storemerge1__PHI_TEMPORARY;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @xrotg\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = load double* %%b, align 8, !dbg !4 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_24_count);
  llvm_cbe_tmp__1 = (double )*llvm_cbe_b;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__1, *(long long*)(&llvm_cbe_tmp__1));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = load double* %%a, align 8, !dbg !3 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_27_count);
  llvm_cbe_tmp__2 = (double )*llvm_cbe_a;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__2, *(long long*)(&llvm_cbe_tmp__2));
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = tail call double @fabs(double %%2) nounwind, !dbg !3 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_28_count);
  llvm_cbe_tmp__3 = (double ) /*tail*/ fabs(llvm_cbe_tmp__2);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__2, *(long long*)(&llvm_cbe_tmp__2));
printf("\nReturn  = %lf",llvm_cbe_tmp__3);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = load double* %%b, align 8, !dbg !4 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_34_count);
  llvm_cbe_tmp__4 = (double )*llvm_cbe_b;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__4, *(long long*)(&llvm_cbe_tmp__4));
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = tail call double @fabs(double %%4) nounwind, !dbg !4 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_35_count);
  llvm_cbe_tmp__5 = (double ) /*tail*/ fabs(llvm_cbe_tmp__4);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__4, *(long long*)(&llvm_cbe_tmp__4));
printf("\nReturn  = %lf",llvm_cbe_tmp__5);
}
  if ((llvm_fcmp_ogt(llvm_cbe_tmp__3, llvm_cbe_tmp__5))) {
    goto llvm_cbe_tmp__24;
  } else {
    llvm_cbe_tmp__7__PHI_TEMPORARY = (double )llvm_cbe_tmp__1;   /* for PHI node */
    goto llvm_cbe_tmp__25;
  }

llvm_cbe_tmp__24:
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = load double* %%a, align 8, !dbg !3 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_43_count);
  llvm_cbe_tmp__6 = (double )*llvm_cbe_a;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__6, *(long long*)(&llvm_cbe_tmp__6));
  llvm_cbe_tmp__7__PHI_TEMPORARY = (double )llvm_cbe_tmp__6;   /* for PHI node */
  goto llvm_cbe_tmp__25;

llvm_cbe_tmp__25:
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = phi double [ %%8, %%7 ], [ %%1, %%0  for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_47_count);
  llvm_cbe_tmp__7 = (double )llvm_cbe_tmp__7__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %lf",llvm_cbe_tmp__7);
printf("\n = %lf",llvm_cbe_tmp__6);
printf("\n = %lf",llvm_cbe_tmp__1);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = fadd double %%3, %%5, !dbg !6 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_48_count);
  llvm_cbe_tmp__8 = (double )llvm_cbe_tmp__3 + llvm_cbe_tmp__5;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__8, *(long long*)(&llvm_cbe_tmp__8));
  if ((llvm_fcmp_oeq(llvm_cbe_tmp__8, 0x0p0))) {
    goto llvm_cbe_tmp__26;
  } else {
    goto llvm_cbe_tmp__27;
  }

llvm_cbe_tmp__26:
if (AESL_DEBUG_TRACE)
printf("\n  store double 0.000000e+00, double* %%s, align 8, !dbg !6 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_60_count);
  *llvm_cbe_s = 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", 0x0p0);
if (AESL_DEBUG_TRACE)
printf("\n  store double 1.000000e+00, double* %%c, align 8, !dbg !5 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_61_count);
  *llvm_cbe_c = 0x1p0;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", 0x1p0);
if (AESL_DEBUG_TRACE)
printf("\n  store double 0.000000e+00, double* %%a, align 8, !dbg !3 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_62_count);
  *llvm_cbe_a = 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", 0x0p0);
if (AESL_DEBUG_TRACE)
printf("\n  store double 0.000000e+00, double* %%b, align 8, !dbg !4 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_63_count);
  *llvm_cbe_b = 0x0p0;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", 0x0p0);
  goto llvm_cbe_tmp__28;

llvm_cbe_tmp__27:
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = fdiv double %%3, %%11, !dbg !6 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_65_count);
  llvm_cbe_tmp__9 = (double )llvm_cbe_tmp__3 / llvm_cbe_tmp__8;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__9, *(long long*)(&llvm_cbe_tmp__9));
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = fdiv double %%5, %%11, !dbg !7 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_67_count);
  llvm_cbe_tmp__10 = (double )llvm_cbe_tmp__5 / llvm_cbe_tmp__8;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__10, *(long long*)(&llvm_cbe_tmp__10));
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = fmul double %%15, %%15, !dbg !7 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_71_count);
  llvm_cbe_tmp__11 = (double )llvm_cbe_tmp__9 * llvm_cbe_tmp__9;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__11, *(long long*)(&llvm_cbe_tmp__11));
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = fmul double %%16, %%16, !dbg !7 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_74_count);
  llvm_cbe_tmp__12 = (double )llvm_cbe_tmp__10 * llvm_cbe_tmp__10;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__12, *(long long*)(&llvm_cbe_tmp__12));
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = fadd double %%17, %%18, !dbg !7 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_75_count);
  llvm_cbe_tmp__13 = (double )llvm_cbe_tmp__11 + llvm_cbe_tmp__12;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__13, *(long long*)(&llvm_cbe_tmp__13));
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = tail call double @sqrt(double %%19) nounwind readnone, !dbg !7 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_76_count);
  llvm_cbe_tmp__14 = (double ) /*tail*/ sqrt(llvm_cbe_tmp__13);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__13, *(long long*)(&llvm_cbe_tmp__13));
printf("\nReturn  = %lf",llvm_cbe_tmp__14);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = fmul double %%11, %%20, !dbg !7 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_77_count);
  llvm_cbe_tmp__15 = (double )llvm_cbe_tmp__8 * llvm_cbe_tmp__14;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__15, *(long long*)(&llvm_cbe_tmp__15));
  if ((llvm_fcmp_olt(llvm_cbe_tmp__7, 0x0p0))) {
    goto llvm_cbe_tmp__29;
  } else {
    llvm_cbe_tmp__17__PHI_TEMPORARY = (double )llvm_cbe_tmp__15;   /* for PHI node */
    goto llvm_cbe_tmp__30;
  }

llvm_cbe_tmp__29:
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = fsub double -0.000000e+00, %%21, !dbg !7 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_89_count);
  llvm_cbe_tmp__16 = (double )-(llvm_cbe_tmp__15);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__16, *(long long*)(&llvm_cbe_tmp__16));
  llvm_cbe_tmp__17__PHI_TEMPORARY = (double )llvm_cbe_tmp__16;   /* for PHI node */
  goto llvm_cbe_tmp__30;

llvm_cbe_tmp__30:
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = phi double [ %%24, %%23 ], [ %%21, %%14  for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_100_count);
  llvm_cbe_tmp__17 = (double )llvm_cbe_tmp__17__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\n = %lf",llvm_cbe_tmp__17);
printf("\n = %lf",llvm_cbe_tmp__16);
printf("\n = %lf",llvm_cbe_tmp__15);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = load double* %%a, align 8, !dbg !4 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_101_count);
  llvm_cbe_tmp__18 = (double )*llvm_cbe_a;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__18, *(long long*)(&llvm_cbe_tmp__18));
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = fdiv double %%27, %%26, !dbg !4 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_102_count);
  llvm_cbe_tmp__19 = (double )llvm_cbe_tmp__18 / llvm_cbe_tmp__17;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__19, *(long long*)(&llvm_cbe_tmp__19));
if (AESL_DEBUG_TRACE)
printf("\n  store double %%28, double* %%c, align 8, !dbg !4 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_103_count);
  *llvm_cbe_c = llvm_cbe_tmp__19;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__19);
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = load double* %%b, align 8, !dbg !4 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_104_count);
  llvm_cbe_tmp__20 = (double )*llvm_cbe_b;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__20, *(long long*)(&llvm_cbe_tmp__20));
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = fdiv double %%29, %%26, !dbg !4 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_105_count);
  llvm_cbe_tmp__21 = (double )llvm_cbe_tmp__20 / llvm_cbe_tmp__17;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__21, *(long long*)(&llvm_cbe_tmp__21));
if (AESL_DEBUG_TRACE)
printf("\n  store double %%30, double* %%s, align 8, !dbg !4 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_106_count);
  *llvm_cbe_s = llvm_cbe_tmp__21;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__21);
  if ((llvm_fcmp_ogt(llvm_cbe_tmp__3, llvm_cbe_tmp__5))) {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (double )llvm_cbe_tmp__21;   /* for PHI node */
    goto llvm_cbe_tmp__31;
  } else {
    goto llvm_cbe_tmp__32;
  }

llvm_cbe_tmp__32:
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = load double* %%c, align 8, !dbg !5 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_108_count);
  llvm_cbe_tmp__22 = (double )*llvm_cbe_c;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__22, *(long long*)(&llvm_cbe_tmp__22));
  if ((llvm_fcmp_une(llvm_cbe_tmp__22, 0x0p0))) {
    goto llvm_cbe_tmp__33;
  } else {
    llvm_cbe_storemerge1__PHI_TEMPORARY = (double )0x1p0;   /* for PHI node */
    goto llvm_cbe_tmp__31;
  }

llvm_cbe_tmp__33:
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = fdiv double 1.000000e+00, %%32, !dbg !5 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_111_count);
  llvm_cbe_tmp__23 = (double )0x1p0 / llvm_cbe_tmp__22;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__23, *(long long*)(&llvm_cbe_tmp__23));
  llvm_cbe_storemerge1__PHI_TEMPORARY = (double )llvm_cbe_tmp__23;   /* for PHI node */
  goto llvm_cbe_tmp__31;

llvm_cbe_tmp__31:
if (AESL_DEBUG_TRACE)
printf("\n  %%storemerge1 = phi double [ %%30, %%25 ], [ %%35, %%34 ], [ 1.000000e+00, %%31  for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_storemerge1_count);
  llvm_cbe_storemerge1 = (double )llvm_cbe_storemerge1__PHI_TEMPORARY;
if (AESL_DEBUG_TRACE) {
printf("\nstoremerge1 = %lf",llvm_cbe_storemerge1);
printf("\n = %lf",llvm_cbe_tmp__21);
printf("\n = %lf",llvm_cbe_tmp__23);
printf("\n = %lf",0x1p0);
}
if (AESL_DEBUG_TRACE)
printf("\n  store double %%storemerge1, double* %%b, align 8, !dbg !5 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_113_count);
  *llvm_cbe_b = llvm_cbe_storemerge1;
if (AESL_DEBUG_TRACE)
printf("\nstoremerge1 = %lf\n", llvm_cbe_storemerge1);
if (AESL_DEBUG_TRACE)
printf("\n  store double %%26, double* %%a, align 8, !dbg !4 for 0x%I64xth hint within @xrotg  --> \n", ++aesl_llvm_cbe_114_count);
  *llvm_cbe_a = llvm_cbe_tmp__17;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__17);
  goto llvm_cbe_tmp__28;

llvm_cbe_tmp__28:
  if (AESL_DEBUG_TRACE)
      printf("\nEND @xrotg}\n");
  return;
}

