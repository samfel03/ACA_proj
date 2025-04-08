set ModuleHierarchy {[{
"Name" : "loop_uhat_sparse","ID" : "0","Type" : "sequential",
"SubInsts" : [
	{"Name" : "grp_loop_uhat_sparse_Pipeline_VITIS_LOOP_57_1_fu_271","ID" : "1","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "VITIS_LOOP_57_1","ID" : "2","Type" : "pipeline"},]},
	{"Name" : "grp_loop_uhat_sparse_Pipeline_VITIS_LOOP_96_6_fu_320","ID" : "3","Type" : "sequential",
		"SubLoops" : [
		{"Name" : "VITIS_LOOP_96_6","ID" : "4","Type" : "pipeline"},]},],
"SubLoops" : [
	{"Name" : "VITIS_LOOP_66_2","ID" : "5","Type" : "no",
	"SubInsts" : [
	{"Name" : "grp_loop_uhat_sparse_Pipeline_VITIS_LOOP_70_3_fu_288","ID" : "6","Type" : "sequential",
			"SubLoops" : [
			{"Name" : "VITIS_LOOP_70_3","ID" : "7","Type" : "pipeline",
			"SubInsts" : [
			{"Name" : "pow_generic_double_s","ID" : "8","Type" : "pipeline"},]},]},],
	"SubLoops" : [
	{"Name" : "VITIS_LOOP_74_4","ID" : "9","Type" : "no",
		"SubInsts" : [
		{"Name" : "grp_loop_uhat_sparse_Pipeline_VITIS_LOOP_83_5_fu_333","ID" : "10","Type" : "sequential",
				"SubLoops" : [
				{"Name" : "VITIS_LOOP_83_5","ID" : "11","Type" : "pipeline"},]},
		{"Name" : "grp_pow_generic_double_s_fu_344","ID" : "12","Type" : "pipeline"},]},]},]
}]}