set moduleName loop_uhat_sparse_Pipeline_VITIS_LOOP_57_1
set isTopModule 0
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set DLRegFirstOffset 0
set DLRegItemOffset 0
set C_modelName {loop_uhat_sparse_Pipeline_VITIS_LOOP_57_1}
set C_modelType { void 0 }
set C_modelArgList {
	{ inStream_V_data_V int 64 regular {axi_s 0 volatile  { inStream Data } }  }
	{ inStream_V_keep_V int 8 regular {axi_s 0 volatile  { inStream Keep } }  }
	{ inStream_V_strb_V int 8 regular {axi_s 0 volatile  { inStream Strb } }  }
	{ inStream_V_last_V int 1 regular {axi_s 0 volatile  { inStream Last } }  }
	{ input_data_rowStart int 32 regular {array 17048 { 0 3 } 0 1 }  }
	{ input_data_colIndex int 15 regular {array 17048 { 0 3 } 0 1 }  }
	{ input_data_value double 64 regular {array 17048 { 0 3 } 0 1 }  }
	{ input_data_L double 64 regular {array 17048 { 0 3 } 0 1 }  }
	{ input_data_R double 64 regular {array 17048 { 0 3 } 0 1 }  }
}
set hasAXIMCache 0
set AXIMCacheInstList { }
set C_modelArgMapList {[ 
	{ "Name" : "inStream_V_data_V", "interface" : "axis", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "inStream_V_keep_V", "interface" : "axis", "bitwidth" : 8, "direction" : "READONLY"} , 
 	{ "Name" : "inStream_V_strb_V", "interface" : "axis", "bitwidth" : 8, "direction" : "READONLY"} , 
 	{ "Name" : "inStream_V_last_V", "interface" : "axis", "bitwidth" : 1, "direction" : "READONLY"} , 
 	{ "Name" : "input_data_rowStart", "interface" : "memory", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "input_data_colIndex", "interface" : "memory", "bitwidth" : 15, "direction" : "WRITEONLY"} , 
 	{ "Name" : "input_data_value", "interface" : "memory", "bitwidth" : 64, "direction" : "WRITEONLY"} , 
 	{ "Name" : "input_data_L", "interface" : "memory", "bitwidth" : 64, "direction" : "WRITEONLY"} , 
 	{ "Name" : "input_data_R", "interface" : "memory", "bitwidth" : 64, "direction" : "WRITEONLY"} ]}
