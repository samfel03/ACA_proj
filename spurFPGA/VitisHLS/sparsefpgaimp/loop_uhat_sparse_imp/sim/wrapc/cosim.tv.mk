# ==============================================================
# Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
# Tool Version Limit: 2023.10
# Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
# Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
# 
# ==============================================================
__SIM_FPO__ = 1
__SIM_MATHHLS__ = 1
__SIM_FFT__ = 1
__SIM_FIR__ = 1
__SIM_DDS__ = 1

DIRECTORY := $(shell basename $(CURDIR))
ifeq ($(DIRECTORY), wrapc_pc)
  override TARGET := cosim.pc.exe
  WFLAG += -DPOST_CHECK
else
  override TARGET := cosim.tv.exe
endif
IRWRAPPER  := $(basename $(wildcard *.ll))
CPPWRAPPER := $(IRWRAPPER:_ir=)
APATB_UTIL := $(basename $(wildcard $(IRWRAPPER:_ir=_util).cpp))

AUTOPILOT_ROOT := C:/Xilinx/Vitis_HLS/2023.2
AUTOPILOT_MACH := win64

ifdef AP_GCC_M32
  AUTOPILOT_MACH := Linux_x86
  IFLAG += -m32
endif
ifndef AP_GCC_PATH
  AP_GCC_PATH := C:/Xilinx/Vitis_HLS/2023.2/tps/win64/msys64/mingw64/bin
endif
AUTOPILOT_TOOL = ${AUTOPILOT_ROOT}/${AUTOPILOT_MACH}/tools
AUTOPILOT_TECH = ${AUTOPILOT_ROOT}/common/technology
CCFLAG += -Werror=return-type
TOOLCHAIN += 

IFLAG += -g

IFLAG += -I "${AUTOPILOT_ROOT}/include"
IFLAG += -I "${AUTOPILOT_ROOT}/include/ap_sysc"
IFLAG += -I "${AUTOPILOT_ROOT}/common/technology/generic/SystemC"
IFLAG += -I "${AUTOPILOT_ROOT}/common/technology/generic/SystemC/AESL_FP_comp"
IFLAG += -I "${AUTOPILOT_ROOT}/common/technology/generic/SystemC/AESL_comp"
IFLAG += -I "${AUTOPILOT_ROOT}/${AUTOPILOT_MACH}/tools/auto_cc/include"
IFLAG += -D__VITIS_HLS__
IFLAG += -D__HLS_COSIM__
IFLAG += -D__SIM_FPO__
IFLAG += -D__SIM_FFT__
IFLAG += -D__SIM_FIR__
IFLAG += -D__SIM_DDS__
IFLAG += -D__DSP48E1__
WFLAG += -DUSE_BINARY_TV_FILE
IFLAG += -DNT
LFLAG += -Wl,--stack,0x40000000
LFLAG += -lpthread
LFLAG += -L "${AUTOPILOT_ROOT}/${AUTOPILOT_MACH}/tools/clang-3.9-csynth/lib/clang/7.0.0/lib/windows" -lhls_half2float
IFLAG += -D__RTL_SIMULATION__
IFLAG += -D__xilinx_ip_top=
DFLAG += -DAESL_PIPELINE
LFLAG += -Wl,--enable-auto-import
DFLAG += -DAESL_EXTERN_C

include ./Makefile.rules

APATB_OBJECTS := $(addprefix $(ObjDir)/, $(addsuffix .o, $(CPPWRAPPER) $(IRWRAPPER) $(APATB_UTIL)))
OBJECTS := $(filter-out $(APATB_OBJECTS), $(OBJECTS)) $(APATB_OBJECTS)

all : $(TARGET)

$(ObjDir)/$(CPPWRAPPER).o: $(CPPWRAPPER).cpp
	$(Echo) "   Compiling $<" $(AVE_DIR_DLOG)
	$(Verb) $(CXX) -fno-builtin-isinf -fno-builtin-isnan -c $(IFLAG) $(WFLAG) $< -o $@

$(ObjDir)/mainsparse.cpp_pre.cpp.tb.o : mainsparse.cpp_pre.cpp.tb.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling mainsparse.cpp_pre.cpp.tb.cpp" $(AVE_DIR_DLOG)
	$(Verb) $(CC) ${CCFLAG} ${TOOLCHAIN}  -fno-builtin-isinf -fno-builtin-isnan -c -Wl,--heap,3000000000 -Wl,--heap,3000000000 -Wno-unknown-pragmas -Wno-unknown-pragmas $(IFLAG) $(DFLAG) $< -o $@; \

$(ObjDir)/call_rcond.c_pre.c.tb.o : call_rcond.c_pre.c.tb.c $(ObjDir)/.dir
	$(Echo) "   Compiling call_rcond.c_pre.c.tb.c" $(AVE_DIR_DLOG)
	$(Verb) $(CC) ${CCFLAG} ${TOOLCHAIN} -fno-builtin-isinf -fno-builtin-isnan -c  $(IFLAG) $(DFLAG) $< -o $@; \

