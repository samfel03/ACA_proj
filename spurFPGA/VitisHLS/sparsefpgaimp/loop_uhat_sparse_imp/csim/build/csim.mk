# ==============================================================
# Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
# Tool Version Limit: 2023.10
# Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
# Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
# 
# ==============================================================
CSIM_DESIGN = 1

__SIM_FPO__ = 1

__SIM_MATHHLS__ = 1

__SIM_FFT__ = 1

__SIM_FIR__ = 1

__SIM_DDS__ = 1

ObjDir = obj

HLS_SOURCES = ../../../../../CCE-C/library/mainsparse.cpp ../../../../../CCE-C/library/src/call_rcond.c ../../../loop_uhat_sparse.cpp ../../../../../CCE-C/library/src/rtGetInf.c ../../../../../CCE-C/library/src/rtGetNaN.c ../../../../../CCE-C/library/src/rt_nonfinite.c ../../../../../CCE-C/library/src/svd.c ../../../../../CCE-C/library/src/xaxpy.c ../../../../../CCE-C/library/src/xdotc.c ../../../../../CCE-C/library/src/xnrm2.c ../../../../../CCE-C/library/src/xrot.c ../../../../../CCE-C/library/src/xrotg.c ../../../../../CCE-C/library/src/xswap.c

override TARGET := csim.exe

AUTOPILOT_ROOT := C:/Xilinx/Vitis_HLS/2023.2
AUTOPILOT_MACH := win64
ifdef AP_GCC_M32
  AUTOPILOT_MACH := Linux_x86
  IFLAG += -m32
endif
ifndef AP_GCC_PATH
  AP_GCC_PATH := C:/Xilinx/Vitis_HLS/2023.2/tps/win64/msys64/mingw64/bin
endif
AUTOPILOT_TOOL := ${AUTOPILOT_ROOT}/${AUTOPILOT_MACH}/tools
AP_CLANG_PATH := ${AUTOPILOT_ROOT}/tps/win64/msys64/mingw64/bin
AUTOPILOT_TECH := ${AUTOPILOT_ROOT}/common/technology


IFLAG += -I "${AUTOPILOT_ROOT}/include"
IFLAG += -I "${AUTOPILOT_ROOT}/include/ap_sysc"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC/AESL_FP_comp"
IFLAG += -I "${AUTOPILOT_TECH}/generic/SystemC/AESL_comp"
IFLAG += -I "${AUTOPILOT_TOOL}/auto_cc/include"
IFLAG += -D__HLS_COSIM__

IFLAG += -D__HLS_CSIM__

IFLAG += -D__VITIS_HLS__

IFLAG += -D__SIM_FPO__

IFLAG += -D__SIM_FFT__

IFLAG += -D__SIM_FIR__

IFLAG += -D__SIM_DDS__

IFLAG += -D__DSP48E1__
LFLAG += -Wl,--stack,0x40000000
IFLAG += -g
IFLAG += -DNT
LFLAG += -Wl,--enable-auto-import 
DFLAG += -DAUTOCC
DFLAG += -D__xilinx_ip_top= -DAESL_TB
CCFLAG += -Werror=return-type
CCFLAG += -Wno-abi
TOOLCHAIN += 



include ./Makefile.rules

all: $(TARGET)



AUTOCC := cmd //c apcc.bat  

$(ObjDir)/mainsparse.o: ../../../../../CCE-C/library/mainsparse.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../../../CCE-C/library/mainsparse.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD -IC:/Research/CU-Spur-Sean/spurFPGA/CCE-C/library/include -IC:/Research/CU-Spur-Sean/spurFPGA/CCE-C/library/include -Wno-unknown-pragmas -Wno-unknown-pragmas  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/mainsparse.d

$(ObjDir)/call_rcond.o: ../../../../../CCE-C/library/src/call_rcond.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../../CCE-C/library/src/call_rcond.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/call_rcond.d

$(ObjDir)/loop_uhat_sparse.o: ../../../loop_uhat_sparse.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling ../../../loop_uhat_sparse.cpp in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(CC) ${CCFLAG} -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/loop_uhat_sparse.d

$(ObjDir)/rtGetInf.o: ../../../../../CCE-C/library/src/rtGetInf.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../../CCE-C/library/src/rtGetInf.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/rtGetInf.d

$(ObjDir)/rtGetNaN.o: ../../../../../CCE-C/library/src/rtGetNaN.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../../CCE-C/library/src/rtGetNaN.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/rtGetNaN.d

$(ObjDir)/rt_nonfinite.o: ../../../../../CCE-C/library/src/rt_nonfinite.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../../CCE-C/library/src/rt_nonfinite.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/rt_nonfinite.d

$(ObjDir)/svd.o: ../../../../../CCE-C/library/src/svd.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../../CCE-C/library/src/svd.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/svd.d

$(ObjDir)/xaxpy.o: ../../../../../CCE-C/library/src/xaxpy.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../../CCE-C/library/src/xaxpy.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/xaxpy.d

$(ObjDir)/xdotc.o: ../../../../../CCE-C/library/src/xdotc.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../../CCE-C/library/src/xdotc.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/xdotc.d

$(ObjDir)/xnrm2.o: ../../../../../CCE-C/library/src/xnrm2.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../../CCE-C/library/src/xnrm2.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/xnrm2.d

$(ObjDir)/xrot.o: ../../../../../CCE-C/library/src/xrot.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../../CCE-C/library/src/xrot.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/xrot.d

$(ObjDir)/xrotg.o: ../../../../../CCE-C/library/src/xrotg.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../../CCE-C/library/src/xrotg.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/xrotg.d

$(ObjDir)/xswap.o: ../../../../../CCE-C/library/src/xswap.c $(ObjDir)/.dir
	$(Echo) "   Compiling(apcc) ../../../../../CCE-C/library/src/xswap.c in $(BuildMode) mode" $(AVE_DIR_DLOG)
	$(Verb)  $(AUTOCC) -c -MMD  $(IFLAG) $(DFLAG) $< -o $@ ; \

-include $(ObjDir)/xswap.d
