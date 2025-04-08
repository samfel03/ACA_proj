// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xloop_uhat_sparse.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XLoop_uhat_sparse_CfgInitialize(XLoop_uhat_sparse *InstancePtr, XLoop_uhat_sparse_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XLoop_uhat_sparse_Start(XLoop_uhat_sparse *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_AP_CTRL) & 0x80;
    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XLoop_uhat_sparse_IsDone(XLoop_uhat_sparse *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XLoop_uhat_sparse_IsIdle(XLoop_uhat_sparse *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XLoop_uhat_sparse_IsReady(XLoop_uhat_sparse *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XLoop_uhat_sparse_EnableAutoRestart(XLoop_uhat_sparse *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XLoop_uhat_sparse_DisableAutoRestart(XLoop_uhat_sparse *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_AP_CTRL, 0);
}

void XLoop_uhat_sparse_Set_rowStart(XLoop_uhat_sparse *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_ROWSTART_DATA, (u32)(Data));
    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_ROWSTART_DATA + 4, (u32)(Data >> 32));
}

u64 XLoop_uhat_sparse_Get_rowStart(XLoop_uhat_sparse *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_ROWSTART_DATA);
    Data += (u64)XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_ROWSTART_DATA + 4) << 32;
    return Data;
}

void XLoop_uhat_sparse_Set_colIndex(XLoop_uhat_sparse *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_COLINDEX_DATA, (u32)(Data));
    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_COLINDEX_DATA + 4, (u32)(Data >> 32));
}

u64 XLoop_uhat_sparse_Get_colIndex(XLoop_uhat_sparse *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_COLINDEX_DATA);
    Data += (u64)XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_COLINDEX_DATA + 4) << 32;
    return Data;
}

void XLoop_uhat_sparse_Set_value_r(XLoop_uhat_sparse *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_VALUE_R_DATA, (u32)(Data));
    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_VALUE_R_DATA + 4, (u32)(Data >> 32));
}

u64 XLoop_uhat_sparse_Get_value_r(XLoop_uhat_sparse *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_VALUE_R_DATA);
    Data += (u64)XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_VALUE_R_DATA + 4) << 32;
    return Data;
}

void XLoop_uhat_sparse_Set_ELEMENTS(XLoop_uhat_sparse *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_ELEMENTS_DATA, Data);
}

u32 XLoop_uhat_sparse_Get_ELEMENTS(XLoop_uhat_sparse *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_ELEMENTS_DATA);
    return Data;
}

void XLoop_uhat_sparse_Set_tol(XLoop_uhat_sparse *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_TOL_DATA, (u32)(Data));
    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_TOL_DATA + 4, (u32)(Data >> 32));
}

u64 XLoop_uhat_sparse_Get_tol(XLoop_uhat_sparse *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_TOL_DATA);
    Data += (u64)XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_TOL_DATA + 4) << 32;
    return Data;
}

void XLoop_uhat_sparse_Set_L(XLoop_uhat_sparse *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_L_DATA, (u32)(Data));
    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_L_DATA + 4, (u32)(Data >> 32));
}

u64 XLoop_uhat_sparse_Get_L(XLoop_uhat_sparse *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_L_DATA);
    Data += (u64)XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_L_DATA + 4) << 32;
    return Data;
}

void XLoop_uhat_sparse_Set_L_exp(XLoop_uhat_sparse *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_L_EXP_DATA, (u32)(Data));
    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_L_EXP_DATA + 4, (u32)(Data >> 32));
}

u64 XLoop_uhat_sparse_Get_L_exp(XLoop_uhat_sparse *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_L_EXP_DATA);
    Data += (u64)XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_L_EXP_DATA + 4) << 32;
    return Data;
}

void XLoop_uhat_sparse_Set_uhat_i(XLoop_uhat_sparse *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_UHAT_I_DATA, (u32)(Data));
    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_UHAT_I_DATA + 4, (u32)(Data >> 32));
}

u64 XLoop_uhat_sparse_Get_uhat_i(XLoop_uhat_sparse *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_UHAT_I_DATA);
    Data += (u64)XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_UHAT_I_DATA + 4) << 32;
    return Data;
}

void XLoop_uhat_sparse_Set_R(XLoop_uhat_sparse *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_R_DATA, (u32)(Data));
    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_R_DATA + 4, (u32)(Data >> 32));
}

u64 XLoop_uhat_sparse_Get_R(XLoop_uhat_sparse *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_R_DATA);
    Data += (u64)XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_R_DATA + 4) << 32;
    return Data;
}

void XLoop_uhat_sparse_Set_R_exp(XLoop_uhat_sparse *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_R_EXP_DATA, (u32)(Data));
    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_R_EXP_DATA + 4, (u32)(Data >> 32));
}

u64 XLoop_uhat_sparse_Get_R_exp(XLoop_uhat_sparse *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_R_EXP_DATA);
    Data += (u64)XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_R_EXP_DATA + 4) << 32;
    return Data;
}

void XLoop_uhat_sparse_InterruptGlobalEnable(XLoop_uhat_sparse *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_GIE, 1);
}

void XLoop_uhat_sparse_InterruptGlobalDisable(XLoop_uhat_sparse *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_GIE, 0);
}

void XLoop_uhat_sparse_InterruptEnable(XLoop_uhat_sparse *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_IER);
    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_IER, Register | Mask);
}

void XLoop_uhat_sparse_InterruptDisable(XLoop_uhat_sparse *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_IER);
    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_IER, Register & (~Mask));
}

void XLoop_uhat_sparse_InterruptClear(XLoop_uhat_sparse *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XLoop_uhat_sparse_WriteReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_ISR, Mask);
}

u32 XLoop_uhat_sparse_InterruptGetEnabled(XLoop_uhat_sparse *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_IER);
}

u32 XLoop_uhat_sparse_InterruptGetStatus(XLoop_uhat_sparse *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XLoop_uhat_sparse_ReadReg(InstancePtr->Control_BaseAddress, XLOOP_UHAT_SPARSE_CONTROL_ADDR_ISR);
}

