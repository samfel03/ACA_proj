# 1 "../CCE-C/library/src/rtGetInf.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 360 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Xilinx/Vitis_HLS/2023.2/common/technology/autopilot\\etc/autopilot_ssdm_op.h" 1
# 266 "C:/Xilinx/Vitis_HLS/2023.2/common/technology/autopilot\\etc/autopilot_ssdm_op.h"
    void _ssdm_op_IfRead() __attribute__ ((nothrow));
    void _ssdm_op_IfWrite() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_IfNbRead() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_IfNbWrite() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_IfCanRead() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_IfCanWrite() __attribute__ ((nothrow));


    void _ssdm_StreamRead() __attribute__ ((nothrow));
    void _ssdm_StreamWrite() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_StreamNbRead() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_StreamNbWrite() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_StreamCanRead() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_StreamCanWrite() __attribute__ ((nothrow));
    void _ssdm_op_ReadReq() __attribute__ ((nothrow));
    void _ssdm_op_Read() __attribute__ ((nothrow));
    void _ssdm_op_WriteReq() __attribute__ ((nothrow));
    void _ssdm_op_Write() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_NbReadReq() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_CanReadReq() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_NbWriteReq() __attribute__ ((nothrow));
    unsigned int __attribute__ ((bitwidth(1))) _ssdm_op_CanWriteReq() __attribute__ ((nothrow));




    void _ssdm_op_MemShiftRead() __attribute__ ((nothrow));

    void _ssdm_op_PrintNone() __attribute__ ((nothrow));
    void _ssdm_op_PrintInt() __attribute__ ((nothrow));
    void _ssdm_op_PrintDouble() __attribute__ ((nothrow));

    void _ssdm_op_Wait(int) __attribute__ ((nothrow));
    void _ssdm_op_Poll() __attribute__ ((nothrow));

    void _ssdm_op_Return() __attribute__ ((nothrow));


    void _ssdm_op_SpecSynModule() __attribute__ ((nothrow));
    void _ssdm_op_SpecTopModule() __attribute__ ((nothrow));
    void _ssdm_op_SpecProcessDecl() __attribute__ ((nothrow));
    void _ssdm_op_SpecProcessDef() __attribute__ ((nothrow));
    void _ssdm_op_SpecPort() __attribute__ ((nothrow));
    void _ssdm_op_SpecConnection() __attribute__ ((nothrow));
    void _ssdm_op_SpecChannel() __attribute__ ((nothrow));
    void _ssdm_op_SpecSensitive() __attribute__ ((nothrow));
    void _ssdm_op_SpecModuleInst() __attribute__ ((nothrow));
    void _ssdm_op_SpecPortMap() __attribute__ ((nothrow));

    void _ssdm_op_SpecReset() __attribute__ ((nothrow));

    void _ssdm_op_SpecPlatform() __attribute__ ((nothrow));
    void _ssdm_op_SpecClockDomain() __attribute__ ((nothrow));
    void _ssdm_op_SpecPowerDomain() __attribute__ ((nothrow));

    int _ssdm_op_SpecRegionBegin() __attribute__ ((nothrow));
    int _ssdm_op_SpecRegionEnd() __attribute__ ((nothrow));

    void _ssdm_op_SpecLoopName() __attribute__ ((nothrow));

    void _ssdm_op_SpecLoopTripCount() __attribute__ ((nothrow));

    int _ssdm_op_SpecStateBegin() __attribute__ ((nothrow));
    int _ssdm_op_SpecStateEnd() __attribute__ ((nothrow));

    void _ssdm_op_SpecInterface() __attribute__ ((nothrow));

    void _ssdm_op_SpecPipeline() __attribute__ ((nothrow));
    void _ssdm_op_SpecDataflowPipeline() __attribute__ ((nothrow));


    void _ssdm_op_SpecLatency() __attribute__ ((nothrow));
    void _ssdm_op_SpecParallel() __attribute__ ((nothrow));
    void _ssdm_op_SpecProtocol() __attribute__ ((nothrow));
    void _ssdm_op_SpecOccurrence() __attribute__ ((nothrow));

    void _ssdm_op_SpecResource() __attribute__ ((nothrow));
    void _ssdm_op_SpecResourceLimit() __attribute__ ((nothrow));
    void _ssdm_op_SpecCHCore() __attribute__ ((nothrow));
    void _ssdm_op_SpecFUCore() __attribute__ ((nothrow));
    void _ssdm_op_SpecIFCore() __attribute__ ((nothrow));
    void _ssdm_op_SpecIPCore() __attribute__ ((nothrow));
    void _ssdm_op_SpecMemCore() __attribute__ ((nothrow));

    void _ssdm_op_SpecExt() __attribute__ ((nothrow));




    void _ssdm_SpecArrayDimSize() __attribute__ ((nothrow));

    void _ssdm_RegionBegin() __attribute__ ((nothrow));
    void _ssdm_RegionEnd() __attribute__ ((nothrow));

    void _ssdm_Unroll() __attribute__ ((nothrow));
    void _ssdm_UnrollRegion() __attribute__ ((nothrow));

    void _ssdm_InlineAll() __attribute__ ((nothrow));
    void _ssdm_InlineLoop() __attribute__ ((nothrow));
    void _ssdm_Inline() __attribute__ ((nothrow));
    void _ssdm_InlineSelf() __attribute__ ((nothrow));
    void _ssdm_InlineRegion() __attribute__ ((nothrow));

    void _ssdm_SpecArrayMap() __attribute__ ((nothrow));
    void _ssdm_SpecArrayPartition() __attribute__ ((nothrow));
    void _ssdm_SpecArrayReshape() __attribute__ ((nothrow));

    void _ssdm_SpecStream() __attribute__ ((nothrow));

    void _ssdm_op_SpecStable() __attribute__ ((nothrow));
    void _ssdm_op_SpecStableContent() __attribute__ ((nothrow));

    void _ssdm_op_SpecBindPort() __attribute__ ((nothrow));

    void _ssdm_op_SpecPipoDepth() __attribute__ ((nothrow));

    void _ssdm_SpecExpr() __attribute__ ((nothrow));
    void _ssdm_SpecExprBalance() __attribute__ ((nothrow));

    void _ssdm_SpecDependence() __attribute__ ((nothrow));

    void _ssdm_SpecLoopMerge() __attribute__ ((nothrow));
    void _ssdm_SpecLoopFlatten() __attribute__ ((nothrow));
    void _ssdm_SpecLoopRewind() __attribute__ ((nothrow));

    void _ssdm_SpecFuncInstantiation() __attribute__ ((nothrow));
    void _ssdm_SpecFuncBuffer() __attribute__ ((nothrow));
    void _ssdm_SpecFuncExtract() __attribute__ ((nothrow));
    void _ssdm_SpecConstant() __attribute__ ((nothrow));

    void _ssdm_DataPack() __attribute__ ((nothrow));
    void _ssdm_SpecDataPack() __attribute__ ((nothrow));

    void _ssdm_op_SpecBitsMap() __attribute__ ((nothrow));
    void _ssdm_op_SpecLicense() __attribute__ ((nothrow));
