; ModuleID = 'C:/Research/CU-Spur-Sean/spurFPGA/VitisHLS/sparsefpgaimp/loop_uhat_sparse_imp/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>" = type { %"struct.hls::axis<ap_int<64>, 0, 0, 0, '8', false>" }
%"struct.hls::axis<ap_int<64>, 0, 0, 0, '8', false>" = type { %"struct.ap_int<64>", %"struct.ap_uint<8>", %"struct.ap_uint<8>", %"class.std::ios_base::Init", %"struct.ap_uint<1>", %"class.std::ios_base::Init", %"class.std::ios_base::Init" }
%"struct.ap_int<64>" = type { %"struct.ap_int_base<64, true>" }
%"struct.ap_int_base<64, true>" = type { %"struct.ssdm_int<64, true>" }
%"struct.ssdm_int<64, true>" = type { i64 }
%"struct.ap_uint<8>" = type { %"struct.ap_int_base<8, false>" }
%"struct.ap_int_base<8, false>" = type { %"class.std::ios_base::Init" }
%"struct.ap_uint<1>" = type { %"struct.ap_int_base<1, false>" }
%"struct.ap_int_base<1, false>" = type { %"struct.ssdm_int<1, false>" }
%"struct.ssdm_int<1, false>" = type { i1 }
%"class.std::ios_base::Init" = type { i8 }

; Function Attrs: noinline willreturn
define void @apatb_loop_uhat_sparse_ir(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* noalias nonnull dereferenceable(16) %inStream, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* noalias nonnull dereferenceable(16) %outStream, i32 %ELEMENTS, double %tol, double %L_exp, double %R_exp) local_unnamed_addr #0 {
entry:
  %inStream_copy.data = alloca i64, align 512
  %inStream_copy.keep = alloca i8, align 512
  %inStream_copy.strb = alloca i8, align 512
  %inStream_copy.last = alloca i1, align 512
  %outStream_copy.data = alloca i64, align 512
  %outStream_copy.keep = alloca i8, align 512
  %outStream_copy.strb = alloca i8, align 512
  %outStream_copy.last = alloca i1, align 512
  call fastcc void @copy_in(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* nonnull %inStream, i64* nonnull align 512 %inStream_copy.data, i8* nonnull align 512 %inStream_copy.keep, i8* nonnull align 512 %inStream_copy.strb, i1* nonnull align 512 %inStream_copy.last, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* nonnull %outStream, i64* nonnull align 512 %outStream_copy.data, i8* nonnull align 512 %outStream_copy.keep, i8* nonnull align 512 %outStream_copy.strb, i1* nonnull align 512 %outStream_copy.last)
  call void @apatb_loop_uhat_sparse_hw(i64* %inStream_copy.data, i8* %inStream_copy.keep, i8* %inStream_copy.strb, i1* %inStream_copy.last, i64* %outStream_copy.data, i8* %outStream_copy.keep, i8* %outStream_copy.strb, i1* %outStream_copy.last, i32 %ELEMENTS, double %tol, double %L_exp, double %R_exp)
  call void @copy_back(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %inStream, i64* %inStream_copy.data, i8* %inStream_copy.keep, i8* %inStream_copy.strb, i1* %inStream_copy.last, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %outStream, i64* %outStream_copy.data, i8* %outStream_copy.keep, i8* %outStream_copy.strb, i1* %outStream_copy.last)
  ret void
}

; Function Attrs: argmemonly noinline willreturn
define internal fastcc void @copy_in(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* noalias, i64* noalias align 512 "unpacked"="1.0" %_V_data_V, i8* noalias align 512 "unpacked"="1.1" %_V_keep_V, i8* noalias align 512 "unpacked"="1.2" %_V_strb_V, i1* noalias align 512 "unpacked"="1.3" %_V_last_V, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* noalias, i64* noalias align 512 "unpacked"="3.0" %_V_data_V1, i8* noalias align 512 "unpacked"="3.1" %_V_keep_V2, i8* noalias align 512 "unpacked"="3.2" %_V_strb_V3, i1* noalias align 512 "unpacked"="3.3" %_V_last_V4) unnamed_addr #1 {
entry:
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>.180"(i64* align 512 %_V_data_V, i8* align 512 %_V_keep_V, i8* align 512 %_V_strb_V, i1* align 512 %_V_last_V, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %0)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>.180"(i64* align 512 %_V_data_V1, i8* align 512 %_V_keep_V2, i8* align 512 %_V_strb_V3, i1* align 512 %_V_last_V4, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %1)
  ret void
}

