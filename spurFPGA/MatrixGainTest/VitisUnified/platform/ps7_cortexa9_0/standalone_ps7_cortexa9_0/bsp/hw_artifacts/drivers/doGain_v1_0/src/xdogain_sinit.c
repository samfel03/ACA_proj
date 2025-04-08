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
#include "xdogain.h"

extern XDogain_Config XDogain_ConfigTable[];

#ifdef SDT
XDogain_Config *XDogain_LookupConfig(UINTPTR BaseAddress) {
	XDogain_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XDogain_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XDogain_ConfigTable[Index].Ctrl_bus_BaseAddress == BaseAddress) {
			ConfigPtr = &XDogain_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XDogain_Initialize(XDogain *InstancePtr, UINTPTR BaseAddress) {
	XDogain_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XDogain_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XDogain_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XDogain_Config *XDogain_LookupConfig(u16 DeviceId) {
	XDogain_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XDOGAIN_NUM_INSTANCES; Index++) {
		if (XDogain_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XDogain_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XDogain_Initialize(XDogain *InstancePtr, u16 DeviceId) {
	XDogain_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XDogain_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XDogain_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

