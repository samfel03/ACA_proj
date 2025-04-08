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
void xswap(double *llvm_cbe_x, signed int llvm_cbe_ix0, signed int llvm_cbe_iy0);


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

void xswap(double *llvm_cbe_x, signed int llvm_cbe_ix0, signed int llvm_cbe_iy0) {
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
  unsigned int llvm_cbe_tmp__1;
  static  unsigned long long aesl_llvm_cbe_16_count = 0;
  unsigned int llvm_cbe_tmp__2;
  static  unsigned long long aesl_llvm_cbe_17_count = 0;
  static  unsigned long long aesl_llvm_cbe_18_count = 0;
  static  unsigned long long aesl_llvm_cbe_19_count = 0;
  static  unsigned long long aesl_llvm_cbe_20_count = 0;
  unsigned long long llvm_cbe_tmp__3;
  static  unsigned long long aesl_llvm_cbe_21_count = 0;
  double *llvm_cbe_tmp__4;
  static  unsigned long long aesl_llvm_cbe_22_count = 0;
  double llvm_cbe_tmp__5;
  static  unsigned long long aesl_llvm_cbe_23_count = 0;
  static  unsigned long long aesl_llvm_cbe_24_count = 0;
  static  unsigned long long aesl_llvm_cbe_25_count = 0;
  static  unsigned long long aesl_llvm_cbe_26_count = 0;
  static  unsigned long long aesl_llvm_cbe_27_count = 0;
  static  unsigned long long aesl_llvm_cbe_28_count = 0;
  unsigned long long llvm_cbe_tmp__6;
  static  unsigned long long aesl_llvm_cbe_29_count = 0;
  double *llvm_cbe_tmp__7;
  static  unsigned long long aesl_llvm_cbe_30_count = 0;
  double llvm_cbe_tmp__8;
  static  unsigned long long aesl_llvm_cbe_31_count = 0;
  static  unsigned long long aesl_llvm_cbe_32_count = 0;
  static  unsigned long long aesl_llvm_cbe_33_count = 0;
  static  unsigned long long aesl_llvm_cbe_34_count = 0;
  static  unsigned long long aesl_llvm_cbe_35_count = 0;
  static  unsigned long long aesl_llvm_cbe_36_count = 0;
  static  unsigned long long aesl_llvm_cbe_37_count = 0;
  static  unsigned long long aesl_llvm_cbe_38_count = 0;
  static  unsigned long long aesl_llvm_cbe_39_count = 0;
  static  unsigned long long aesl_llvm_cbe_40_count = 0;
  static  unsigned long long aesl_llvm_cbe_41_count = 0;
  unsigned long long llvm_cbe_tmp__9;
  static  unsigned long long aesl_llvm_cbe_42_count = 0;
  double *llvm_cbe_tmp__10;
  static  unsigned long long aesl_llvm_cbe_43_count = 0;
  double llvm_cbe_tmp__11;
  static  unsigned long long aesl_llvm_cbe_44_count = 0;
  static  unsigned long long aesl_llvm_cbe_45_count = 0;
  static  unsigned long long aesl_llvm_cbe_46_count = 0;
  static  unsigned long long aesl_llvm_cbe_47_count = 0;
  static  unsigned long long aesl_llvm_cbe_48_count = 0;
  static  unsigned long long aesl_llvm_cbe_49_count = 0;
  unsigned long long llvm_cbe_tmp__12;
  static  unsigned long long aesl_llvm_cbe_50_count = 0;
  double *llvm_cbe_tmp__13;
  static  unsigned long long aesl_llvm_cbe_51_count = 0;
  double llvm_cbe_tmp__14;
  static  unsigned long long aesl_llvm_cbe_52_count = 0;
  static  unsigned long long aesl_llvm_cbe_53_count = 0;
  static  unsigned long long aesl_llvm_cbe_54_count = 0;
  static  unsigned long long aesl_llvm_cbe_55_count = 0;
  static  unsigned long long aesl_llvm_cbe_56_count = 0;
  static  unsigned long long aesl_llvm_cbe_57_count = 0;
  static  unsigned long long aesl_llvm_cbe_58_count = 0;
  static  unsigned long long aesl_llvm_cbe_59_count = 0;
  unsigned int llvm_cbe_tmp__15;
  static  unsigned long long aesl_llvm_cbe_60_count = 0;
  static  unsigned long long aesl_llvm_cbe_61_count = 0;
  static  unsigned long long aesl_llvm_cbe_62_count = 0;
  static  unsigned long long aesl_llvm_cbe_63_count = 0;
  unsigned long long llvm_cbe_tmp__16;
  static  unsigned long long aesl_llvm_cbe_64_count = 0;
  double *llvm_cbe_tmp__17;
  static  unsigned long long aesl_llvm_cbe_65_count = 0;
  double llvm_cbe_tmp__18;
  static  unsigned long long aesl_llvm_cbe_66_count = 0;
  static  unsigned long long aesl_llvm_cbe_67_count = 0;
  static  unsigned long long aesl_llvm_cbe_68_count = 0;
  unsigned int llvm_cbe_tmp__19;
  static  unsigned long long aesl_llvm_cbe_69_count = 0;
  static  unsigned long long aesl_llvm_cbe_70_count = 0;
  static  unsigned long long aesl_llvm_cbe_71_count = 0;
  static  unsigned long long aesl_llvm_cbe_72_count = 0;
  unsigned long long llvm_cbe_tmp__20;
  static  unsigned long long aesl_llvm_cbe_73_count = 0;
  double *llvm_cbe_tmp__21;
  static  unsigned long long aesl_llvm_cbe_74_count = 0;
  double llvm_cbe_tmp__22;
  static  unsigned long long aesl_llvm_cbe_75_count = 0;
  static  unsigned long long aesl_llvm_cbe_76_count = 0;
  static  unsigned long long aesl_llvm_cbe_77_count = 0;
  static  unsigned long long aesl_llvm_cbe_78_count = 0;
  static  unsigned long long aesl_llvm_cbe_79_count = 0;
  static  unsigned long long aesl_llvm_cbe_80_count = 0;
  static  unsigned long long aesl_llvm_cbe_81_count = 0;
  static  unsigned long long aesl_llvm_cbe_82_count = 0;
  unsigned int llvm_cbe_tmp__23;
  static  unsigned long long aesl_llvm_cbe_83_count = 0;
  static  unsigned long long aesl_llvm_cbe_84_count = 0;
  static  unsigned long long aesl_llvm_cbe_85_count = 0;
  static  unsigned long long aesl_llvm_cbe_86_count = 0;
  unsigned long long llvm_cbe_tmp__24;
  static  unsigned long long aesl_llvm_cbe_87_count = 0;
  double *llvm_cbe_tmp__25;
  static  unsigned long long aesl_llvm_cbe_88_count = 0;
  double llvm_cbe_tmp__26;
  static  unsigned long long aesl_llvm_cbe_89_count = 0;
  static  unsigned long long aesl_llvm_cbe_90_count = 0;
  static  unsigned long long aesl_llvm_cbe_91_count = 0;
  unsigned int llvm_cbe_tmp__27;
  static  unsigned long long aesl_llvm_cbe_92_count = 0;
  static  unsigned long long aesl_llvm_cbe_93_count = 0;
  static  unsigned long long aesl_llvm_cbe_94_count = 0;
  static  unsigned long long aesl_llvm_cbe_95_count = 0;
  unsigned long long llvm_cbe_tmp__28;
  static  unsigned long long aesl_llvm_cbe_96_count = 0;
  double *llvm_cbe_tmp__29;
  static  unsigned long long aesl_llvm_cbe_97_count = 0;
  double llvm_cbe_tmp__30;
  static  unsigned long long aesl_llvm_cbe_98_count = 0;
  static  unsigned long long aesl_llvm_cbe_99_count = 0;
  static  unsigned long long aesl_llvm_cbe_100_count = 0;
  static  unsigned long long aesl_llvm_cbe_101_count = 0;
  static  unsigned long long aesl_llvm_cbe_102_count = 0;
  static  unsigned long long aesl_llvm_cbe_103_count = 0;
  static  unsigned long long aesl_llvm_cbe_104_count = 0;
  static  unsigned long long aesl_llvm_cbe_105_count = 0;
  unsigned int llvm_cbe_tmp__31;
  static  unsigned long long aesl_llvm_cbe_106_count = 0;
  static  unsigned long long aesl_llvm_cbe_107_count = 0;
  static  unsigned long long aesl_llvm_cbe_108_count = 0;
  static  unsigned long long aesl_llvm_cbe_109_count = 0;
  unsigned long long llvm_cbe_tmp__32;
  static  unsigned long long aesl_llvm_cbe_110_count = 0;
  double *llvm_cbe_tmp__33;
  static  unsigned long long aesl_llvm_cbe_111_count = 0;
  double llvm_cbe_tmp__34;
  static  unsigned long long aesl_llvm_cbe_112_count = 0;
  static  unsigned long long aesl_llvm_cbe_113_count = 0;
  static  unsigned long long aesl_llvm_cbe_114_count = 0;
  unsigned int llvm_cbe_tmp__35;
  static  unsigned long long aesl_llvm_cbe_115_count = 0;
  static  unsigned long long aesl_llvm_cbe_116_count = 0;
  static  unsigned long long aesl_llvm_cbe_117_count = 0;
  static  unsigned long long aesl_llvm_cbe_118_count = 0;
  unsigned long long llvm_cbe_tmp__36;
  static  unsigned long long aesl_llvm_cbe_119_count = 0;
  double *llvm_cbe_tmp__37;
  static  unsigned long long aesl_llvm_cbe_120_count = 0;
  double llvm_cbe_tmp__38;
  static  unsigned long long aesl_llvm_cbe_121_count = 0;
  static  unsigned long long aesl_llvm_cbe_122_count = 0;
  static  unsigned long long aesl_llvm_cbe_123_count = 0;
  static  unsigned long long aesl_llvm_cbe_124_count = 0;
  static  unsigned long long aesl_llvm_cbe_125_count = 0;
  static  unsigned long long aesl_llvm_cbe_126_count = 0;
  static  unsigned long long aesl_llvm_cbe_127_count = 0;
  static  unsigned long long aesl_llvm_cbe_128_count = 0;
  unsigned int llvm_cbe_tmp__39;
  static  unsigned long long aesl_llvm_cbe_129_count = 0;
  static  unsigned long long aesl_llvm_cbe_130_count = 0;
  static  unsigned long long aesl_llvm_cbe_131_count = 0;
  static  unsigned long long aesl_llvm_cbe_132_count = 0;
  unsigned long long llvm_cbe_tmp__40;
  static  unsigned long long aesl_llvm_cbe_133_count = 0;
  double *llvm_cbe_tmp__41;
  static  unsigned long long aesl_llvm_cbe_134_count = 0;
  double llvm_cbe_tmp__42;
  static  unsigned long long aesl_llvm_cbe_135_count = 0;
  static  unsigned long long aesl_llvm_cbe_136_count = 0;
  static  unsigned long long aesl_llvm_cbe_137_count = 0;
  unsigned int llvm_cbe_tmp__43;
  static  unsigned long long aesl_llvm_cbe_138_count = 0;
  static  unsigned long long aesl_llvm_cbe_139_count = 0;
  static  unsigned long long aesl_llvm_cbe_140_count = 0;
  static  unsigned long long aesl_llvm_cbe_141_count = 0;
  unsigned long long llvm_cbe_tmp__44;
  static  unsigned long long aesl_llvm_cbe_142_count = 0;
  double *llvm_cbe_tmp__45;
  static  unsigned long long aesl_llvm_cbe_143_count = 0;
  double llvm_cbe_tmp__46;
  static  unsigned long long aesl_llvm_cbe_144_count = 0;
  static  unsigned long long aesl_llvm_cbe_145_count = 0;
  static  unsigned long long aesl_llvm_cbe_146_count = 0;
  static  unsigned long long aesl_llvm_cbe_147_count = 0;
  static  unsigned long long aesl_llvm_cbe_148_count = 0;
  static  unsigned long long aesl_llvm_cbe_149_count = 0;
  static  unsigned long long aesl_llvm_cbe_150_count = 0;
  static  unsigned long long aesl_llvm_cbe_151_count = 0;
  unsigned int llvm_cbe_tmp__47;
  static  unsigned long long aesl_llvm_cbe_152_count = 0;
  static  unsigned long long aesl_llvm_cbe_153_count = 0;
  static  unsigned long long aesl_llvm_cbe_154_count = 0;
  static  unsigned long long aesl_llvm_cbe_155_count = 0;
  unsigned long long llvm_cbe_tmp__48;
  static  unsigned long long aesl_llvm_cbe_156_count = 0;
  double *llvm_cbe_tmp__49;
  static  unsigned long long aesl_llvm_cbe_157_count = 0;
  double llvm_cbe_tmp__50;
  static  unsigned long long aesl_llvm_cbe_158_count = 0;
  static  unsigned long long aesl_llvm_cbe_159_count = 0;
  static  unsigned long long aesl_llvm_cbe_160_count = 0;
  unsigned int llvm_cbe_tmp__51;
  static  unsigned long long aesl_llvm_cbe_161_count = 0;
  static  unsigned long long aesl_llvm_cbe_162_count = 0;
  static  unsigned long long aesl_llvm_cbe_163_count = 0;
  static  unsigned long long aesl_llvm_cbe_164_count = 0;
  unsigned long long llvm_cbe_tmp__52;
  static  unsigned long long aesl_llvm_cbe_165_count = 0;
  double *llvm_cbe_tmp__53;
  static  unsigned long long aesl_llvm_cbe_166_count = 0;
  double llvm_cbe_tmp__54;
  static  unsigned long long aesl_llvm_cbe_167_count = 0;
  static  unsigned long long aesl_llvm_cbe_168_count = 0;
  static  unsigned long long aesl_llvm_cbe_169_count = 0;
  static  unsigned long long aesl_llvm_cbe_170_count = 0;
  static  unsigned long long aesl_llvm_cbe_171_count = 0;
  static  unsigned long long aesl_llvm_cbe_172_count = 0;
  static  unsigned long long aesl_llvm_cbe_173_count = 0;
  static  unsigned long long aesl_llvm_cbe_174_count = 0;
  unsigned int llvm_cbe_tmp__55;
  static  unsigned long long aesl_llvm_cbe_175_count = 0;
  static  unsigned long long aesl_llvm_cbe_176_count = 0;
  static  unsigned long long aesl_llvm_cbe_177_count = 0;
  static  unsigned long long aesl_llvm_cbe_178_count = 0;
  unsigned long long llvm_cbe_tmp__56;
  static  unsigned long long aesl_llvm_cbe_179_count = 0;
  double *llvm_cbe_tmp__57;
  static  unsigned long long aesl_llvm_cbe_180_count = 0;
  double llvm_cbe_tmp__58;
  static  unsigned long long aesl_llvm_cbe_181_count = 0;
  static  unsigned long long aesl_llvm_cbe_182_count = 0;
  static  unsigned long long aesl_llvm_cbe_183_count = 0;
  unsigned int llvm_cbe_tmp__59;
  static  unsigned long long aesl_llvm_cbe_184_count = 0;
  static  unsigned long long aesl_llvm_cbe_185_count = 0;
  static  unsigned long long aesl_llvm_cbe_186_count = 0;
  static  unsigned long long aesl_llvm_cbe_187_count = 0;
  unsigned long long llvm_cbe_tmp__60;
  static  unsigned long long aesl_llvm_cbe_188_count = 0;
  double *llvm_cbe_tmp__61;
  static  unsigned long long aesl_llvm_cbe_189_count = 0;
  double llvm_cbe_tmp__62;
  static  unsigned long long aesl_llvm_cbe_190_count = 0;
  static  unsigned long long aesl_llvm_cbe_191_count = 0;
  static  unsigned long long aesl_llvm_cbe_192_count = 0;
  static  unsigned long long aesl_llvm_cbe_193_count = 0;
  static  unsigned long long aesl_llvm_cbe_194_count = 0;
  static  unsigned long long aesl_llvm_cbe_195_count = 0;
  static  unsigned long long aesl_llvm_cbe_196_count = 0;
  static  unsigned long long aesl_llvm_cbe_197_count = 0;

const char* AESL_DEBUG_TRACE = getenv("DEBUG_TRACE");
if (AESL_DEBUG_TRACE)
printf("\n\{ BEGIN @xswap\n");
if (AESL_DEBUG_TRACE)
printf("\n  %%1 = add i32 %%ix0, -1, !dbg !4 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_15_count);
  llvm_cbe_tmp__1 = (unsigned int )((unsigned int )(llvm_cbe_ix0&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__1&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%2 = add i32 %%iy0, -1, !dbg !4 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_16_count);
  llvm_cbe_tmp__2 = (unsigned int )((unsigned int )(llvm_cbe_iy0&4294967295ull)) + ((unsigned int )(4294967295u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__2&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%3 = sext i32 %%1 to i64, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_20_count);
  llvm_cbe_tmp__3 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__1);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__3);
if (AESL_DEBUG_TRACE)
printf("\n  %%4 = getelementptr inbounds double* %%x, i64 %%3, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_21_count);
  llvm_cbe_tmp__4 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__3))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__3));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%5 = load double* %%4, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_22_count);
  llvm_cbe_tmp__5 = (double )*llvm_cbe_tmp__4;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__5, *(long long*)(&llvm_cbe_tmp__5));
