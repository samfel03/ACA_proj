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

