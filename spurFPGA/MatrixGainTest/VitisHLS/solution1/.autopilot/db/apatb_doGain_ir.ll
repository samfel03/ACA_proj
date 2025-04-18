; ModuleID = 'C:/Research/CU-Spur-Sean/spurFPGA/MatrixGainTest/VitisHLS/solution1/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>" = type { %"struct.hls::axis<ap_int<32>, 2, 5, 6, '8', false>" }
%"struct.hls::axis<ap_int<32>, 2, 5, 6, '8', false>" = type { %"struct.ap_int<32>", %"struct.ap_uint<4>", %"struct.ap_uint<4>", %"struct.ap_uint<2>", %"struct.ap_uint<1>", %"struct.ap_uint<5>", %"struct.ap_uint<6>" }
%"struct.ap_int<32>" = type { %"struct.ap_int_base<32, true>" }
%"struct.ap_int_base<32, true>" = type { %"struct.ssdm_int<32, true>" }
%"struct.ssdm_int<32, true>" = type { i32 }
%"struct.ap_uint<4>" = type { %"struct.ap_int_base<4, false>" }
%"struct.ap_int_base<4, false>" = type { %"struct.ssdm_int<4, false>" }
%"struct.ssdm_int<4, false>" = type { i4 }
%"struct.ap_uint<2>" = type { %"struct.ap_int_base<2, false>" }
%"struct.ap_int_base<2, false>" = type { %"struct.ssdm_int<2, false>" }
%"struct.ssdm_int<2, false>" = type { i2 }
%"struct.ap_uint<1>" = type { %"struct.ap_int_base<1, false>" }
%"struct.ap_int_base<1, false>" = type { %"struct.ssdm_int<1, false>" }
%"struct.ssdm_int<1, false>" = type { i1 }
%"struct.ap_uint<5>" = type { %"struct.ap_int_base<5, false>" }
%"struct.ap_int_base<5, false>" = type { %"struct.ssdm_int<5, false>" }
%"struct.ssdm_int<5, false>" = type { i5 }
%"struct.ap_uint<6>" = type { %"struct.ap_int_base<6, false>" }
%"struct.ap_int_base<6, false>" = type { %"struct.ssdm_int<6, false>" }
%"struct.ssdm_int<6, false>" = type { i6 }

; Function Attrs: inaccessiblemem_or_argmemonly noinline willreturn
define void @apatb_doGain_ir(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* noalias nonnull dereferenceable(12) %inStream, %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* noalias nonnull dereferenceable(12) %outStream, i32 %gain) local_unnamed_addr #0 {
entry:
  %inStream_copy.data = alloca i32, align 512
  %inStream_copy.keep = alloca i4, align 512
  %inStream_copy.strb = alloca i4, align 512
  %inStream_copy.user = alloca i2, align 512
  %inStream_copy.last = alloca i1, align 512
  %inStream_copy.id = alloca i5, align 512
  %inStream_copy.dest = alloca i6, align 512
  %outStream_copy.data = alloca i32, align 512
  %outStream_copy.keep = alloca i4, align 512
  %outStream_copy.strb = alloca i4, align 512
  %outStream_copy.user = alloca i2, align 512
  %outStream_copy.last = alloca i1, align 512
  %outStream_copy.id = alloca i5, align 512
  %outStream_copy.dest = alloca i6, align 512
  call fastcc void @copy_in(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* nonnull %inStream, i32* nonnull align 512 %inStream_copy.data, i4* nonnull align 512 %inStream_copy.keep, i4* nonnull align 512 %inStream_copy.strb, i2* nonnull align 512 %inStream_copy.user, i1* nonnull align 512 %inStream_copy.last, i5* nonnull align 512 %inStream_copy.id, i6* nonnull align 512 %inStream_copy.dest, %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* nonnull %outStream, i32* nonnull align 512 %outStream_copy.data, i4* nonnull align 512 %outStream_copy.keep, i4* nonnull align 512 %outStream_copy.strb, i2* nonnull align 512 %outStream_copy.user, i1* nonnull align 512 %outStream_copy.last, i5* nonnull align 512 %outStream_copy.id, i6* nonnull align 512 %outStream_copy.dest)
  call void @apatb_doGain_hw(i32* %inStream_copy.data, i4* %inStream_copy.keep, i4* %inStream_copy.strb, i2* %inStream_copy.user, i1* %inStream_copy.last, i5* %inStream_copy.id, i6* %inStream_copy.dest, i32* %outStream_copy.data, i4* %outStream_copy.keep, i4* %outStream_copy.strb, i2* %outStream_copy.user, i1* %outStream_copy.last, i5* %outStream_copy.id, i6* %outStream_copy.dest, i32 %gain)
  call void @copy_back(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %inStream, i32* %inStream_copy.data, i4* %inStream_copy.keep, i4* %inStream_copy.strb, i2* %inStream_copy.user, i1* %inStream_copy.last, i5* %inStream_copy.id, i6* %inStream_copy.dest, %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %outStream, i32* %outStream_copy.data, i4* %outStream_copy.keep, i4* %outStream_copy.strb, i2* %outStream_copy.user, i1* %outStream_copy.last, i5* %outStream_copy.id, i6* %outStream_copy.dest)
  ret void
}