if (AESL_DEBUG_TRACE)
printf("\n  %%6 = sext i32 %%2 to i64, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_28_count);
  llvm_cbe_tmp__6 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__2);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__6);
if (AESL_DEBUG_TRACE)
printf("\n  %%7 = getelementptr inbounds double* %%x, i64 %%6, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_29_count);
  llvm_cbe_tmp__7 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__6))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__6));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%8 = load double* %%7, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_30_count);
  llvm_cbe_tmp__8 = (double )*llvm_cbe_tmp__7;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__8, *(long long*)(&llvm_cbe_tmp__8));
if (AESL_DEBUG_TRACE)
printf("\n  store double %%8, double* %%4, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_31_count);
  *llvm_cbe_tmp__4 = llvm_cbe_tmp__8;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__8);
if (AESL_DEBUG_TRACE)
printf("\n  store double %%5, double* %%7, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_32_count);
  *llvm_cbe_tmp__7 = llvm_cbe_tmp__5;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__5);
if (AESL_DEBUG_TRACE)
printf("\n  %%9 = sext i32 %%ix0 to i64, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_41_count);
  llvm_cbe_tmp__9 = (unsigned long long )((signed long long )(signed int )llvm_cbe_ix0);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__9);
if (AESL_DEBUG_TRACE)
printf("\n  %%10 = getelementptr inbounds double* %%x, i64 %%9, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_42_count);
  llvm_cbe_tmp__10 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__9))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__9));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%11 = load double* %%10, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_43_count);
  llvm_cbe_tmp__11 = (double )*llvm_cbe_tmp__10;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__11, *(long long*)(&llvm_cbe_tmp__11));