# RTL Port declarations: 
set portNum 32
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ inStream_TVALID sc_in sc_logic 1 invld 0 } 
	{ inStream_TDATA sc_in sc_lv 64 signal 0 } 
	{ inStream_TREADY sc_out sc_logic 1 inacc 3 } 
	{ inStream_TKEEP sc_in sc_lv 8 signal 1 } 
	{ inStream_TSTRB sc_in sc_lv 8 signal 2 } 
	{ inStream_TLAST sc_in sc_lv 1 signal 3 } 
	{ input_data_rowStart_address0 sc_out sc_lv 15 signal 4 } 
	{ input_data_rowStart_ce0 sc_out sc_logic 1 signal 4 } 
	{ input_data_rowStart_we0 sc_out sc_logic 1 signal 4 } 
	{ input_data_rowStart_d0 sc_out sc_lv 32 signal 4 } 
	{ input_data_colIndex_address0 sc_out sc_lv 15 signal 5 } 
	{ input_data_colIndex_ce0 sc_out sc_logic 1 signal 5 } 
	{ input_data_colIndex_we0 sc_out sc_logic 1 signal 5 } 
	{ input_data_colIndex_d0 sc_out sc_lv 15 signal 5 } 
	{ input_data_value_address0 sc_out sc_lv 15 signal 6 } 
	{ input_data_value_ce0 sc_out sc_logic 1 signal 6 } 
	{ input_data_value_we0 sc_out sc_logic 1 signal 6 } 
	{ input_data_value_d0 sc_out sc_lv 64 signal 6 } 
	{ input_data_L_address0 sc_out sc_lv 15 signal 7 } 
	{ input_data_L_ce0 sc_out sc_logic 1 signal 7 } 
	{ input_data_L_we0 sc_out sc_logic 1 signal 7 } 
	{ input_data_L_d0 sc_out sc_lv 64 signal 7 } 
	{ input_data_R_address0 sc_out sc_lv 15 signal 8 } 
	{ input_data_R_ce0 sc_out sc_logic 1 signal 8 } 
	{ input_data_R_we0 sc_out sc_logic 1 signal 8 } 
	{ input_data_R_d0 sc_out sc_lv 64 signal 8 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "inStream_TVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "invld", "bundle":{"name": "inStream_V_data_V", "role": "default" }} , 
 	{ "name": "inStream_TDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "inStream_V_data_V", "role": "default" }} , 
 	{ "name": "inStream_TREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "inacc", "bundle":{"name": "inStream_V_last_V", "role": "default" }} , 
 	{ "name": "inStream_TKEEP", "direction": "in", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "inStream_V_keep_V", "role": "default" }} , 
 	{ "name": "inStream_TSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "inStream_V_strb_V", "role": "default" }} , 
 	{ "name": "inStream_TLAST", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "inStream_V_last_V", "role": "default" }} , 
 	{ "name": "input_data_rowStart_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":15, "type": "signal", "bundle":{"name": "input_data_rowStart", "role": "address0" }} , 
 	{ "name": "input_data_rowStart_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_rowStart", "role": "ce0" }} , 
 	{ "name": "input_data_rowStart_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_rowStart", "role": "we0" }} , 
 	{ "name": "input_data_rowStart_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "input_data_rowStart", "role": "d0" }} , 
 	{ "name": "input_data_colIndex_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":15, "type": "signal", "bundle":{"name": "input_data_colIndex", "role": "address0" }} , 
 	{ "name": "input_data_colIndex_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_colIndex", "role": "ce0" }} , 
 	{ "name": "input_data_colIndex_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_colIndex", "role": "we0" }} , 
 	{ "name": "input_data_colIndex_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":15, "type": "signal", "bundle":{"name": "input_data_colIndex", "role": "d0" }} , 
 	{ "name": "input_data_value_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":15, "type": "signal", "bundle":{"name": "input_data_value", "role": "address0" }} , 
 	{ "name": "input_data_value_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_value", "role": "ce0" }} , 
 	{ "name": "input_data_value_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_value", "role": "we0" }} , 
 	{ "name": "input_data_value_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "input_data_value", "role": "d0" }} , 
 	{ "name": "input_data_L_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":15, "type": "signal", "bundle":{"name": "input_data_L", "role": "address0" }} , 
 	{ "name": "input_data_L_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_L", "role": "ce0" }} , 
 	{ "name": "input_data_L_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_L", "role": "we0" }} , 
 	{ "name": "input_data_L_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "input_data_L", "role": "d0" }} , 
 	{ "name": "input_data_R_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":15, "type": "signal", "bundle":{"name": "input_data_R", "role": "address0" }} , 
 	{ "name": "input_data_R_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_R", "role": "ce0" }} , 
 	{ "name": "input_data_R_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_R", "role": "we0" }} , 
 	{ "name": "input_data_R_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "input_data_R", "role": "d0" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2"],
		"CDFG" : "loop_uhat_sparse_Pipeline_VITIS_LOOP_57_1",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "85247", "EstimateLatencyMax" : "85247",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "inStream_V_data_V", "Type" : "Axis", "Direction" : "I", "BaseName" : "inStream",
				"BlockSignal" : [
					{"Name" : "inStream_TDATA_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "inStream_V_keep_V", "Type" : "Axis", "Direction" : "I", "BaseName" : "inStream"},
			{"Name" : "inStream_V_strb_V", "Type" : "Axis", "Direction" : "I", "BaseName" : "inStream"},
			{"Name" : "inStream_V_last_V", "Type" : "Axis", "Direction" : "I", "BaseName" : "inStream"},
			{"Name" : "input_data_rowStart", "Type" : "Memory", "Direction" : "O"},
			{"Name" : "input_data_colIndex", "Type" : "Memory", "Direction" : "O"},
			{"Name" : "input_data_value", "Type" : "Memory", "Direction" : "O"},
			{"Name" : "input_data_L", "Type" : "Memory", "Direction" : "O"},
			{"Name" : "input_data_R", "Type" : "Memory", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_57_1", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "5", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter2", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter2", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.sitodp_64ns_64_6_no_dsp_1_U1", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.flow_control_loop_pipe_sequential_init_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	loop_uhat_sparse_Pipeline_VITIS_LOOP_57_1 {
		inStream_V_data_V {Type I LastRead 4 FirstWrite -1}
		inStream_V_keep_V {Type I LastRead 4 FirstWrite -1}
		inStream_V_strb_V {Type I LastRead 4 FirstWrite -1}
		inStream_V_last_V {Type I LastRead 4 FirstWrite -1}
		input_data_rowStart {Type O LastRead -1 FirstWrite 0}
		input_data_colIndex {Type O LastRead -1 FirstWrite 1}
		input_data_value {Type O LastRead -1 FirstWrite 8}
		input_data_L {Type O LastRead -1 FirstWrite 9}
		input_data_R {Type O LastRead -1 FirstWrite 10}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "85247", "Max" : "85247"}
	, {"Name" : "Interval", "Min" : "85247", "Max" : "85247"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	inStream_V_data_V { axis {  { inStream_TVALID in_vld 0 1 }  { inStream_TDATA in_data 0 64 } } }
	inStream_V_keep_V { axis {  { inStream_TKEEP in_data 0 8 } } }
	inStream_V_strb_V { axis {  { inStream_TSTRB in_data 0 8 } } }
	inStream_V_last_V { axis {  { inStream_TREADY in_acc 1 1 }  { inStream_TLAST in_data 0 1 } } }
	input_data_rowStart { ap_memory {  { input_data_rowStart_address0 mem_address 1 15 }  { input_data_rowStart_ce0 mem_ce 1 1 }  { input_data_rowStart_we0 mem_we 1 1 }  { input_data_rowStart_d0 mem_din 1 32 } } }
	input_data_colIndex { ap_memory {  { input_data_colIndex_address0 mem_address 1 15 }  { input_data_colIndex_ce0 mem_ce 1 1 }  { input_data_colIndex_we0 mem_we 1 1 }  { input_data_colIndex_d0 mem_din 1 15 } } }
	input_data_value { ap_memory {  { input_data_value_address0 mem_address 1 15 }  { input_data_value_ce0 mem_ce 1 1 }  { input_data_value_we0 mem_we 1 1 }  { input_data_value_d0 mem_din 1 64 } } }
	input_data_L { ap_memory {  { input_data_L_address0 mem_address 1 15 }  { input_data_L_ce0 mem_ce 1 1 }  { input_data_L_we0 mem_we 1 1 }  { input_data_L_d0 mem_din 1 64 } } }
	input_data_R { ap_memory {  { input_data_R_address0 mem_address 1 15 }  { input_data_R_ce0 mem_ce 1 1 }  { input_data_R_we0 mem_we 1 1 }  { input_data_R_d0 mem_din 1 64 } } }
}