; Function Attrs: argmemonly noinline willreturn
define internal fastcc void @copy_in(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* noalias, i32* noalias align 512 "unpacked"="1.0" %_V_data_V, i4* noalias align 512 "unpacked"="1.1" %_V_keep_V, i4* noalias align 512 "unpacked"="1.2" %_V_strb_V, i2* noalias align 512 "unpacked"="1.3" %_V_user_V, i1* noalias align 512 "unpacked"="1.4" %_V_last_V, i5* noalias align 512 "unpacked"="1.5" %_V_id_V, i6* noalias align 512 "unpacked"="1.6" %_V_dest_V, %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* noalias, i32* noalias align 512 "unpacked"="3.0" %_V_data_V1, i4* noalias align 512 "unpacked"="3.1" %_V_keep_V2, i4* noalias align 512 "unpacked"="3.2" %_V_strb_V3, i2* noalias align 512 "unpacked"="3.3" %_V_user_V4, i1* noalias align 512 "unpacked"="3.4" %_V_last_V5, i5* noalias align 512 "unpacked"="3.5" %_V_id_V6, i6* noalias align 512 "unpacked"="3.6" %_V_dest_V7) unnamed_addr #1 {
entry:
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>.12"(i32* align 512 %_V_data_V, i4* align 512 %_V_keep_V, i4* align 512 %_V_strb_V, i2* align 512 %_V_user_V, i1* align 512 %_V_last_V, i5* align 512 %_V_id_V, i6* align 512 %_V_dest_V, %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %0)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>.12"(i32* align 512 %_V_data_V1, i4* align 512 %_V_keep_V2, i4* align 512 %_V_strb_V3, i2* align 512 %_V_user_V4, i1* align 512 %_V_last_V5, i5* align 512 %_V_id_V6, i6* align 512 %_V_dest_V7, %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %1)
  ret void
}