if (AESL_DEBUG_TRACE)
printf("\n  %%12 = sext i32 %%iy0 to i64, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_49_count);
  llvm_cbe_tmp__12 = (unsigned long long )((signed long long )(signed int )llvm_cbe_iy0);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__12);
if (AESL_DEBUG_TRACE)
printf("\n  %%13 = getelementptr inbounds double* %%x, i64 %%12, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_50_count);
  llvm_cbe_tmp__13 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__12))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__12));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%14 = load double* %%13, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_51_count);
  llvm_cbe_tmp__14 = (double )*llvm_cbe_tmp__13;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__14, *(long long*)(&llvm_cbe_tmp__14));
if (AESL_DEBUG_TRACE)
printf("\n  store double %%14, double* %%10, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_52_count);
  *llvm_cbe_tmp__10 = llvm_cbe_tmp__14;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__14);
if (AESL_DEBUG_TRACE)
printf("\n  store double %%11, double* %%13, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_53_count);
  *llvm_cbe_tmp__13 = llvm_cbe_tmp__11;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__11);
if (AESL_DEBUG_TRACE)
printf("\n  %%15 = add i32 %%ix0, 1, !dbg !4 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_59_count);
  llvm_cbe_tmp__15 = (unsigned int )((unsigned int )(llvm_cbe_ix0&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__15&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%16 = sext i32 %%15 to i64, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_63_count);
  llvm_cbe_tmp__16 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__15);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__16);
