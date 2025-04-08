// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xloop_uhat_sparse.h"

extern XLoop_uhat_sparse_Config XLoop_uhat_sparse_ConfigTable[];

#ifdef SDT
XLoop_uhat_sparse_Config *XLoop_uhat_sparse_LookupConfig(UINTPTR BaseAddress) {
	XLoop_uhat_sparse_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XLoop_uhat_sparse_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XLoop_uhat_sparse_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XLoop_uhat_sparse_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XLoop_uhat_sparse_Initialize(XLoop_uhat_sparse *InstancePtr, UINTPTR BaseAddress) {
	XLoop_uhat_sparse_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XLoop_uhat_sparse_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XLoop_uhat_sparse_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XLoop_uhat_sparse_Config *XLoop_uhat_sparse_LookupConfig(u16 DeviceId) {
	XLoop_uhat_sparse_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XLOOP_UHAT_SPARSE_NUM_INSTANCES; Index++) {
		if (XLoop_uhat_sparse_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XLoop_uhat_sparse_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XLoop_uhat_sparse_Initialize(XLoop_uhat_sparse *InstancePtr, u16 DeviceId) {
	XLoop_uhat_sparse_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XLoop_uhat_sparse_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XLoop_uhat_sparse_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