; Function Attrs: argmemonly noinline willreturn
define internal fastcc void @copy_out(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* noalias, i32* noalias align 512 "unpacked"="1.0" %_V_data_V, i4* noalias align 512 "unpacked"="1.1" %_V_keep_V, i4* noalias align 512 "unpacked"="1.2" %_V_strb_V, i2* noalias align 512 "unpacked"="1.3" %_V_user_V, i1* noalias align 512 "unpacked"="1.4" %_V_last_V, i5* noalias align 512 "unpacked"="1.5" %_V_id_V, i6* noalias align 512 "unpacked"="1.6" %_V_dest_V, %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* noalias, i32* noalias align 512 "unpacked"="3.0" %_V_data_V1, i4* noalias align 512 "unpacked"="3.1" %_V_keep_V2, i4* noalias align 512 "unpacked"="3.2" %_V_strb_V3, i2* noalias align 512 "unpacked"="3.3" %_V_user_V4, i1* noalias align 512 "unpacked"="3.4" %_V_last_V5, i5* noalias align 512 "unpacked"="3.5" %_V_id_V6, i6* noalias align 512 "unpacked"="3.6" %_V_dest_V7) unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %0, i32* align 512 %_V_data_V, i4* align 512 %_V_keep_V, i4* align 512 %_V_strb_V, i2* align 512 %_V_user_V, i1* align 512 %_V_last_V, i5* align 512 %_V_id_V, i6* align 512 %_V_dest_V)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %1, i32* align 512 %_V_data_V1, i4* align 512 %_V_keep_V2, i4* align 512 %_V_strb_V3, i2* align 512 %_V_user_V4, i1* align 512 %_V_last_V5, i5* align 512 %_V_id_V6, i6* align 512 %_V_dest_V7)
  ret void
}

; Function Attrs: argmemonly noinline willreturn
define internal fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* noalias %dst, i32* noalias align 512 "unpacked"="1.0" %src_V_data_V, i4* noalias align 512 "unpacked"="1.1" %src_V_keep_V, i4* noalias align 512 "unpacked"="1.2" %src_V_strb_V, i2* noalias align 512 "unpacked"="1.3" %src_V_user_V, i1* noalias align 512 "unpacked"="1.4" %src_V_last_V, i5* noalias align 512 "unpacked"="1.5" %src_V_id_V, i6* noalias align 512 "unpacked"="1.6" %src_V_dest_V) unnamed_addr #3 {
entry:
  %0 = icmp eq %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %dst, null
  br i1 %0, label %ret, label %copy

copy:                                             ; preds = %entry
  call fastcc void @"streamcpy_hls.p0class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>.7"(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* nonnull %dst, i32* align 512 %src_V_data_V, i4* align 512 %src_V_keep_V, i4* align 512 %src_V_strb_V, i2* align 512 %src_V_user_V, i1* align 512 %src_V_last_V, i5* align 512 %src_V_id_V, i6* align 512 %src_V_dest_V)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline willreturn
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>.7"(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* noalias nocapture, i32* noalias nocapture align 512 "unpacked"="1.0" %_V_data_V, i4* noalias nocapture align 512 "unpacked"="1.1" %_V_keep_V, i4* noalias nocapture align 512 "unpacked"="1.2" %_V_strb_V, i2* noalias nocapture align 512 "unpacked"="1.3" %_V_user_V, i1* noalias nocapture align 512 "unpacked"="1.4" %_V_last_V, i5* noalias nocapture align 512 "unpacked"="1.5" %_V_id_V, i6* noalias nocapture align 512 "unpacked"="1.6" %_V_dest_V) unnamed_addr #4 {
entry:
  %1 = alloca i32
  %2 = alloca i4
  %3 = alloca i4
  %4 = alloca i2
  %5 = alloca i1
  %6 = alloca i5
  %7 = alloca i6
  %8 = alloca %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"
  br label %empty

empty:                                            ; preds = %push, %entry
  %9 = bitcast i32* %_V_data_V to i8*
  %10 = call i1 @fpga_fifo_not_empty_4(i8* %9)
  br i1 %10, label %push, label %ret