if (AESL_DEBUG_TRACE)
printf("\n  %%17 = getelementptr inbounds double* %%x, i64 %%16, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_64_count);
  llvm_cbe_tmp__17 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__16))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__16));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%18 = load double* %%17, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_65_count);
  llvm_cbe_tmp__18 = (double )*llvm_cbe_tmp__17;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__18, *(long long*)(&llvm_cbe_tmp__18));
if (AESL_DEBUG_TRACE)
printf("\n  %%19 = add i32 %%iy0, 1, !dbg !4 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_68_count);
  llvm_cbe_tmp__19 = (unsigned int )((unsigned int )(llvm_cbe_iy0&4294967295ull)) + ((unsigned int )(1u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__19&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%20 = sext i32 %%19 to i64, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_72_count);
  llvm_cbe_tmp__20 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__19);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__20);
if (AESL_DEBUG_TRACE)
printf("\n  %%21 = getelementptr inbounds double* %%x, i64 %%20, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_73_count);
  llvm_cbe_tmp__21 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__20))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__20));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%22 = load double* %%21, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_74_count);
  llvm_cbe_tmp__22 = (double )*llvm_cbe_tmp__21;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__22, *(long long*)(&llvm_cbe_tmp__22));
if (AESL_DEBUG_TRACE)
printf("\n  store double %%22, double* %%17, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_75_count);
  *llvm_cbe_tmp__17 = llvm_cbe_tmp__22;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__22);