$(ObjDir)/loop_uhat_sparse.cpp_pre.cpp.tb.o : loop_uhat_sparse.cpp_pre.cpp.tb.cpp $(ObjDir)/.dir
	$(Echo) "   Compiling loop_uhat_sparse.cpp_pre.cpp.tb.cpp" $(AVE_DIR_DLOG)
	$(Verb) $(CC) ${CCFLAG} ${TOOLCHAIN}  -fno-builtin-isinf -fno-builtin-isnan -c -Wl,--heap,3000000000 -Wl,--heap,3000000000 $(IFLAG) $(DFLAG) $< -o $@; \

$(ObjDir)/rtGetInf.c_pre.c.tb.o : rtGetInf.c_pre.c.tb.c $(ObjDir)/.dir
	$(Echo) "   Compiling rtGetInf.c_pre.c.tb.c" $(AVE_DIR_DLOG)
	$(Verb) $(CC) ${CCFLAG} ${TOOLCHAIN} -fno-builtin-isinf -fno-builtin-isnan -c  $(IFLAG) $(DFLAG) $< -o $@; \

$(ObjDir)/rtGetNaN.c_pre.c.tb.o : rtGetNaN.c_pre.c.tb.c $(ObjDir)/.dir
	$(Echo) "   Compiling rtGetNaN.c_pre.c.tb.c" $(AVE_DIR_DLOG)
	$(Verb) $(CC) ${CCFLAG} ${TOOLCHAIN} -fno-builtin-isinf -fno-builtin-isnan -c  $(IFLAG) $(DFLAG) $< -o $@; \

$(ObjDir)/rt_nonfinite.c_pre.c.tb.o : rt_nonfinite.c_pre.c.tb.c $(ObjDir)/.dir
	$(Echo) "   Compiling rt_nonfinite.c_pre.c.tb.c" $(AVE_DIR_DLOG)
	$(Verb) $(CC) ${CCFLAG} ${TOOLCHAIN} -fno-builtin-isinf -fno-builtin-isnan -c  $(IFLAG) $(DFLAG) $< -o $@; \

$(ObjDir)/svd.c_pre.c.tb.o : svd.c_pre.c.tb.c $(ObjDir)/.dir
	$(Echo) "   Compiling svd.c_pre.c.tb.c" $(AVE_DIR_DLOG)
	$(Verb) $(CC) ${CCFLAG} ${TOOLCHAIN} -fno-builtin-isinf -fno-builtin-isnan -c  $(IFLAG) $(DFLAG) $< -o $@; \

$(ObjDir)/xaxpy.c_pre.c.tb.o : xaxpy.c_pre.c.tb.c $(ObjDir)/.dir
	$(Echo) "   Compiling xaxpy.c_pre.c.tb.c" $(AVE_DIR_DLOG)
	$(Verb) $(CC) ${CCFLAG} ${TOOLCHAIN} -fno-builtin-isinf -fno-builtin-isnan -c  $(IFLAG) $(DFLAG) $< -o $@; \

$(ObjDir)/xdotc.c_pre.c.tb.o : xdotc.c_pre.c.tb.c $(ObjDir)/.dir
	$(Echo) "   Compiling xdotc.c_pre.c.tb.c" $(AVE_DIR_DLOG)
	$(Verb) $(CC) ${CCFLAG} ${TOOLCHAIN} -fno-builtin-isinf -fno-builtin-isnan -c  $(IFLAG) $(DFLAG) $< -o $@; \

$(ObjDir)/xnrm2.c_pre.c.tb.o : xnrm2.c_pre.c.tb.c $(ObjDir)/.dir
	$(Echo) "   Compiling xnrm2.c_pre.c.tb.c" $(AVE_DIR_DLOG)
	$(Verb) $(CC) ${CCFLAG} ${TOOLCHAIN} -fno-builtin-isinf -fno-builtin-isnan -c  $(IFLAG) $(DFLAG) $< -o $@; \

$(ObjDir)/xrot.c_pre.c.tb.o : xrot.c_pre.c.tb.c $(ObjDir)/.dir
	$(Echo) "   Compiling xrot.c_pre.c.tb.c" $(AVE_DIR_DLOG)
	$(Verb) $(CC) ${CCFLAG} ${TOOLCHAIN} -fno-builtin-isinf -fno-builtin-isnan -c  $(IFLAG) $(DFLAG) $< -o $@; \

$(ObjDir)/xrotg.c_pre.c.tb.o : xrotg.c_pre.c.tb.c $(ObjDir)/.dir
	$(Echo) "   Compiling xrotg.c_pre.c.tb.c" $(AVE_DIR_DLOG)
	$(Verb) $(CC) ${CCFLAG} ${TOOLCHAIN} -fno-builtin-isinf -fno-builtin-isnan -c  $(IFLAG) $(DFLAG) $< -o $@; \

$(ObjDir)/xswap.c_pre.c.tb.o : xswap.c_pre.c.tb.c $(ObjDir)/.dir
	$(Echo) "   Compiling xswap.c_pre.c.tb.c" $(AVE_DIR_DLOG)
	$(Verb) $(CC) ${CCFLAG} ${TOOLCHAIN} -fno-builtin-isinf -fno-builtin-isnan -c  $(IFLAG) $(DFLAG) $< -o $@; \