push:                                             ; preds = %empty
  %11 = bitcast i32* %1 to i8*
  %12 = bitcast i32* %_V_data_V to i8*
  call void @fpga_fifo_pop_4(i8* %11, i8* %12)
  %13 = load volatile i32, i32* %1
  %14 = bitcast i4* %3 to i8*
  %15 = bitcast i4* %_V_keep_V to i8*
  call void @fpga_fifo_pop_1(i8* %14, i8* %15)
  %16 = bitcast i4* %3 to i8*
  %17 = load i8, i8* %16
  %18 = trunc i8 %17 to i4
  %19 = bitcast i4* %2 to i8*
  %20 = bitcast i4* %_V_strb_V to i8*
  call void @fpga_fifo_pop_1(i8* %19, i8* %20)
  %21 = bitcast i4* %2 to i8*
  %22 = load i8, i8* %21
  %23 = trunc i8 %22 to i4
  %24 = bitcast i2* %4 to i8*
  %25 = bitcast i2* %_V_user_V to i8*
  call void @fpga_fifo_pop_1(i8* %24, i8* %25)
  %26 = bitcast i2* %4 to i8*
  %27 = load i8, i8* %26
  %28 = trunc i8 %27 to i2
  %29 = bitcast i1* %5 to i8*
  %30 = bitcast i1* %_V_last_V to i8*
  call void @fpga_fifo_pop_1(i8* %29, i8* %30)
  %31 = bitcast i1* %5 to i8*
  %32 = load i8, i8* %31
  %33 = trunc i8 %32 to i1
  %34 = bitcast i5* %6 to i8*
  %35 = bitcast i5* %_V_id_V to i8*
  call void @fpga_fifo_pop_1(i8* %34, i8* %35)
  %36 = bitcast i5* %6 to i8*
  %37 = load i8, i8* %36
  %38 = trunc i8 %37 to i5
  %39 = bitcast i6* %7 to i8*
  %40 = bitcast i6* %_V_dest_V to i8*
  call void @fpga_fifo_pop_1(i8* %39, i8* %40)
  %41 = bitcast i6* %7 to i8*
  %42 = load i8, i8* %41
  %43 = trunc i8 %42 to i6
  %.fca.0.0.0.0.0.insert = insertvalue %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>" undef, i32 %13, 0, 0, 0, 0, 0
  %.fca.0.1.0.0.0.insert = insertvalue %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>" %.fca.0.0.0.0.0.insert, i4 %18, 0, 1, 0, 0, 0
  %.fca.0.2.0.0.0.insert = insertvalue %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>" %.fca.0.1.0.0.0.insert, i4 %23, 0, 2, 0, 0, 0
  %.fca.0.3.0.0.0.insert = insertvalue %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>" %.fca.0.2.0.0.0.insert, i2 %28, 0, 3, 0, 0, 0
  %.fca.0.4.0.0.0.insert = insertvalue %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>" %.fca.0.3.0.0.0.insert, i1 %33, 0, 4, 0, 0, 0
  %.fca.0.5.0.0.0.insert = insertvalue %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>" %.fca.0.4.0.0.0.insert, i5 %38, 0, 5, 0, 0, 0
  %.fca.0.6.0.0.0.insert = insertvalue %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>" %.fca.0.5.0.0.0.insert, i6 %43, 0, 6, 0, 0, 0
  store %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>" %.fca.0.6.0.0.0.insert, %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %8
  %44 = bitcast %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %8 to i8*
  %45 = bitcast %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %0 to i8*
  call void @fpga_fifo_push_12(i8* %44, i8* %45)
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: argmemonly noinline willreturn
define internal fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>.12"(i32* noalias align 512 "unpacked"="0.0" %dst_V_data_V, i4* noalias align 512 "unpacked"="0.1" %dst_V_keep_V, i4* noalias align 512 "unpacked"="0.2" %dst_V_strb_V, i2* noalias align 512 "unpacked"="0.3" %dst_V_user_V, i1* noalias align 512 "unpacked"="0.4" %dst_V_last_V, i5* noalias align 512 "unpacked"="0.5" %dst_V_id_V, i6* noalias align 512 "unpacked"="0.6" %dst_V_dest_V, %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* noalias %src) unnamed_addr #3 {
entry:
  %0 = icmp eq %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %src, null
  br i1 %0, label %ret, label %copy