if (AESL_DEBUG_TRACE)
printf("\n  store double %%18, double* %%21, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_76_count);
  *llvm_cbe_tmp__21 = llvm_cbe_tmp__18;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__18);
if (AESL_DEBUG_TRACE)
printf("\n  %%23 = add i32 %%ix0, 2, !dbg !4 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_82_count);
  llvm_cbe_tmp__23 = (unsigned int )((unsigned int )(llvm_cbe_ix0&4294967295ull)) + ((unsigned int )(2u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__23&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%24 = sext i32 %%23 to i64, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_86_count);
  llvm_cbe_tmp__24 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__23);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__24);
if (AESL_DEBUG_TRACE)
printf("\n  %%25 = getelementptr inbounds double* %%x, i64 %%24, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_87_count);
  llvm_cbe_tmp__25 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__24))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__24));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%26 = load double* %%25, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_88_count);
  llvm_cbe_tmp__26 = (double )*llvm_cbe_tmp__25;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__26, *(long long*)(&llvm_cbe_tmp__26));
if (AESL_DEBUG_TRACE)
printf("\n  %%27 = add i32 %%iy0, 2, !dbg !4 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_91_count);
  llvm_cbe_tmp__27 = (unsigned int )((unsigned int )(llvm_cbe_iy0&4294967295ull)) + ((unsigned int )(2u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__27&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%28 = sext i32 %%27 to i64, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_95_count);
  llvm_cbe_tmp__28 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__27);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__28);
