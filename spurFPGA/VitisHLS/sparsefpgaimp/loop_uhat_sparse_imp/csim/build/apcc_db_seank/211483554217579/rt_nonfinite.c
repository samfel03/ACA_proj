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

/* External Global Variable Declarations */
extern double rtNaN;
extern double rtInf;
extern double rtMinusInf;
extern float rtNaNF;
extern float rtInfF;
extern float rtMinusInfF;

/* Function Declarations */
double fmod(double, double);
float fmodf(float, float);
long double fmodl(long double, long double);
unsigned char rtIsInf(double llvm_cbe_value);
signed int __fpclassify(double );
unsigned char rtIsInfF(float llvm_cbe_value);
unsigned char rtIsNaN(double llvm_cbe_value);
signed int __isnan(double );
unsigned char rtIsNaNF(float llvm_cbe_value);


/* Global Variable Definitions and Initialization */
double rtNaN = LLVM_NAN("0x7ff8000000000000") /*nan*/ ;
double rtInf = LLVM_INF /*inf*/ ;
double rtMinusInf = -LLVM_INF /*inf*/ ;
float rtNaNF = LLVM_NANF("0x7ff8000000000000") /*nan*/ ;
float rtInfF = LLVM_INFF /*inf*/ ;
float rtMinusInfF = -LLVM_INFF /*inf*/ ;


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

unsigned char rtIsInf(double llvm_cbe_value) {
  static  unsigned long long aesl_llvm_cbe_1_count = 0;
  static  unsigned long long aesl_llvm_cbe_2_count = 0;
  static  unsigned long long aesl_llvm_cbe_3_count = 0;
  unsigned int llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_4_count = 0;
  static  unsigned long long aesl_llvm_cbe_5_count = 0;
  unsigned char llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_6_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @rtIsInf\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = tail call i32 @__fpclassify(double %%value) nounwind, !dbg !5 for 0x%I64xth hint within @rtIsInf  --> \n", ++aesl_llvm_cbe_3_count);
  llvm_cbe_tmp__1 = (unsigned int ) /*tail*/ __fpclassify(llvm_cbe_value);
if (AESL_DEBUG_TRACE) {
printf("\nArgument value = %lf,  0x%llx",llvm_cbe_value, *(long long*)(&llvm_cbe_value));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__1);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = zext i1 %%2 to i8, !dbg !5 for 0x%I64xth hint within @rtIsInf  --> \n", ++aesl_llvm_cbe_5_count);
  llvm_cbe_tmp__2 = (unsigned char )((unsigned char )(bool )((llvm_cbe_tmp__1&4294967295U) == (1280u&4294967295U))&1U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__2);
  if (AESL_DEBUG_TRACE)
      printf("\nEND @rtIsInf}\n");
  return llvm_cbe_tmp__2;
}


unsigned char rtIsInfF(float llvm_cbe_value) {
  static  unsigned long long aesl_llvm_cbe_7_count = 0;
  static  unsigned long long aesl_llvm_cbe_8_count = 0;
  static  unsigned long long aesl_llvm_cbe_9_count = 0;
  double llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_10_count = 0;
  unsigned int llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_11_count = 0;
  static  unsigned long long aesl_llvm_cbe_12_count = 0;
  unsigned char llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_13_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @rtIsInfF\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = fpext float %%value to double, !dbg !5 for 0x%I64xth hint within @rtIsInfF  --> \n", ++aesl_llvm_cbe_9_count);
  llvm_cbe_tmp__3 = (double )((double )llvm_cbe_value);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__3, *(long long*)(&llvm_cbe_tmp__3));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = tail call i32 @__fpclassify(double %%1) nounwind, !dbg !5 for 0x%I64xth hint within @rtIsInfF  --> \n", ++aesl_llvm_cbe_10_count);
  llvm_cbe_tmp__4 = (unsigned int ) /*tail*/ __fpclassify(llvm_cbe_tmp__3);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__3, *(long long*)(&llvm_cbe_tmp__3));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__4);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = zext i1 %%3 to i8, !dbg !5 for 0x%I64xth hint within @rtIsInfF  --> \n", ++aesl_llvm_cbe_12_count);
  llvm_cbe_tmp__5 = (unsigned char )((unsigned char )(bool )((llvm_cbe_tmp__4&4294967295U) == (1280u&4294967295U))&1U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__5);
  if (AESL_DEBUG_TRACE)
      printf("\nEND @rtIsInfF}\n");
  return llvm_cbe_tmp__5;
}


unsigned char rtIsNaN(double llvm_cbe_value) {
  static  unsigned long long aesl_llvm_cbe_14_count = 0;
  static  unsigned long long aesl_llvm_cbe_15_count = 0;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  unsigned int llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  unsigned char llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @rtIsNaN\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = tail call i32 @__isnan(double %%value) nounwind, !dbg !5 for 0x%I64xth hint within @rtIsNaN  --> \n", ++aesl_llvm_cbe_16_count);
  llvm_cbe_tmp__6 = (unsigned int ) /*tail*/ __isnan(llvm_cbe_value);
if (AESL_DEBUG_TRACE) {
printf("\nArgument value = %lf,  0x%llx",llvm_cbe_value, *(long long*)(&llvm_cbe_value));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__6);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = zext i1 %%2 to i8, !dbg !5 for 0x%I64xth hint within @rtIsNaN  --> \n", ++aesl_llvm_cbe_18_count);
  llvm_cbe_tmp__7 = (unsigned char )((unsigned char )(bool )((llvm_cbe_tmp__6&4294967295U) != (0u&4294967295U))&1U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__7);
  if (AESL_DEBUG_TRACE)
      printf("\nEND @rtIsNaN}\n");
  return llvm_cbe_tmp__7;
}


unsigned char rtIsNaNF(float llvm_cbe_value) {
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  double llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  unsigned int llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  unsigned char llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @rtIsNaNF\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = fpext float %%value to double, !dbg !5 for 0x%I64xth hint within @rtIsNaNF  --> \n", ++aesl_llvm_cbe_22_count);
  llvm_cbe_tmp__8 = (double )((double )llvm_cbe_value);
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__8, *(long long*)(&llvm_cbe_tmp__8));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = tail call i32 @__isnan(double %%1) nounwind, !dbg !5 for 0x%I64xth hint within @rtIsNaNF  --> \n", ++aesl_llvm_cbe_23_count);
  llvm_cbe_tmp__9 = (unsigned int ) /*tail*/ __isnan(llvm_cbe_tmp__8);
if (AESL_DEBUG_TRACE) {
printf("\nArgument  = %lf,  0x%llx",llvm_cbe_tmp__8, *(long long*)(&llvm_cbe_tmp__8));
printf("\nReturn  = 0x%X",llvm_cbe_tmp__9);
}
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = zext i1 %%3 to i8, !dbg !5 for 0x%I64xth hint within @rtIsNaNF  --> \n", ++aesl_llvm_cbe_25_count);
  llvm_cbe_tmp__10 = (unsigned char )((unsigned char )(bool )((llvm_cbe_tmp__9&4294967295U) != (0u&4294967295U))&1U);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", llvm_cbe_tmp__10);
  if (AESL_DEBUG_TRACE)
      printf("\nEND @rtIsNaNF}\n");
  return llvm_cbe_tmp__10;
}