copy:                                             ; preds = %entry
  call fastcc void @"streamcpy_hls.p0class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>.15"(i32* align 512 %dst_V_data_V, i4* align 512 %dst_V_keep_V, i4* align 512 %dst_V_strb_V, i2* align 512 %dst_V_user_V, i1* align 512 %dst_V_last_V, i5* align 512 %dst_V_id_V, i6* align 512 %dst_V_dest_V, %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* nonnull %src)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline willreturn
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>.15"(i32* noalias nocapture align 512 "unpacked"="0.0" %_V_data_V, i4* noalias nocapture align 512 "unpacked"="0.1" %_V_keep_V, i4* noalias nocapture align 512 "unpacked"="0.2" %_V_strb_V, i2* noalias nocapture align 512 "unpacked"="0.3" %_V_user_V, i1* noalias nocapture align 512 "unpacked"="0.4" %_V_last_V, i5* noalias nocapture align 512 "unpacked"="0.5" %_V_id_V, i6* noalias nocapture align 512 "unpacked"="0.6" %_V_dest_V, %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* noalias nocapture) unnamed_addr #4 {
entry:
  %1 = alloca %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"
  %2 = alloca i32
  %3 = alloca i4
  %4 = alloca i4
  %5 = alloca i2
  %6 = alloca i1
  %7 = alloca i5
  %8 = alloca i6
  br label %empty

empty:                                            ; preds = %push, %entry
  %9 = bitcast %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %0 to i8*
  %10 = call i1 @fpga_fifo_not_empty_12(i8* %9)
  br i1 %10, label %push, label %ret

push:                                             ; preds = %empty
  %11 = bitcast %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %1 to i8*
  %12 = bitcast %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %0 to i8*
  call void @fpga_fifo_pop_12(i8* %11, i8* %12)
  %13 = load volatile %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>", %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %1
  %.fca.0.0.0.0.0.extract = extractvalue %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>" %13, 0, 0, 0, 0, 0
  %.fca.0.1.0.0.0.extract = extractvalue %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>" %13, 0, 1, 0, 0, 0
  %.fca.0.2.0.0.0.extract = extractvalue %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>" %13, 0, 2, 0, 0, 0
  %.fca.0.3.0.0.0.extract = extractvalue %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>" %13, 0, 3, 0, 0, 0
  %.fca.0.4.0.0.0.extract = extractvalue %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>" %13, 0, 4, 0, 0, 0
  %.fca.0.5.0.0.0.extract = extractvalue %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>" %13, 0, 5, 0, 0, 0
  %.fca.0.6.0.0.0.extract = extractvalue %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>" %13, 0, 6, 0, 0, 0
  store i32 %.fca.0.0.0.0.0.extract, i32* %2
  %14 = bitcast i32* %2 to i8*
  %15 = bitcast i32* %_V_data_V to i8*
  call void @fpga_fifo_push_4(i8* %14, i8* %15)
  store i4 %.fca.0.1.0.0.0.extract, i4* %4
  %16 = bitcast i4* %4 to i8*
  %17 = bitcast i4* %_V_keep_V to i8*
  call void @fpga_fifo_push_1(i8* %16, i8* %17)
  store i4 %.fca.0.2.0.0.0.extract, i4* %3
  %18 = bitcast i4* %3 to i8*
  %19 = bitcast i4* %_V_strb_V to i8*
  call void @fpga_fifo_push_1(i8* %18, i8* %19)
  store i2 %.fca.0.3.0.0.0.extract, i2* %5
  %20 = bitcast i2* %5 to i8*
  %21 = bitcast i2* %_V_user_V to i8*
  call void @fpga_fifo_push_1(i8* %20, i8* %21)
  store i1 %.fca.0.4.0.0.0.extract, i1* %6
  %22 = bitcast i1* %6 to i8*
  %23 = bitcast i1* %_V_last_V to i8*
  call void @fpga_fifo_push_1(i8* %22, i8* %23)
  store i5 %.fca.0.5.0.0.0.extract, i5* %7
  %24 = bitcast i5* %7 to i8*
  %25 = bitcast i5* %_V_id_V to i8*
  call void @fpga_fifo_push_1(i8* %24, i8* %25)
  store i6 %.fca.0.6.0.0.0.extract, i6* %8
  %26 = bitcast i6* %8 to i8*
  %27 = bitcast i6* %_V_dest_V to i8*
  call void @fpga_fifo_push_1(i8* %26, i8* %27)
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  ret void
}