if (AESL_DEBUG_TRACE)
printf("\n  %%29 = getelementptr inbounds double* %%x, i64 %%28, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_96_count);
  llvm_cbe_tmp__29 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__28))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__28));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%30 = load double* %%29, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_97_count);
  llvm_cbe_tmp__30 = (double )*llvm_cbe_tmp__29;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__30, *(long long*)(&llvm_cbe_tmp__30));
if (AESL_DEBUG_TRACE)
printf("\n  store double %%30, double* %%25, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_98_count);
  *llvm_cbe_tmp__25 = llvm_cbe_tmp__30;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__30);
if (AESL_DEBUG_TRACE)
printf("\n  store double %%26, double* %%29, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_99_count);
  *llvm_cbe_tmp__29 = llvm_cbe_tmp__26;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__26);
if (AESL_DEBUG_TRACE)
printf("\n  %%31 = add i32 %%ix0, 3, !dbg !4 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_105_count);
  llvm_cbe_tmp__31 = (unsigned int )((unsigned int )(llvm_cbe_ix0&4294967295ull)) + ((unsigned int )(3u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__31&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%32 = sext i32 %%31 to i64, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_109_count);
  llvm_cbe_tmp__32 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__31);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__32);
if (AESL_DEBUG_TRACE)
printf("\n  %%33 = getelementptr inbounds double* %%x, i64 %%32, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_110_count);
  llvm_cbe_tmp__33 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__32))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__32));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%34 = load double* %%33, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_111_count);
  llvm_cbe_tmp__34 = (double )*llvm_cbe_tmp__33;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__34, *(long long*)(&llvm_cbe_tmp__34));
