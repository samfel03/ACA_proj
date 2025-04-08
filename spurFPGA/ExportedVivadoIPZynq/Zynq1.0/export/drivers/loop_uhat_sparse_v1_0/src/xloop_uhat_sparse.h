// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XLOOP_UHAT_SPARSE_H
#define XLOOP_UHAT_SPARSE_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xloop_uhat_sparse_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Control_BaseAddress;
} XLoop_uhat_sparse_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XLoop_uhat_sparse;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XLoop_uhat_sparse_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XLoop_uhat_sparse_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XLoop_uhat_sparse_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XLoop_uhat_sparse_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XLoop_uhat_sparse_Initialize(XLoop_uhat_sparse *InstancePtr, UINTPTR BaseAddress);
XLoop_uhat_sparse_Config* XLoop_uhat_sparse_LookupConfig(UINTPTR BaseAddress);
#else
int XLoop_uhat_sparse_Initialize(XLoop_uhat_sparse *InstancePtr, u16 DeviceId);
XLoop_uhat_sparse_Config* XLoop_uhat_sparse_LookupConfig(u16 DeviceId);
#endif
int XLoop_uhat_sparse_CfgInitialize(XLoop_uhat_sparse *InstancePtr, XLoop_uhat_sparse_Config *ConfigPtr);
#else
int XLoop_uhat_sparse_Initialize(XLoop_uhat_sparse *InstancePtr, const char* InstanceName);
int XLoop_uhat_sparse_Release(XLoop_uhat_sparse *InstancePtr);
#endif

void XLoop_uhat_sparse_Start(XLoop_uhat_sparse *InstancePtr);
u32 XLoop_uhat_sparse_IsDone(XLoop_uhat_sparse *InstancePtr);
u32 XLoop_uhat_sparse_IsIdle(XLoop_uhat_sparse *InstancePtr);
u32 XLoop_uhat_sparse_IsReady(XLoop_uhat_sparse *InstancePtr);
void XLoop_uhat_sparse_EnableAutoRestart(XLoop_uhat_sparse *InstancePtr);
void XLoop_uhat_sparse_DisableAutoRestart(XLoop_uhat_sparse *InstancePtr);

void XLoop_uhat_sparse_Set_rowStart(XLoop_uhat_sparse *InstancePtr, u64 Data);
u64 XLoop_uhat_sparse_Get_rowStart(XLoop_uhat_sparse *InstancePtr);
void XLoop_uhat_sparse_Set_colIndex(XLoop_uhat_sparse *InstancePtr, u64 Data);
u64 XLoop_uhat_sparse_Get_colIndex(XLoop_uhat_sparse *InstancePtr);
void XLoop_uhat_sparse_Set_value_r(XLoop_uhat_sparse *InstancePtr, u64 Data);
u64 XLoop_uhat_sparse_Get_value_r(XLoop_uhat_sparse *InstancePtr);
void XLoop_uhat_sparse_Set_ELEMENTS(XLoop_uhat_sparse *InstancePtr, u32 Data);
u32 XLoop_uhat_sparse_Get_ELEMENTS(XLoop_uhat_sparse *InstancePtr);
void XLoop_uhat_sparse_Set_tol(XLoop_uhat_sparse *InstancePtr, u64 Data);
u64 XLoop_uhat_sparse_Get_tol(XLoop_uhat_sparse *InstancePtr);
void XLoop_uhat_sparse_Set_L(XLoop_uhat_sparse *InstancePtr, u64 Data);
u64 XLoop_uhat_sparse_Get_L(XLoop_uhat_sparse *InstancePtr);
void XLoop_uhat_sparse_Set_L_exp(XLoop_uhat_sparse *InstancePtr, u64 Data);
u64 XLoop_uhat_sparse_Get_L_exp(XLoop_uhat_sparse *InstancePtr);
void XLoop_uhat_sparse_Set_uhat_i(XLoop_uhat_sparse *InstancePtr, u64 Data);
u64 XLoop_uhat_sparse_Get_uhat_i(XLoop_uhat_sparse *InstancePtr);
void XLoop_uhat_sparse_Set_R(XLoop_uhat_sparse *InstancePtr, u64 Data);
u64 XLoop_uhat_sparse_Get_R(XLoop_uhat_sparse *InstancePtr);
void XLoop_uhat_sparse_Set_R_exp(XLoop_uhat_sparse *InstancePtr, u64 Data);
u64 XLoop_uhat_sparse_Get_R_exp(XLoop_uhat_sparse *InstancePtr);

void XLoop_uhat_sparse_InterruptGlobalEnable(XLoop_uhat_sparse *InstancePtr);
void XLoop_uhat_sparse_InterruptGlobalDisable(XLoop_uhat_sparse *InstancePtr);
void XLoop_uhat_sparse_InterruptEnable(XLoop_uhat_sparse *InstancePtr, u32 Mask);
void XLoop_uhat_sparse_InterruptDisable(XLoop_uhat_sparse *InstancePtr, u32 Mask);
void XLoop_uhat_sparse_InterruptClear(XLoop_uhat_sparse *InstancePtr, u32 Mask);
u32 XLoop_uhat_sparse_InterruptGetEnabled(XLoop_uhat_sparse *InstancePtr);
u32 XLoop_uhat_sparse_InterruptGetStatus(XLoop_uhat_sparse *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
