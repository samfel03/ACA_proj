// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
// control
// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of L
//        bit 31~0 - L[31:0] (Read/Write)
// 0x14 : Data signal of L
//        bit 31~0 - L[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of uhat_i
//        bit 31~0 - uhat_i[31:0] (Read/Write)
// 0x20 : Data signal of uhat_i
//        bit 31~0 - uhat_i[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of R
//        bit 31~0 - R[31:0] (Read/Write)
// 0x2c : Data signal of R
//        bit 31~0 - R[63:32] (Read/Write)
// 0x30 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_L_DATA      0x10
#define XLOOP_UHAT_SPARSE_CONTROL_BITS_L_DATA      64
#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_UHAT_I_DATA 0x1c
#define XLOOP_UHAT_SPARSE_CONTROL_BITS_UHAT_I_DATA 64
#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_R_DATA      0x28
#define XLOOP_UHAT_SPARSE_CONTROL_BITS_R_DATA      64