; Function Attrs: argmemonly noinline willreturn
define internal fastcc void @copy_out(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* noalias, i64* noalias align 512 "unpacked"="1.0" %_V_data_V, i8* noalias align 512 "unpacked"="1.1" %_V_keep_V, i8* noalias align 512 "unpacked"="1.2" %_V_strb_V, i1* noalias align 512 "unpacked"="1.3" %_V_last_V, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* noalias, i64* noalias align 512 "unpacked"="3.0" %_V_data_V1, i8* noalias align 512 "unpacked"="3.1" %_V_keep_V2, i8* noalias align 512 "unpacked"="3.2" %_V_strb_V3, i1* noalias align 512 "unpacked"="3.3" %_V_last_V4) unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %0, i64* align 512 %_V_data_V, i8* align 512 %_V_keep_V, i8* align 512 %_V_strb_V, i1* align 512 %_V_last_V)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %1, i64* align 512 %_V_data_V1, i8* align 512 %_V_keep_V2, i8* align 512 %_V_strb_V3, i1* align 512 %_V_last_V4)
  ret void
}

; Function Attrs: argmemonly noinline willreturn
define internal fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* noalias %dst, i64* noalias align 512 "unpacked"="1.0" %src_V_data_V, i8* noalias align 512 "unpacked"="1.1" %src_V_keep_V, i8* noalias align 512 "unpacked"="1.2" %src_V_strb_V, i1* noalias align 512 "unpacked"="1.3" %src_V_last_V) unnamed_addr #3 {
entry:
  %0 = icmp eq %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %dst, null
  br i1 %0, label %ret, label %copy

copy:                                             ; preds = %entry
  call fastcc void @"streamcpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>.175"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* nonnull %dst, i64* align 512 %src_V_data_V, i8* align 512 %src_V_keep_V, i8* align 512 %src_V_strb_V, i1* align 512 %src_V_last_V)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline willreturn
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>.175"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* noalias nocapture, i64* noalias nocapture align 512 "unpacked"="1.0" %_V_data_V, i8* noalias nocapture align 512 "unpacked"="1.1" %_V_keep_V, i8* noalias nocapture align 512 "unpacked"="1.2" %_V_strb_V, i1* noalias nocapture align 512 "unpacked"="1.3" %_V_last_V) unnamed_addr #4 {
entry:
  %1 = alloca i64
  %2 = alloca i8
  %3 = alloca i8
  %4 = alloca i1
  %5 = alloca %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"
  br label %empty

empty:                                            ; preds = %push, %entry
  %6 = bitcast i64* %_V_data_V to i8*
  %7 = call i1 @fpga_fifo_not_empty_8(i8* %6)
  br i1 %7, label %push, label %ret

push:                                             ; preds = %empty
  %8 = bitcast i64* %1 to i8*
  %9 = bitcast i64* %_V_data_V to i8*
  call void @fpga_fifo_pop_8(i8* %8, i8* %9)
  %10 = load volatile i64, i64* %1
  call void @fpga_fifo_pop_1(i8* %3, i8* %_V_keep_V)
  %11 = load volatile i8, i8* %3
  call void @fpga_fifo_pop_1(i8* %2, i8* %_V_strb_V)
  %12 = load volatile i8, i8* %2
  %13 = bitcast i1* %4 to i8*
  %14 = bitcast i1* %_V_last_V to i8*
  call void @fpga_fifo_pop_1(i8* %13, i8* %14)
  %15 = bitcast i1* %4 to i8*
  %16 = load i8, i8* %15
  %17 = trunc i8 %16 to i1
  %.fca.0.0.0.0.0.insert = insertvalue %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>" undef, i64 %10, 0, 0, 0, 0, 0
  %.fca.0.1.0.0.0.insert = insertvalue %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>" %.fca.0.0.0.0.0.insert, i8 %11, 0, 1, 0, 0, 0
  %.fca.0.2.0.0.0.insert = insertvalue %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>" %.fca.0.1.0.0.0.insert, i8 %12, 0, 2, 0, 0, 0
  %.fca.0.4.0.0.0.insert = insertvalue %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>" %.fca.0.2.0.0.0.insert, i1 %17, 0, 4, 0, 0, 0
  store %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>" %.fca.0.4.0.0.0.insert, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %5
  %18 = bitcast %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %5 to i8*
  %19 = bitcast %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %0 to i8*
  call void @fpga_fifo_push_16(i8* %18, i8* %19)
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: argmemonly noinline willreturn
define internal fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>.180"(i64* noalias align 512 "unpacked"="0.0" %dst_V_data_V, i8* noalias align 512 "unpacked"="0.1" %dst_V_keep_V, i8* noalias align 512 "unpacked"="0.2" %dst_V_strb_V, i1* noalias align 512 "unpacked"="0.3" %dst_V_last_V, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* noalias %src) unnamed_addr #3 {
entry:
  %0 = icmp eq %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %src, null
  br i1 %0, label %ret, label %copy

copy:                                             ; preds = %entry
  call fastcc void @"streamcpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>.183"(i64* align 512 %dst_V_data_V, i8* align 512 %dst_V_keep_V, i8* align 512 %dst_V_strb_V, i1* align 512 %dst_V_last_V, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* nonnull %src)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline willreturn
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>.183"(i64* noalias nocapture align 512 "unpacked"="0.0" %_V_data_V, i8* noalias nocapture align 512 "unpacked"="0.1" %_V_keep_V, i8* noalias nocapture align 512 "unpacked"="0.2" %_V_strb_V, i1* noalias nocapture align 512 "unpacked"="0.3" %_V_last_V, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* noalias nocapture) unnamed_addr #4 {
entry:
  %1 = alloca %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"
  %2 = alloca i64
  %3 = alloca i8
  %4 = alloca i8
  %5 = alloca i1
  br label %empty