# 2 "<built-in>" 2
# 1 "../CCE-C/library/src/rtGetInf.c" 2
# 17 "../CCE-C/library/src/rtGetInf.c"
# 1 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\rtGetInf.h" 1
# 15 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\rtGetInf.h"
# 1 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\rtwtypes.h" 1
# 41 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\rtwtypes.h"
# 1 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h" 1
# 32 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
# 1 "C:\\Xilinx\\Vitis_HLS\\2023.2\\win64\\tools\\clang-3.9-csynth\\lib\\clang\\7.0.0\\include\\limits.h" 1 3
# 37 "C:\\Xilinx\\Vitis_HLS\\2023.2\\win64\\tools\\clang-3.9-csynth\\lib\\clang\\7.0.0\\include\\limits.h" 3
# 1 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\limits.h" 1 3





# 1 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\crtdefs.h" 1 3
# 10 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\crtdefs.h" 3
# 1 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 1 3
# 12 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 3
# 1 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include/_mingw_mac.h" 1 3
# 13 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 2 3
# 1 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include/_mingw_secapi.h" 1 3
# 14 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 2 3
# 282 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 3
# 1 "C:\\Xilinx\\Vitis_HLS\\2023.2\\win64\\tools\\clang-3.9-csynth\\lib\\clang\\7.0.0\\include\\vadefs.h" 1 3
# 26 "C:\\Xilinx\\Vitis_HLS\\2023.2\\win64\\tools\\clang-3.9-csynth\\lib\\clang\\7.0.0\\include\\vadefs.h" 3
# 1 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\vadefs.h" 1 3








# 1 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 1 3
# 595 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 3
# 1 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include/sdks/_mingw_directx.h" 1 3
# 596 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 2 3
# 1 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include/sdks/_mingw_ddk.h" 1 3
# 597 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 2 3
# 10 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\vadefs.h" 2 3




#pragma pack(push,_CRT_PACKING)
# 24 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\vadefs.h" 3
 typedef __builtin_va_list __gnuc_va_list;






  typedef __gnuc_va_list va_list;
