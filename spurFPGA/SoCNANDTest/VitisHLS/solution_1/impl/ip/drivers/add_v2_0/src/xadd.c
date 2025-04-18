// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xadd.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XAdd_CfgInitialize(XAdd *InstancePtr, XAdd_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Crtls_BaseAddress = ConfigPtr->Crtls_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XAdd_Start(XAdd *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdd_ReadReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_AP_CTRL) & 0x80;
    XAdd_WriteReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_AP_CTRL, Data | 0x01);
}

u32 XAdd_IsDone(XAdd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdd_ReadReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XAdd_IsIdle(XAdd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdd_ReadReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XAdd_IsReady(XAdd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdd_ReadReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XAdd_EnableAutoRestart(XAdd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdd_WriteReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_AP_CTRL, 0x80);
}

void XAdd_DisableAutoRestart(XAdd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdd_WriteReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_AP_CTRL, 0);
}

u32 XAdd_Get_return(XAdd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdd_ReadReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_AP_RETURN);
    return Data;
}
void XAdd_Set_a(XAdd *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdd_WriteReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_A_DATA, Data);
}

u32 XAdd_Get_a(XAdd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdd_ReadReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_A_DATA);
    return Data;
}

void XAdd_Set_b(XAdd *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdd_WriteReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_B_DATA, Data);
}

u32 XAdd_Get_b(XAdd *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdd_ReadReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_B_DATA);
    return Data;
}

void XAdd_InterruptGlobalEnable(XAdd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdd_WriteReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_GIE, 1);
}

void XAdd_InterruptGlobalDisable(XAdd *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdd_WriteReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_GIE, 0);
}

void XAdd_InterruptEnable(XAdd *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XAdd_ReadReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_IER);
    XAdd_WriteReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_IER, Register | Mask);
}

void XAdd_InterruptDisable(XAdd *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XAdd_ReadReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_IER);
    XAdd_WriteReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_IER, Register & (~Mask));
}

void XAdd_InterruptClear(XAdd *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdd_WriteReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_ISR, Mask);
}

u32 XAdd_InterruptGetEnabled(XAdd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XAdd_ReadReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_IER);
}

u32 XAdd_InterruptGetStatus(XAdd *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XAdd_ReadReg(InstancePtr->Crtls_BaseAddress, XADD_CRTLS_ADDR_ISR);
}