empty:                                            ; preds = %push, %entry
  %6 = bitcast %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %0 to i8*
  %7 = call i1 @fpga_fifo_not_empty_16(i8* %6)
  br i1 %7, label %push, label %ret

push:                                             ; preds = %empty
  %8 = bitcast %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %1 to i8*
  %9 = bitcast %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %0 to i8*
  call void @fpga_fifo_pop_16(i8* %8, i8* %9)
  %10 = load volatile %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>", %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %1
  %.fca.0.0.0.0.0.extract = extractvalue %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>" %10, 0, 0, 0, 0, 0
  %.fca.0.1.0.0.0.extract = extractvalue %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>" %10, 0, 1, 0, 0, 0
  %.fca.0.2.0.0.0.extract = extractvalue %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>" %10, 0, 2, 0, 0, 0
  %.fca.0.4.0.0.0.extract = extractvalue %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>" %10, 0, 4, 0, 0, 0
  store i64 %.fca.0.0.0.0.0.extract, i64* %2
  %11 = bitcast i64* %2 to i8*
  %12 = bitcast i64* %_V_data_V to i8*
  call void @fpga_fifo_push_8(i8* %11, i8* %12)
  store i8 %.fca.0.1.0.0.0.extract, i8* %4
  call void @fpga_fifo_push_1(i8* %4, i8* %_V_keep_V)
  store i8 %.fca.0.2.0.0.0.extract, i8* %3
  call void @fpga_fifo_push_1(i8* %3, i8* %_V_strb_V)
  store i1 %.fca.0.4.0.0.0.extract, i1* %5
  %13 = bitcast i1* %5 to i8*
  %14 = bitcast i1* %_V_last_V to i8*
  call void @fpga_fifo_push_1(i8* %13, i8* %14)
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  ret void
}

declare void @apatb_loop_uhat_sparse_hw(i64*, i8*, i8*, i1*, i64*, i8*, i8*, i1*, i32, double, double, double)

; Function Attrs: argmemonly noinline willreturn
define internal fastcc void @copy_back(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* noalias, i64* noalias align 512 "unpacked"="1.0" %_V_data_V, i8* noalias align 512 "unpacked"="1.1" %_V_keep_V, i8* noalias align 512 "unpacked"="1.2" %_V_strb_V, i1* noalias align 512 "unpacked"="1.3" %_V_last_V, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* noalias, i64* noalias align 512 "unpacked"="3.0" %_V_data_V1, i8* noalias align 512 "unpacked"="3.1" %_V_keep_V2, i8* noalias align 512 "unpacked"="3.2" %_V_strb_V3, i1* noalias align 512 "unpacked"="3.3" %_V_last_V4) unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %0, i64* align 512 %_V_data_V, i8* align 512 %_V_keep_V, i8* align 512 %_V_strb_V, i1* align 512 %_V_last_V)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %1, i64* align 512 %_V_data_V1, i8* align 512 %_V_keep_V2, i8* align 512 %_V_strb_V3, i1* align 512 %_V_last_V4)
  ret void
}

define void @loop_uhat_sparse_hw_stub_wrapper(i64*, i8*, i8*, i1*, i64*, i8*, i8*, i1*, i32, double, double, double) #5 {
entry:
  %12 = alloca %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"
  %13 = alloca %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"
  call void @copy_out(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %12, i64* %0, i8* %1, i8* %2, i1* %3, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %13, i64* %4, i8* %5, i8* %6, i1* %7)
  call void @loop_uhat_sparse_hw_stub(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %12, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %13, i32 %8, double %9, double %10, double %11)
  call void @copy_in(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %12, i64* %0, i8* %1, i8* %2, i1* %3, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"* %13, i64* %4, i8* %5, i8* %6, i1* %7)
  ret void
}

declare void @loop_uhat_sparse_hw_stub(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"*, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0, '8', false>, 0>"*, i32, double, double, double)

declare i1 @fpga_fifo_not_empty_16(i8*)

declare i1 @fpga_fifo_not_empty_8(i8*)

declare void @fpga_fifo_pop_16(i8*, i8*)

declare void @fpga_fifo_pop_8(i8*, i8*)

declare void @fpga_fifo_pop_1(i8*, i8*)

declare void @fpga_fifo_push_16(i8*, i8*)

declare void @fpga_fifo_push_8(i8*, i8*)

declare void @fpga_fifo_push_1(i8*, i8*)

attributes #0 = { noinline willreturn "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline willreturn "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline willreturn "fpga.wrapper.func"="copyout" }
attributes #3 = { argmemonly noinline willreturn "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #4 = { argmemonly noinline willreturn "fpga.wrapper.func"="streamcpy_hls" }
attributes #5 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.rotate.disable"}
