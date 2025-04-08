; ModuleID = 'C:/Users/seank/Documents/Research/spurFPGA/sparsefpgaimp/loop_uhat_sparse_imp/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

; Function Attrs: argmemonly noinline willreturn
define void @apatb_loop_uhat_sparse_ir(i32* noalias nocapture nonnull readonly %rowStart, i32* noalias nocapture nonnull readonly %colIndex, double* noalias nocapture nonnull readonly %value, i32 %ELEMENTS, double %tol, double* noalias nocapture nonnull readonly %L, double %L_exp, double* noalias nocapture nonnull %uhat_i, double* noalias nocapture nonnull readonly %R, double %R_exp) local_unnamed_addr #0 {
entry:
  %rowStart_copy = alloca i32, align 512
  %colIndex_copy = alloca i32, align 512
  %value_copy = alloca double, align 512
  %L_copy = alloca double, align 512
  %uhat_i_copy = alloca double, align 512
  %R_copy = alloca double, align 512
  call fastcc void @copy_in(i32* nonnull %rowStart, i32* nonnull align 512 %rowStart_copy, i32* nonnull %colIndex, i32* nonnull align 512 %colIndex_copy, double* nonnull %value, double* nonnull align 512 %value_copy, double* nonnull %L, double* nonnull align 512 %L_copy, double* nonnull %uhat_i, double* nonnull align 512 %uhat_i_copy, double* nonnull %R, double* nonnull align 512 %R_copy)
  call void @apatb_loop_uhat_sparse_hw(i32* %rowStart_copy, i32* %colIndex_copy, double* %value_copy, i32 %ELEMENTS, double %tol, double* %L_copy, double %L_exp, double* %uhat_i_copy, double* %R_copy, double %R_exp)
  call void @copy_back(i32* %rowStart, i32* %rowStart_copy, i32* %colIndex, i32* %colIndex_copy, double* %value, double* %value_copy, double* %L, double* %L_copy, double* %uhat_i, double* %uhat_i_copy, double* %R, double* %R_copy)
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_in(i32* noalias readonly, i32* noalias align 512, i32* noalias readonly, i32* noalias align 512, double* noalias readonly, double* noalias align 512, double* noalias readonly, double* noalias align 512, double* noalias readonly, double* noalias align 512, double* noalias readonly, double* noalias align 512) unnamed_addr #1 {
entry:
  call fastcc void @onebyonecpy_hls.p0i32(i32* align 512 %1, i32* %0)
  call fastcc void @onebyonecpy_hls.p0i32(i32* align 512 %3, i32* %2)
  call fastcc void @onebyonecpy_hls.p0f64(double* align 512 %5, double* %4)
  call fastcc void @onebyonecpy_hls.p0f64(double* align 512 %7, double* %6)
  call fastcc void @onebyonecpy_hls.p0f64(double* align 512 %9, double* %8)
  call fastcc void @onebyonecpy_hls.p0f64(double* align 512 %11, double* %10)
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @onebyonecpy_hls.p0i32(i32* noalias align 512 %dst, i32* noalias readonly %src) unnamed_addr #2 {
entry:
  %0 = icmp eq i32* %dst, null
  %1 = icmp eq i32* %src, null
  %2 = or i1 %0, %1
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %3 = load i32, i32* %src, align 4
  store i32 %3, i32* %dst, align 512
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @onebyonecpy_hls.p0f64(double* noalias align 512 %dst, double* noalias readonly %src) unnamed_addr #2 {
entry:
  %0 = icmp eq double* %dst, null
  %1 = icmp eq double* %src, null
  %2 = or i1 %0, %1
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %3 = load double, double* %src, align 8
  store double %3, double* %dst, align 512
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_out(i32* noalias, i32* noalias readonly align 512, i32* noalias, i32* noalias readonly align 512, double* noalias, double* noalias readonly align 512, double* noalias, double* noalias readonly align 512, double* noalias, double* noalias readonly align 512, double* noalias, double* noalias readonly align 512) unnamed_addr #3 {
entry:
  call fastcc void @onebyonecpy_hls.p0i32(i32* %0, i32* align 512 %1)
  call fastcc void @onebyonecpy_hls.p0i32(i32* %2, i32* align 512 %3)
  call fastcc void @onebyonecpy_hls.p0f64(double* %4, double* align 512 %5)
  call fastcc void @onebyonecpy_hls.p0f64(double* %6, double* align 512 %7)
  call fastcc void @onebyonecpy_hls.p0f64(double* %8, double* align 512 %9)
  call fastcc void @onebyonecpy_hls.p0f64(double* %10, double* align 512 %11)
  ret void
}

declare void @apatb_loop_uhat_sparse_hw(i32*, i32*, double*, i32, double, double*, double, double*, double*, double)

; Function Attrs: argmemonly noinline norecurse willreturn
define internal fastcc void @copy_back(i32* noalias, i32* noalias readonly align 512, i32* noalias, i32* noalias readonly align 512, double* noalias, double* noalias readonly align 512, double* noalias, double* noalias readonly align 512, double* noalias, double* noalias readonly align 512, double* noalias, double* noalias readonly align 512) unnamed_addr #3 {
entry:
  call fastcc void @onebyonecpy_hls.p0f64(double* %8, double* align 512 %9)
  ret void
}

define void @loop_uhat_sparse_hw_stub_wrapper(i32*, i32*, double*, i32, double, double*, double, double*, double*, double) #4 {
entry:
  call void @copy_out(i32* null, i32* %0, i32* null, i32* %1, double* null, double* %2, double* null, double* %5, double* null, double* %7, double* null, double* %8)
  call void @loop_uhat_sparse_hw_stub(i32* %0, i32* %1, double* %2, i32 %3, double %4, double* %5, double %6, double* %7, double* %8, double %9)
  call void @copy_in(i32* null, i32* %0, i32* null, i32* %1, double* null, double* %2, double* null, double* %5, double* null, double* %7, double* null, double* %8)
  ret void
}

declare void @loop_uhat_sparse_hw_stub(i32*, i32*, double*, i32, double, double*, double, double*, double*, double)

attributes #0 = { argmemonly noinline willreturn "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #3 = { argmemonly noinline norecurse willreturn "fpga.wrapper.func"="copyout" }
attributes #4 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