declare void @apatb_doGain_hw(i32*, i4*, i4*, i2*, i1*, i5*, i6*, i32*, i4*, i4*, i2*, i1*, i5*, i6*, i32)

; Function Attrs: argmemonly noinline willreturn
define internal fastcc void @copy_back(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* noalias, i32* noalias align 512 "unpacked"="1.0" %_V_data_V, i4* noalias align 512 "unpacked"="1.1" %_V_keep_V, i4* noalias align 512 "unpacked"="1.2" %_V_strb_V, i2* noalias align 512 "unpacked"="1.3" %_V_user_V, i1* noalias align 512 "unpacked"="1.4" %_V_last_V, i5* noalias align 512 "unpacked"="1.5" %_V_id_V, i6* noalias align 512 "unpacked"="1.6" %_V_dest_V, %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* noalias, i32* noalias align 512 "unpacked"="3.0" %_V_data_V1, i4* noalias align 512 "unpacked"="3.1" %_V_keep_V2, i4* noalias align 512 "unpacked"="3.2" %_V_strb_V3, i2* noalias align 512 "unpacked"="3.3" %_V_user_V4, i1* noalias align 512 "unpacked"="3.4" %_V_last_V5, i5* noalias align 512 "unpacked"="3.5" %_V_id_V6, i6* noalias align 512 "unpacked"="3.6" %_V_dest_V7) unnamed_addr #2 {
entry:
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %0, i32* align 512 %_V_data_V, i4* align 512 %_V_keep_V, i4* align 512 %_V_strb_V, i2* align 512 %_V_user_V, i1* align 512 %_V_last_V, i5* align 512 %_V_id_V, i6* align 512 %_V_dest_V)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %1, i32* align 512 %_V_data_V1, i4* align 512 %_V_keep_V2, i4* align 512 %_V_strb_V3, i2* align 512 %_V_user_V4, i1* align 512 %_V_last_V5, i5* align 512 %_V_id_V6, i6* align 512 %_V_dest_V7)
  ret void
}

define void @doGain_hw_stub_wrapper(i32*, i4*, i4*, i2*, i1*, i5*, i6*, i32*, i4*, i4*, i2*, i1*, i5*, i6*, i32) #5 {
entry:
  %15 = alloca %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"
  %16 = alloca %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"
  call void @copy_out(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %15, i32* %0, i4* %1, i4* %2, i2* %3, i1* %4, i5* %5, i6* %6, %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %16, i32* %7, i4* %8, i4* %9, i2* %10, i1* %11, i5* %12, i6* %13)
  call void @doGain_hw_stub(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %15, %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %16, i32 %14)
  call void @copy_in(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %15, i32* %0, i4* %1, i4* %2, i2* %3, i1* %4, i5* %5, i6* %6, %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"* %16, i32* %7, i4* %8, i4* %9, i2* %10, i1* %11, i5* %12, i6* %13)
  ret void
}

declare void @doGain_hw_stub(%"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"*, %"class.hls::stream<hls::axis<ap_int<32>, 2, 5, 6, '8', false>, 0>"*, i32)

declare i1 @fpga_fifo_not_empty_12(i8*)

declare i1 @fpga_fifo_not_empty_4(i8*)

declare void @fpga_fifo_pop_12(i8*, i8*)

declare void @fpga_fifo_pop_4(i8*, i8*)

declare void @fpga_fifo_pop_1(i8*, i8*)

declare void @fpga_fifo_push_12(i8*, i8*)

declare void @fpga_fifo_push_4(i8*, i8*)

declare void @fpga_fifo_push_1(i8*, i8*)

attributes #0 = { inaccessiblemem_or_argmemonly noinline willreturn "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline willreturn "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline willreturn "fpga.wrapper.func"="copyout" }
attributes #3 = { argmemonly noinline willreturn "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #4 = { argmemonly noinline willreturn "fpga.wrapper.func"="streamcpy_hls" }
attributes #5 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.rotate.disable"}
