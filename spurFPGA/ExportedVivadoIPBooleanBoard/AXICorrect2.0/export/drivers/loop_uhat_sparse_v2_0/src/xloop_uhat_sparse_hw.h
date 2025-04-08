// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
// control
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
// 0x10 : Data signal of rowStart
//        bit 31~0 - rowStart[31:0] (Read/Write)
// 0x14 : Data signal of rowStart
//        bit 31~0 - rowStart[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of colIndex
//        bit 31~0 - colIndex[31:0] (Read/Write)
// 0x20 : Data signal of colIndex
//        bit 31~0 - colIndex[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of value_r
//        bit 31~0 - value_r[31:0] (Read/Write)
// 0x2c : Data signal of value_r
//        bit 31~0 - value_r[63:32] (Read/Write)
// 0x30 : reserved
// 0x34 : Data signal of ELEMENTS
//        bit 31~0 - ELEMENTS[31:0] (Read/Write)
// 0x38 : reserved
// 0x3c : Data signal of tol
//        bit 31~0 - tol[31:0] (Read/Write)
// 0x40 : Data signal of tol
//        bit 31~0 - tol[63:32] (Read/Write)
// 0x44 : reserved
// 0x48 : Data signal of L
//        bit 31~0 - L[31:0] (Read/Write)
// 0x4c : Data signal of L
//        bit 31~0 - L[63:32] (Read/Write)
// 0x50 : reserved
// 0x54 : Data signal of L_exp
//        bit 31~0 - L_exp[31:0] (Read/Write)
// 0x58 : Data signal of L_exp
//        bit 31~0 - L_exp[63:32] (Read/Write)
// 0x5c : reserved
// 0x60 : Data signal of uhat_i
//        bit 31~0 - uhat_i[31:0] (Read/Write)
// 0x64 : Data signal of uhat_i
//        bit 31~0 - uhat_i[63:32] (Read/Write)
// 0x68 : reserved
// 0x6c : Data signal of R
//        bit 31~0 - R[31:0] (Read/Write)
// 0x70 : Data signal of R
//        bit 31~0 - R[63:32] (Read/Write)
// 0x74 : reserved
// 0x78 : Data signal of R_exp
//        bit 31~0 - R_exp[31:0] (Read/Write)
// 0x7c : Data signal of R_exp
//        bit 31~0 - R_exp[63:32] (Read/Write)
// 0x80 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_AP_CTRL       0x00
#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_GIE           0x04
#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_IER           0x08
#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_ISR           0x0c
#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_ROWSTART_DATA 0x10
#define XLOOP_UHAT_SPARSE_CONTROL_BITS_ROWSTART_DATA 64
#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_COLINDEX_DATA 0x1c
#define XLOOP_UHAT_SPARSE_CONTROL_BITS_COLINDEX_DATA 64
#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_VALUE_R_DATA  0x28
#define XLOOP_UHAT_SPARSE_CONTROL_BITS_VALUE_R_DATA  64
#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_ELEMENTS_DATA 0x34
#define XLOOP_UHAT_SPARSE_CONTROL_BITS_ELEMENTS_DATA 32
#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_TOL_DATA      0x3c
#define XLOOP_UHAT_SPARSE_CONTROL_BITS_TOL_DATA      64
#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_L_DATA        0x48
#define XLOOP_UHAT_SPARSE_CONTROL_BITS_L_DATA        64
#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_L_EXP_DATA    0x54
#define XLOOP_UHAT_SPARSE_CONTROL_BITS_L_EXP_DATA    64
#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_UHAT_I_DATA   0x60
#define XLOOP_UHAT_SPARSE_CONTROL_BITS_UHAT_I_DATA   64
#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_R_DATA        0x6c
#define XLOOP_UHAT_SPARSE_CONTROL_BITS_R_DATA        64
#define XLOOP_UHAT_SPARSE_CONTROL_ADDR_R_EXP_DATA    0x78
#define XLOOP_UHAT_SPARSE_CONTROL_BITS_R_EXP_DATA    64

