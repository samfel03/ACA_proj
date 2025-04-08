set moduleName loop_uhat_sparse_Pipeline_VITIS_LOOP_70_3
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
set C_modelName {loop_uhat_sparse_Pipeline_VITIS_LOOP_70_3}
set C_modelType { void 0 }
set C_modelArgList {
	{ input_data_R double 64 regular {array 17048 { 1 3 } 1 1 }  }
	{ output_data double 64 regular {array 17048 { 1 3 } 1 1 }  }
	{ R_exp double 64 regular  }
	{ integral double 64 regular {array 17048 { 0 3 } 0 1 }  }
}
set hasAXIMCache 0
set AXIMCacheInstList { }
set C_modelArgMapList {[ 
	{ "Name" : "input_data_R", "interface" : "memory", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "output_data", "interface" : "memory", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "R_exp", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "integral", "interface" : "memory", "bitwidth" : 64, "direction" : "WRITEONLY"} ]}
# RTL Port declarations: 
set portNum 28
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ input_data_R_address0 sc_out sc_lv 15 signal 0 } 
	{ input_data_R_ce0 sc_out sc_logic 1 signal 0 } 
	{ input_data_R_q0 sc_in sc_lv 64 signal 0 } 
	{ output_data_address0 sc_out sc_lv 15 signal 1 } 
	{ output_data_ce0 sc_out sc_logic 1 signal 1 } 
	{ output_data_q0 sc_in sc_lv 64 signal 1 } 
	{ R_exp sc_in sc_lv 64 signal 2 } 
	{ integral_address0 sc_out sc_lv 15 signal 3 } 
	{ integral_ce0 sc_out sc_logic 1 signal 3 } 
	{ integral_we0 sc_out sc_logic 1 signal 3 } 
	{ integral_d0 sc_out sc_lv 64 signal 3 } 
	{ grp_fu_380_p_din0 sc_out sc_lv 64 signal -1 } 
	{ grp_fu_380_p_din1 sc_out sc_lv 64 signal -1 } 
	{ grp_fu_380_p_dout0 sc_in sc_lv 64 signal -1 } 
	{ grp_fu_380_p_ce sc_out sc_logic 1 signal -1 } 
	{ grp_pow_generic_double_s_fu_344_p_din1 sc_out sc_lv 64 signal -1 } 
	{ grp_pow_generic_double_s_fu_344_p_din2 sc_out sc_lv 64 signal -1 } 
	{ grp_pow_generic_double_s_fu_344_p_dout0 sc_in sc_lv 64 signal -1 } 
	{ grp_pow_generic_double_s_fu_344_p_start sc_out sc_logic 1 signal -1 } 
	{ grp_pow_generic_double_s_fu_344_p_ready sc_in sc_logic 1 signal -1 } 
	{ grp_pow_generic_double_s_fu_344_p_done sc_in sc_logic 1 signal -1 } 
	{ grp_pow_generic_double_s_fu_344_p_idle sc_in sc_logic 1 signal -1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "input_data_R_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":15, "type": "signal", "bundle":{"name": "input_data_R", "role": "address0" }} , 
 	{ "name": "input_data_R_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_R", "role": "ce0" }} , 
 	{ "name": "input_data_R_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "input_data_R", "role": "q0" }} , 
 	{ "name": "output_data_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":15, "type": "signal", "bundle":{"name": "output_data", "role": "address0" }} , 
 	{ "name": "output_data_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_data", "role": "ce0" }} , 
 	{ "name": "output_data_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "output_data", "role": "q0" }} , 
 	{ "name": "R_exp", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "R_exp", "role": "default" }} , 
 	{ "name": "integral_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":15, "type": "signal", "bundle":{"name": "integral", "role": "address0" }} , 
 	{ "name": "integral_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "integral", "role": "ce0" }} , 
 	{ "name": "integral_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "integral", "role": "we0" }} , 
 	{ "name": "integral_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "integral", "role": "d0" }} , 
 	{ "name": "grp_fu_380_p_din0", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "grp_fu_380_p_din0", "role": "default" }} , 
 	{ "name": "grp_fu_380_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "grp_fu_380_p_din1", "role": "default" }} , 
 	{ "name": "grp_fu_380_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "grp_fu_380_p_dout0", "role": "default" }} , 
 	{ "name": "grp_fu_380_p_ce", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_fu_380_p_ce", "role": "default" }} , 
 	{ "name": "grp_pow_generic_double_s_fu_344_p_din1", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "grp_pow_generic_double_s_fu_344_p_din1", "role": "default" }} , 
 	{ "name": "grp_pow_generic_double_s_fu_344_p_din2", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "grp_pow_generic_double_s_fu_344_p_din2", "role": "default" }} , 
 	{ "name": "grp_pow_generic_double_s_fu_344_p_dout0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "grp_pow_generic_double_s_fu_344_p_dout0", "role": "default" }} , 
 	{ "name": "grp_pow_generic_double_s_fu_344_p_start", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_pow_generic_double_s_fu_344_p_start", "role": "default" }} , 
 	{ "name": "grp_pow_generic_double_s_fu_344_p_ready", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_pow_generic_double_s_fu_344_p_ready", "role": "default" }} , 
 	{ "name": "grp_pow_generic_double_s_fu_344_p_done", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_pow_generic_double_s_fu_344_p_done", "role": "default" }} , 
 	{ "name": "grp_pow_generic_double_s_fu_344_p_idle", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "grp_pow_generic_double_s_fu_344_p_idle", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1"],
		"CDFG" : "loop_uhat_sparse_Pipeline_VITIS_LOOP_70_3",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "17145", "EstimateLatencyMax" : "17145",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "input_data_R", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "output_data", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "R_exp", "Type" : "None", "Direction" : "I"},
			{"Name" : "integral", "Type" : "Memory", "Direction" : "O"},
			{"Name" : "pow_reduce_anonymous_namespace_log_inverse_lut_table_pow_0_5_64_array", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log0_lut_table_array", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_4_4_16_array", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_7_6_64_array", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_12_6_64_array", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_17_6_64_array", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_22_6_64_array", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_27_6_64_array", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_32_6_64_array", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_array", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_array", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_array", "Type" : "Memory", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_70_3", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter96", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter96", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.flow_control_loop_pipe_sequential_init_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	loop_uhat_sparse_Pipeline_VITIS_LOOP_70_3 {
		input_data_R {Type I LastRead 87 FirstWrite -1}
		output_data {Type I LastRead 0 FirstWrite -1}
		R_exp {Type I LastRead 0 FirstWrite -1}
		integral {Type O LastRead -1 FirstWrite 96}
		pow_reduce_anonymous_namespace_log_inverse_lut_table_pow_0_5_64_array {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log0_lut_table_array {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_4_4_16_array {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_7_6_64_array {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_12_6_64_array {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_17_6_64_array {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_22_6_64_array {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_27_6_64_array {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_32_6_64_array {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_array {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_array {Type I LastRead -1 FirstWrite -1}
		pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_array {Type I LastRead -1 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "17145", "Max" : "17145"}
	, {"Name" : "Interval", "Min" : "17145", "Max" : "17145"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	input_data_R { ap_memory {  { input_data_R_address0 mem_address 1 15 }  { input_data_R_ce0 mem_ce 1 1 }  { input_data_R_q0 mem_dout 0 64 } } }
	output_data { ap_memory {  { output_data_address0 mem_address 1 15 }  { output_data_ce0 mem_ce 1 1 }  { output_data_q0 in_data 0 64 } } }
	R_exp { ap_none {  { R_exp in_data 0 64 } } }
	integral { ap_memory {  { integral_address0 mem_address 1 15 }  { integral_ce0 mem_ce 1 1 }  { integral_we0 mem_we 1 1 }  { integral_d0 mem_din 1 64 } } }
}