# 103 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\vadefs.h" 3
#pragma pack(pop)
# 27 "C:\\Xilinx\\Vitis_HLS\\2023.2\\win64\\tools\\clang-3.9-csynth\\lib\\clang\\7.0.0\\include\\vadefs.h" 2 3
# 283 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 2 3
# 569 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\_mingw.h" 3
void __attribute__((__cdecl__)) __debugbreak(void);
extern __inline__ __attribute__((__always_inline__,__gnu_inline__)) void __attribute__((__cdecl__)) __debugbreak(void)
{
  __asm__ __volatile__("int {$}3":);
}




const char *__mingw_get_crt_info (void);
# 11 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\crtdefs.h" 2 3




#pragma pack(push,_CRT_PACKING)
# 35 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\crtdefs.h" 3
__extension__ typedef unsigned long size_t;
# 45 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\crtdefs.h" 3
__extension__ typedef long ssize_t;






typedef size_t rsize_t;
# 62 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\crtdefs.h" 3
__extension__ typedef long intptr_t;
# 75 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\crtdefs.h" 3
__extension__ typedef unsigned long uintptr_t;
# 88 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\crtdefs.h" 3
__extension__ typedef long ptrdiff_t;
# 98 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\crtdefs.h" 3
typedef unsigned short wchar_t;







typedef unsigned short wint_t;
typedef unsigned short wctype_t;





typedef int errno_t;




typedef long __time32_t;




__extension__ typedef long __time64_t;
# 138 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\crtdefs.h" 3
typedef __time64_t time_t;
# 422 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\crtdefs.h" 3
struct threadlocaleinfostruct;
struct threadmbcinfostruct;
typedef struct threadlocaleinfostruct *pthreadlocinfo;
typedef struct threadmbcinfostruct *pthreadmbcinfo;
struct __lc_time_data;

typedef struct localeinfo_struct {
  pthreadlocinfo locinfo;
  pthreadmbcinfo mbcinfo;
} _locale_tstruct,*_locale_t;



typedef struct tagLC_ID {
  unsigned short wLanguage;
  unsigned short wCountry;
  unsigned short wCodePage;
} LC_ID,*LPLC_ID;




typedef struct threadlocaleinfostruct {
  int refcount;
  unsigned int lc_codepage;
  unsigned int lc_collate_cp;
  unsigned long lc_handle[6];
  LC_ID lc_id[6];
  struct {
    char *locale;
    wchar_t *wlocale;
    int *refcount;
    int *wrefcount;
  } lc_category[6];
  int lc_clike;
  int mb_cur_max;
  int *lconv_intl_refcount;
  int *lconv_num_refcount;
  int *lconv_mon_refcount;
  struct lconv *lconv;
  int *ctype1_refcount;
  unsigned short *ctype1;
  const unsigned short *pctype;
  const unsigned char *pclmap;
  const unsigned char *pcumap;
  struct __lc_time_data *lc_time_curr;
} threadlocinfo;







#pragma pack(pop)
# 7 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\limits.h" 2 3
# 38 "C:\\Xilinx\\Vitis_HLS\\2023.2\\win64\\tools\\clang-3.9-csynth\\lib\\clang\\7.0.0\\include\\limits.h" 2 3
# 33 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h" 2
# 44 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
# 1 "C:\\Xilinx\\Vitis_HLS\\2023.2\\win64\\tools\\clang-3.9-csynth\\lib\\clang\\7.0.0\\include\\stdbool.h" 1 3
# 45 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h" 2
# 60 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
# 1 "C:\\Xilinx\\Vitis_HLS\\2023.2\\win64\\tools\\clang-3.9-csynth\\lib\\clang\\7.0.0\\include\\float.h" 1 3
# 45 "C:\\Xilinx\\Vitis_HLS\\2023.2\\win64\\tools\\clang-3.9-csynth\\lib\\clang\\7.0.0\\include\\float.h" 3
# 1 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\float.h" 1 3
# 253 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\float.h" 3
__attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _controlfp (unsigned int unNew, unsigned int unMask) ;
__attribute__((dllimport)) errno_t __attribute__((__cdecl__)) _controlfp_s(unsigned int *_CurrentState, unsigned int _NewValue, unsigned int _Mask);
__attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _control87 (unsigned int unNew, unsigned int unMask);


__attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _clearfp (void);
__attribute__ ((__dllimport__)) unsigned int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _statusfp (void);
# 273 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\float.h" 3
void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fpreset (void);
void __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) fpreset (void);


__attribute__ ((__dllimport__)) int * __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) __fpecode(void);
# 287 "C:/Xilinx/Vitis_HLS/2023.2/tps/mingw/8.3.0/win64.o/nt\\x86_64-w64-mingw32\\include\\float.h" 3
__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _chgsign (double _X);
__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _copysign (double _Number,double _Sign);
__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _logb (double);
__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _nextafter (double, double);
__attribute__ ((__dllimport__)) double __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _scalb (double, long);

__attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _finite (double);
__attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _fpclass (double);
__attribute__ ((__dllimport__)) int __attribute__((__cdecl__)) __attribute__ ((__nothrow__)) _isnan (double);


extern long double __attribute__((__cdecl__)) _chgsignl (long double);
# 46 "C:\\Xilinx\\Vitis_HLS\\2023.2\\win64\\tools\\clang-3.9-csynth\\lib\\clang\\7.0.0\\include\\float.h" 2 3
# 61 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h" 2
# 89 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
typedef unsigned char uchar_T;
typedef unsigned short ushort_T;
typedef unsigned long ulong_T;





typedef unsigned long long ulonglong_T;
# 222 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
 typedef signed char int8_T;
# 239 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
 typedef unsigned char uint8_T;
# 257 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
 typedef short int16_T;
# 275 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
 typedef unsigned short uint16_T;
# 293 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
 typedef int int32_T;
# 311 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
 typedef unsigned int uint32_T;
# 372 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
 typedef float real32_T;
# 386 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
 typedef double real64_T;
# 463 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
  __extension__

 typedef long long int64_T;
# 477 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
  __extension__

 typedef unsigned long long uint64_T;
# 535 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
 typedef real64_T real_T;
# 544 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
 typedef real_T time_T;
# 556 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
typedef unsigned char boolean_T;





typedef char char_T;





typedef int int_T;





typedef unsigned uint_T;





typedef unsigned char byte_T;
# 590 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
    typedef struct {
      real32_T re, im;
    } creal32_T;






    typedef struct {
      real64_T re, im;
    } creal64_T;






    typedef struct {
      real_T re, im;
    } creal_T;
# 619 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
    typedef struct {
      int8_T re, im;
    } cint8_T;






    typedef struct {
      uint8_T re, im;
    } cuint8_T;






    typedef struct {
      int16_T re, im;
    } cint16_T;






    typedef struct {
      uint16_T re, im;
    } cuint16_T;






    typedef struct {
      int32_T re, im;
    } cint32_T;






    typedef struct {
      uint32_T re, im;
    } cuint32_T;






    typedef struct {
      int64_T re, im;
    } cint64_T;






    typedef struct {
      uint64_T re, im;
    } cuint64_T;
# 827 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
# 1 "C:\\Xilinx\\Vitis_HLS\\2023.2\\win64\\tools\\clang-3.9-csynth\\lib\\clang\\7.0.0\\include\\stddef.h" 1 3
# 51 "C:\\Xilinx\\Vitis_HLS\\2023.2\\win64\\tools\\clang-3.9-csynth\\lib\\clang\\7.0.0\\include\\stddef.h" 3
typedef long int ptrdiff_t;
# 62 "C:\\Xilinx\\Vitis_HLS\\2023.2\\win64\\tools\\clang-3.9-csynth\\lib\\clang\\7.0.0\\include\\stddef.h" 3
typedef long unsigned int size_t;
# 90 "C:\\Xilinx\\Vitis_HLS\\2023.2\\win64\\tools\\clang-3.9-csynth\\lib\\clang\\7.0.0\\include\\stddef.h" 3
typedef unsigned short wchar_t;
# 828 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h" 2






typedef size_t mwSize;
typedef size_t mwIndex;
typedef ptrdiff_t mwSignedIndex;






    typedef int64_T SLIndex;
    typedef int64_T SLSize;
# 881 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\tmwtypes.h"
typedef unsigned short CHAR16_T;
# 42 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\rtwtypes.h" 2
# 16 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\rtGetInf.h" 2





extern real_T rtGetInf(void);
extern real32_T rtGetInfF(void);
extern real_T rtGetMinusInf(void);
extern real32_T rtGetMinusInfF(void);
# 18 "../CCE-C/library/src/rtGetInf.c" 2
# 1 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\rt_nonfinite.h" 1
# 21 "C:\\Research\\CU-Spur-Sean\\spurFPGA\\CCE-C\\library\\include\\rt_nonfinite.h"
extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;

extern boolean_T rtIsInf(real_T value);
extern boolean_T rtIsInfF(real32_T value);
extern boolean_T rtIsNaN(real_T value);
extern boolean_T rtIsNaNF(real32_T value);
# 19 "../CCE-C/library/src/rtGetInf.c" 2






real_T rtGetInf(void)
{
  return rtInf;
}






real32_T rtGetInfF(void)
{
  return rtInfF;
}






real_T rtGetMinusInf(void)
{
  return rtMinusInf;
}






real32_T rtGetMinusInfF(void)
{
  return rtMinusInfF;
}
