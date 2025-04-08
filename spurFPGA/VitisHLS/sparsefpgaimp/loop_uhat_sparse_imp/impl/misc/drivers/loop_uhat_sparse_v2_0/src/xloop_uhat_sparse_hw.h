// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
// CTRL_BUS
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read/COR)
//        bit 7  - auto_restart (Read/Write)
//        bit 9  - interrupt (Read)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0 - enable ap_done interrupt (Read/Write)
//        bit 1 - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0 - ap_done (Read/TOW)
//        bit 1 - ap_ready (Read/TOW)
//        others - reserved
// 0x10 : Data signal of ELEMENTS
//        bit 31~0 - ELEMENTS[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of tol
//        bit 31~0 - tol[31:0] (Read/Write)
// 0x1c : Data signal of tol
//        bit 31~0 - tol[63:32] (Read/Write)
// 0x20 : reserved
// 0x24 : Data signal of L_exp
//        bit 31~0 - L_exp[31:0] (Read/Write)
// 0x28 : Data signal of L_exp
//        bit 31~0 - L_exp[63:32] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of R_exp
//        bit 31~0 - R_exp[31:0] (Read/Write)
// 0x34 : Data signal of R_exp
//        bit 31~0 - R_exp[63:32] (Read/Write)
// 0x38 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XLOOP_UHAT_SPARSE_CTRL_BUS_ADDR_AP_CTRL       0x00
#define XLOOP_UHAT_SPARSE_CTRL_BUS_ADDR_GIE           0x04
#define XLOOP_UHAT_SPARSE_CTRL_BUS_ADDR_IER           0x08
#define XLOOP_UHAT_SPARSE_CTRL_BUS_ADDR_ISR           0x0c
#define XLOOP_UHAT_SPARSE_CTRL_BUS_ADDR_ELEMENTS_DATA 0x10
#define XLOOP_UHAT_SPARSE_CTRL_BUS_BITS_ELEMENTS_DATA 32
#define XLOOP_UHAT_SPARSE_CTRL_BUS_ADDR_TOL_DATA      0x18
#define XLOOP_UHAT_SPARSE_CTRL_BUS_BITS_TOL_DATA      64
#define XLOOP_UHAT_SPARSE_CTRL_BUS_ADDR_L_EXP_DATA    0x24
#define XLOOP_UHAT_SPARSE_CTRL_BUS_BITS_L_EXP_DATA    64
#define XLOOP_UHAT_SPARSE_CTRL_BUS_ADDR_R_EXP_DATA    0x30
#define XLOOP_UHAT_SPARSE_CTRL_BUS_BITS_R_EXP_DATA    64

