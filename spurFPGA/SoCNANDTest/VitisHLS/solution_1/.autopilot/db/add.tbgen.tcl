set moduleName add
set isTopModule 1
set isCombinational 1
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set DLRegFirstOffset 0
set DLRegItemOffset 0
set C_modelName {add}
set C_modelType { int 32 }
set C_modelArgList {
	{ a int 32 regular {axi_slave 0}  }
	{ b int 32 regular {axi_slave 0}  }
}
set hasAXIMCache 0
set AXIMCacheInstList { }
set C_modelArgMapList {[ 
	{ "Name" : "a", "interface" : "axi_slave", "bundle":"CRTLS","type":"ap_none","bitwidth" : 32, "direction" : "READONLY", "offset" : {"in":24}, "offset_end" : {"in":31}} , 
 	{ "Name" : "b", "interface" : "axi_slave", "bundle":"CRTLS","type":"ap_none","bitwidth" : 32, "direction" : "READONLY", "offset" : {"in":32}, "offset_end" : {"in":39}} , 
 	{ "Name" : "ap_return", "interface" : "axi_slave", "bundle":"CRTLS","type":"ap_none","bitwidth" : 32, "offset" : {"out":16}} ]}
# RTL Port declarations: 
set portNum 20
set portList { 
	{ s_axi_CRTLS_AWVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_CRTLS_AWREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_CRTLS_AWADDR sc_in sc_lv 6 signal -1 } 
	{ s_axi_CRTLS_WVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_CRTLS_WREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_CRTLS_WDATA sc_in sc_lv 32 signal -1 } 
	{ s_axi_CRTLS_WSTRB sc_in sc_lv 4 signal -1 } 
	{ s_axi_CRTLS_ARVALID sc_in sc_logic 1 signal -1 } 
	{ s_axi_CRTLS_ARREADY sc_out sc_logic 1 signal -1 } 
	{ s_axi_CRTLS_ARADDR sc_in sc_lv 6 signal -1 } 
	{ s_axi_CRTLS_RVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_CRTLS_RREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_CRTLS_RDATA sc_out sc_lv 32 signal -1 } 
	{ s_axi_CRTLS_RRESP sc_out sc_lv 2 signal -1 } 
	{ s_axi_CRTLS_BVALID sc_out sc_logic 1 signal -1 } 
	{ s_axi_CRTLS_BREADY sc_in sc_logic 1 signal -1 } 
	{ s_axi_CRTLS_BRESP sc_out sc_lv 2 signal -1 } 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst_n sc_in sc_logic 1 reset -1 active_low_sync } 
	{ interrupt sc_out sc_logic 1 signal -1 } 
}
set NewPortList {[ 
	{ "name": "s_axi_CRTLS_AWADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "CRTLS", "role": "AWADDR" },"address":[{"name":"add","role":"start","value":"0","valid_bit":"0"},{"name":"add","role":"continue","value":"0","valid_bit":"4"},{"name":"add","role":"auto_start","value":"0","valid_bit":"7"},{"name":"a","role":"data","value":"24"},{"name":"b","role":"data","value":"32"}] },
	{ "name": "s_axi_CRTLS_AWVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "CRTLS", "role": "AWVALID" } },
	{ "name": "s_axi_CRTLS_AWREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "CRTLS", "role": "AWREADY" } },
	{ "name": "s_axi_CRTLS_WVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "CRTLS", "role": "WVALID" } },
	{ "name": "s_axi_CRTLS_WREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "CRTLS", "role": "WREADY" } },
	{ "name": "s_axi_CRTLS_WDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "CRTLS", "role": "WDATA" } },
	{ "name": "s_axi_CRTLS_WSTRB", "direction": "in", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "CRTLS", "role": "WSTRB" } },
	{ "name": "s_axi_CRTLS_ARADDR", "direction": "in", "datatype": "sc_lv", "bitwidth":6, "type": "signal", "bundle":{"name": "CRTLS", "role": "ARADDR" },"address":[{"name":"add","role":"start","value":"0","valid_bit":"0"},{"name":"add","role":"done","value":"0","valid_bit":"1"},{"name":"add","role":"idle","value":"0","valid_bit":"2"},{"name":"add","role":"ready","value":"0","valid_bit":"3"},{"name":"add","role":"auto_start","value":"0","valid_bit":"7"},{"name":"return","role":"data","value":"16"}] },
	{ "name": "s_axi_CRTLS_ARVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "CRTLS", "role": "ARVALID" } },
	{ "name": "s_axi_CRTLS_ARREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "CRTLS", "role": "ARREADY" } },
	{ "name": "s_axi_CRTLS_RVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "CRTLS", "role": "RVALID" } },
	{ "name": "s_axi_CRTLS_RREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "CRTLS", "role": "RREADY" } },
	{ "name": "s_axi_CRTLS_RDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "CRTLS", "role": "RDATA" } },
	{ "name": "s_axi_CRTLS_RRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "CRTLS", "role": "RRESP" } },
	{ "name": "s_axi_CRTLS_BVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "CRTLS", "role": "BVALID" } },
	{ "name": "s_axi_CRTLS_BREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "CRTLS", "role": "BREADY" } },
	{ "name": "s_axi_CRTLS_BRESP", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "CRTLS", "role": "BRESP" } },
	{ "name": "interrupt", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "CRTLS", "role": "interrupt" } }, 
 	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst_n", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1"],
		"CDFG" : "add",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "1",
		"VariableLatency" : "0", "ExactLatency" : "0", "EstimateLatencyMin" : "0", "EstimateLatencyMax" : "0",
		"Combinational" : "1",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "a", "Type" : "None", "Direction" : "I"},
			{"Name" : "b", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.CRTLS_s_axi_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	add {
		a {Type I LastRead 0 FirstWrite -1}
		b {Type I LastRead 0 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "0", "Max" : "0"}
	, {"Name" : "Interval", "Min" : "1", "Max" : "1"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
}

set maxi_interface_dict [dict create]

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
