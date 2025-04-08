set moduleName loop_uhat_sparse_Pipeline_VITIS_LOOP_83_5
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
set C_modelName {loop_uhat_sparse_Pipeline_VITIS_LOOP_83_5}
set C_modelType { void 0 }
set C_modelArgList {
	{ sext_ln83 int 32 regular  }
	{ wide_trip_count int 32 regular  }
	{ input_data_value double 64 regular {array 17048 { 1 3 } 1 1 }  }
	{ input_data_colIndex int 15 regular {array 17048 { 1 3 } 1 1 }  }
	{ integral double 64 regular {array 17048 { 1 3 } 1 1 }  }
	{ rhs_out double 64 regular {pointer 1}  }
}
set hasAXIMCache 0
set AXIMCacheInstList { }
set C_modelArgMapList {[ 
	{ "Name" : "sext_ln83", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "wide_trip_count", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "input_data_value", "interface" : "memory", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "input_data_colIndex", "interface" : "memory", "bitwidth" : 15, "direction" : "READONLY"} , 
 	{ "Name" : "integral", "interface" : "memory", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "rhs_out", "interface" : "wire", "bitwidth" : 64, "direction" : "WRITEONLY"} ]}
# RTL Port declarations: 
set portNum 28
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ sext_ln83 sc_in sc_lv 32 signal 0 } 
	{ wide_trip_count sc_in sc_lv 32 signal 1 } 
	{ input_data_value_address0 sc_out sc_lv 15 signal 2 } 
	{ input_data_value_ce0 sc_out sc_logic 1 signal 2 } 
	{ input_data_value_q0 sc_in sc_lv 64 signal 2 } 
	{ input_data_colIndex_address0 sc_out sc_lv 15 signal 3 } 
	{ input_data_colIndex_ce0 sc_out sc_logic 1 signal 3 } 
	{ input_data_colIndex_q0 sc_in sc_lv 15 signal 3 } 
	{ integral_address0 sc_out sc_lv 15 signal 4 } 
	{ integral_ce0 sc_out sc_logic 1 signal 4 } 
	{ integral_q0 sc_in sc_lv 64 signal 4 } 
	{ rhs_out sc_out sc_lv 64 signal 5 } 
	{ rhs_out_ap_vld sc_out sc_logic 1 outvld 5 } 
	{ grp_fu_374_p_din0 sc_out sc_lv 64 signal -1 } 
	{ grp_fu_374_p_din1 sc_out sc_lv 64 signal -1 } 
	{ grp_fu_374_p_opcode sc_out sc_lv 1 signal -1 } 
	{ grp_fu_374_p_dout0 sc_in sc_lv 64 signal -1 } 
	{ grp_fu_374_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_fu_380_p_din0 sc_out sc_lv 64 signal -1 } 
	{ grp_fu_380_p_din1 sc_out sc_lv 64 signal -1 } 
	{ grp_fu_380_p_dout0 sc_in sc_lv 64 signal -1 } 
	{ grp_fu_380_p_ce sc_out sc_logic 1 signal -1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "sext_ln83", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sext_ln83", "role": "default" }} , 
 	{ "name": "wide_trip_count", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "wide_trip_count", "role": "default" }} , 
 	{ "name": "input_data_value_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":15, "type": "signal", "bundle":{"name": "input_data_value", "role": "address0" }} , 
 	{ "name": "input_data_value_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_value", "role": "ce0" }} , 
 	{ "name": "input_data_value_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "input_data_value", "role": "q0" }} , 
 	{ "name": "input_data_colIndex_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":15, "type": "signal", "bundle":{"name": "input_data_colIndex", "role": "address0" }} , 
 	{ "name": "input_data_colIndex_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_colIndex", "role": "ce0" }} , 
 	{ "name": "input_data_colIndex_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":15, "type": "signal", "bundle":{"name": "input_data_colIndex", "role": "q0" }} , 
 	{ "name": "integral_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":15, "type": "signal", "bundle":{"name": "integral", "role": "address0" }} , 
 	{ "name": "integral_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "integral", "role": "ce0" }} , 
 	{ "name": "integral_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "integral", "role": "q0" }} , 
 	{ "name": "rhs_out", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "rhs_out", "role": "default" }} , 
 	{ "name": "rhs_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "rhs_out", "role": "ap_vld" }} , 
 	{ "name": "grp_fu_374_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "grp_fu_374_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_374_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "grp_fu_374_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_374_p_opcode", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_374_p_opcode", "role": "default" }} , 
 	{ "name": "grp_fu_374_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "grp_fu_374_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_374_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_374_p_ce", "role": "default" }} , 
 	{ "name": "grp_fu_380_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "grp_fu_380_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_380_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "grp_fu_380_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_380_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "grp_fu_380_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_380_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_380_p_ce", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1"],
		"CDFG" : "loop_uhat_sparse_Pipeline_VITIS_LOOP_83_5",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "-1", "EstimateLatencyMax" : "-1",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "sext_ln83", "Type" : "None", "Direction" : "I"},
			{"Name" : "wide_trip_count", "Type" : "None", "Direction" : "I"},
			{"Name" : "input_data_value", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "input_data_colIndex", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "integral", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "rhs_out", "Type" : "Vld", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_83_5", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "7", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage4", "LastStateIter" : "ap_enable_reg_pp0_iter2", "LastStateBlock" : "ap_block_pp0_stage4_subdone", "QuitState" : "ap_ST_fsm_pp0_stage4", "QuitStateIter" : "ap_enable_reg_pp0_iter2", "QuitStateBlock" : "ap_block_pp0_stage4_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.flow_control_loop_pipe_sequential_init_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	loop_uhat_sparse_Pipeline_VITIS_LOOP_83_5 {
		sext_ln83 {Type I LastRead 0 FirstWrite -1}
		wide_trip_count {Type I LastRead 0 FirstWrite -1}
		input_data_value {Type I LastRead 1 FirstWrite -1}
		input_data_colIndex {Type I LastRead 1 FirstWrite -1}
		integral {Type I LastRead 2 FirstWrite -1}
		rhs_out {Type O LastRead -1 FirstWrite 11}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "-1", "Max" : "-1"}
	, {"Name" : "Interval", "Min" : "-1", "Max" : "-1"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	sext_ln83 { ap_none {  { sext_ln83 in_data 0 32 } } }
	wide_trip_count { ap_none {  { wide_trip_count in_data 0 32 } } }
	input_data_value { ap_memory {  { input_data_value_address0 mem_address 1 15 }  { input_data_value_ce0 mem_ce 1 1 }  { input_data_value_q0 mem_dout 0 64 } } }
	input_data_colIndex { ap_memory {  { input_data_colIndex_address0 mem_address 1 15 }  { input_data_colIndex_ce0 mem_ce 1 1 }  { input_data_colIndex_q0 in_data 0 15 } } }
	integral { ap_memory {  { integral_address0 mem_address 1 15 }  { integral_ce0 mem_ce 1 1 }  { integral_q0 mem_dout 0 64 } } }
	rhs_out { ap_vld {  { rhs_out out_data 1 64 }  { rhs_out_ap_vld out_vld 1 1 } } }
}