if (AESL_DEBUG_TRACE)
printf("\n  %%35 = add i32 %%iy0, 3, !dbg !4 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_114_count);
  llvm_cbe_tmp__35 = (unsigned int )((unsigned int )(llvm_cbe_iy0&4294967295ull)) + ((unsigned int )(3u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__35&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%36 = sext i32 %%35 to i64, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_118_count);
  llvm_cbe_tmp__36 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__35);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__36);
if (AESL_DEBUG_TRACE)
printf("\n  %%37 = getelementptr inbounds double* %%x, i64 %%36, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_119_count);
  llvm_cbe_tmp__37 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__36))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__36));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%38 = load double* %%37, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_120_count);
  llvm_cbe_tmp__38 = (double )*llvm_cbe_tmp__37;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__38, *(long long*)(&llvm_cbe_tmp__38));
if (AESL_DEBUG_TRACE)
printf("\n  store double %%38, double* %%33, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_121_count);
  *llvm_cbe_tmp__33 = llvm_cbe_tmp__38;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__38);
if (AESL_DEBUG_TRACE)
printf("\n  store double %%34, double* %%37, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_122_count);
  *llvm_cbe_tmp__37 = llvm_cbe_tmp__34;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__34);
if (AESL_DEBUG_TRACE)
printf("\n  %%39 = add i32 %%ix0, 4, !dbg !4 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_128_count);
  llvm_cbe_tmp__39 = (unsigned int )((unsigned int )(llvm_cbe_ix0&4294967295ull)) + ((unsigned int )(4u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__39&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%40 = sext i32 %%39 to i64, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_132_count);
  llvm_cbe_tmp__40 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__39);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__40);
if (AESL_DEBUG_TRACE)
printf("\n  %%41 = getelementptr inbounds double* %%x, i64 %%40, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_133_count);
  llvm_cbe_tmp__41 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__40))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__40));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%42 = load double* %%41, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_134_count);
  llvm_cbe_tmp__42 = (double )*llvm_cbe_tmp__41;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__42, *(long long*)(&llvm_cbe_tmp__42));
if (AESL_DEBUG_TRACE)
printf("\n  %%43 = add i32 %%iy0, 4, !dbg !4 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_137_count);
  llvm_cbe_tmp__43 = (unsigned int )((unsigned int )(llvm_cbe_iy0&4294967295ull)) + ((unsigned int )(4u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__43&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%44 = sext i32 %%43 to i64, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_141_count);
  llvm_cbe_tmp__44 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__43);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__44);
if (AESL_DEBUG_TRACE)
printf("\n  %%45 = getelementptr inbounds double* %%x, i64 %%44, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_142_count);
  llvm_cbe_tmp__45 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__44))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__44));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%46 = load double* %%45, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_143_count);
  llvm_cbe_tmp__46 = (double )*llvm_cbe_tmp__45;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__46, *(long long*)(&llvm_cbe_tmp__46));
if (AESL_DEBUG_TRACE)
printf("\n  store double %%46, double* %%41, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_144_count);
  *llvm_cbe_tmp__41 = llvm_cbe_tmp__46;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__46);
if (AESL_DEBUG_TRACE)
printf("\n  store double %%42, double* %%45, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_145_count);
  *llvm_cbe_tmp__45 = llvm_cbe_tmp__42;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__42);
if (AESL_DEBUG_TRACE)
printf("\n  %%47 = add i32 %%ix0, 5, !dbg !4 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_151_count);
  llvm_cbe_tmp__47 = (unsigned int )((unsigned int )(llvm_cbe_ix0&4294967295ull)) + ((unsigned int )(5u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__47&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%48 = sext i32 %%47 to i64, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_155_count);
  llvm_cbe_tmp__48 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__47);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__48);
if (AESL_DEBUG_TRACE)
printf("\n  %%49 = getelementptr inbounds double* %%x, i64 %%48, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_156_count);
  llvm_cbe_tmp__49 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__48))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__48));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%50 = load double* %%49, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_157_count);
  llvm_cbe_tmp__50 = (double )*llvm_cbe_tmp__49;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__50, *(long long*)(&llvm_cbe_tmp__50));
