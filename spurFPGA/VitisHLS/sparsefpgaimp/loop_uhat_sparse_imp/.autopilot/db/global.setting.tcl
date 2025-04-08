
set TopModule "loop_uhat_sparse"
set ClockPeriod 10
set ClockList ap_clk
set HasVivadoClockPeriod 1
set CombLogicFlag 0
set PipelineFlag 0
set DataflowTaskPipelineFlag 1
set TrivialPipelineFlag 0
set noPortSwitchingFlag 0
set FloatingPointFlag 1
set FftOrFirFlag 0
set NbRWValue 0
set intNbAccess 0
set NewDSPMapping 1
set HasDSPModule 1
set ResetLevelFlag 0
set ResetStyle control
set ResetSyncFlag 1
set ResetRegisterFlag 0
set ResetVariableFlag 0
set ResetRegisterNum 0
set FsmEncStyle onehot
set MaxFanout 0
set RtlPrefix {}
set RtlSubPrefix loop_uhat_sparse_
set ExtraCCFlags {}
set ExtraCLdFlags {}
set SynCheckOptions {}
set PresynOptions {}
set PreprocOptions {}
set SchedOptions {}
set BindOptions {}
set RtlGenOptions {}
set RtlWriterOptions {}
set CbcGenFlag {}
set CasGenFlag {}
set CasMonitorFlag {}
set AutoSimOptions {}
set ExportMCPathFlag 0
set SCTraceFileName mytrace
set SCTraceFileFormat vcd
set SCTraceOption all
set TargetInfo xc7z007s:-clg400:-1
set SourceFiles {sc {} c {../../../CCE-C/library/src/call_rcond.c ../loop_uhat_sparse.cpp ../../../CCE-C/library/src/rtGetInf.c ../../../CCE-C/library/src/rtGetNaN.c ../../../CCE-C/library/src/rt_nonfinite.c ../../../CCE-C/library/src/svd.c ../../../CCE-C/library/src/xaxpy.c ../../../CCE-C/library/src/xdotc.c ../../../CCE-C/library/src/xnrm2.c ../../../CCE-C/library/src/xrot.c ../../../CCE-C/library/src/xrotg.c ../../../CCE-C/library/src/xswap.c}}
set SourceFlags {sc {} c {{} {} {} {} {} {} {} {} {} {} {} {}}}
set DirectiveFile {}
set TBFiles {verilog ../../../CCE-C/library/mainsparse.cpp bc ../../../CCE-C/library/mainsparse.cpp vhdl ../../../CCE-C/library/mainsparse.cpp sc ../../../CCE-C/library/mainsparse.cpp cas ../../../CCE-C/library/mainsparse.cpp c {}}
set SpecLanguage C
set TVInFiles {bc {} c {} sc {} cas {} vhdl {} verilog {}}
set TVOutFiles {bc {} c {} sc {} cas {} vhdl {} verilog {}}
set TBTops {verilog {} bc {} vhdl {} sc {} cas {} c {}}
set TBInstNames {verilog {} bc {} vhdl {} sc {} cas {} c {}}
set XDCFiles {}
set ExtraGlobalOptions {"area_timing" 1 "clock_gate" 1 "impl_flow" map "power_gate" 0}
set TBTVFileNotFound {}
set AppFile ../hls.app
set ApsFile loop_uhat_sparse_imp.aps
set AvePath ../../.
set DefaultPlatform DefaultPlatform
set multiClockList {}
set SCPortClockMap {}
set intNbAccess 0
set PlatformFiles {{DefaultPlatform {xilinx/zynq/zynq}}}
set HPFPO 0