if (AESL_DEBUG_TRACE)
printf("\n  %%51 = add i32 %%iy0, 5, !dbg !4 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_160_count);
  llvm_cbe_tmp__51 = (unsigned int )((unsigned int )(llvm_cbe_iy0&4294967295ull)) + ((unsigned int )(5u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__51&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%52 = sext i32 %%51 to i64, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_164_count);
  llvm_cbe_tmp__52 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__51);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__52);
if (AESL_DEBUG_TRACE)
printf("\n  %%53 = getelementptr inbounds double* %%x, i64 %%52, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_165_count);
  llvm_cbe_tmp__53 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__52))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__52));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%54 = load double* %%53, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_166_count);
  llvm_cbe_tmp__54 = (double )*llvm_cbe_tmp__53;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__54, *(long long*)(&llvm_cbe_tmp__54));
if (AESL_DEBUG_TRACE)
printf("\n  store double %%54, double* %%49, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_167_count);
  *llvm_cbe_tmp__49 = llvm_cbe_tmp__54;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__54);
if (AESL_DEBUG_TRACE)
printf("\n  store double %%50, double* %%53, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_168_count);
  *llvm_cbe_tmp__53 = llvm_cbe_tmp__50;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__50);
if (AESL_DEBUG_TRACE)
printf("\n  %%55 = add i32 %%ix0, 6, !dbg !4 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_174_count);
  llvm_cbe_tmp__55 = (unsigned int )((unsigned int )(llvm_cbe_ix0&4294967295ull)) + ((unsigned int )(6u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__55&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%56 = sext i32 %%55 to i64, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_178_count);
  llvm_cbe_tmp__56 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__55);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__56);
if (AESL_DEBUG_TRACE)
printf("\n  %%57 = getelementptr inbounds double* %%x, i64 %%56, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_179_count);
  llvm_cbe_tmp__57 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__56))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__56));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%58 = load double* %%57, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_180_count);
  llvm_cbe_tmp__58 = (double )*llvm_cbe_tmp__57;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__58, *(long long*)(&llvm_cbe_tmp__58));
if (AESL_DEBUG_TRACE)
printf("\n  %%59 = add i32 %%iy0, 6, !dbg !4 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_183_count);
  llvm_cbe_tmp__59 = (unsigned int )((unsigned int )(llvm_cbe_iy0&4294967295ull)) + ((unsigned int )(6u&4294967295ull));
if (AESL_DEBUG_TRACE)
printf("\n = 0x%X\n", ((unsigned int )(llvm_cbe_tmp__59&4294967295ull)));
if (AESL_DEBUG_TRACE)
printf("\n  %%60 = sext i32 %%59 to i64, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_187_count);
  llvm_cbe_tmp__60 = (unsigned long long )((signed long long )(signed int )llvm_cbe_tmp__59);
if (AESL_DEBUG_TRACE)
printf("\n = 0x%I64X\n", llvm_cbe_tmp__60);
if (AESL_DEBUG_TRACE)
printf("\n  %%61 = getelementptr inbounds double* %%x, i64 %%60, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_188_count);
  llvm_cbe_tmp__61 = (double *)(&llvm_cbe_x[(((signed long long )llvm_cbe_tmp__60))]);
if (AESL_DEBUG_TRACE) {
printf("\n = 0x%I64X",((signed long long )llvm_cbe_tmp__60));
}
if (AESL_DEBUG_TRACE)
printf("\n  %%62 = load double* %%61, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_189_count);
  llvm_cbe_tmp__62 = (double )*llvm_cbe_tmp__61;
if (AESL_DEBUG_TRACE)
printf("\n = %lf,  0x%llx\n", llvm_cbe_tmp__62, *(long long*)(&llvm_cbe_tmp__62));
if (AESL_DEBUG_TRACE)
printf("\n  store double %%62, double* %%57, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_190_count);
  *llvm_cbe_tmp__57 = llvm_cbe_tmp__62;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__62);
if (AESL_DEBUG_TRACE)
printf("\n  store double %%58, double* %%61, align 8, !dbg !3 for 0x%I64xth hint within @xswap  --> \n", ++aesl_llvm_cbe_191_count);
  *llvm_cbe_tmp__61 = llvm_cbe_tmp__58;
if (AESL_DEBUG_TRACE)
printf("\n = %lf\n", llvm_cbe_tmp__58);
  if (AESL_DEBUG_TRACE)
      printf("\nEND @xswap}\n");
  return;
}

