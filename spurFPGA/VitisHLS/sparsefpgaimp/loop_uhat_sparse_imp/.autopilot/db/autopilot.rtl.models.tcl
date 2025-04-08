set SynModuleInfo {
  {SRCNAME loop_uhat_sparse_Pipeline_VITIS_LOOP_57_1 MODELNAME loop_uhat_sparse_Pipeline_VITIS_LOOP_57_1 RTLNAME loop_uhat_sparse_loop_uhat_sparse_Pipeline_VITIS_LOOP_57_1
    SUBMODULES {
      {MODELNAME loop_uhat_sparse_sitodp_64ns_64_6_no_dsp_1 RTLNAME loop_uhat_sparse_sitodp_64ns_64_6_no_dsp_1 BINDTYPE op TYPE sitodp IMPL auto LATENCY 5 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_flow_control_loop_pipe_sequential_init RTLNAME loop_uhat_sparse_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME loop_uhat_sparse_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME pow_generic<double> MODELNAME pow_generic_double_s RTLNAME loop_uhat_sparse_pow_generic_double_s
    SUBMODULES {
      {MODELNAME loop_uhat_sparse_mul_12s_80ns_90_5_1 RTLNAME loop_uhat_sparse_mul_12s_80ns_90_5_1 BINDTYPE op TYPE mul IMPL auto LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_mul_13s_71s_71_5_1 RTLNAME loop_uhat_sparse_mul_13s_71s_71_5_1 BINDTYPE op TYPE mul IMPL auto LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_mul_40ns_40ns_80_2_1 RTLNAME loop_uhat_sparse_mul_40ns_40ns_80_2_1 BINDTYPE op TYPE mul IMPL auto LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_mul_43ns_36ns_79_3_1 RTLNAME loop_uhat_sparse_mul_43ns_36ns_79_3_1 BINDTYPE op TYPE mul IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_mul_49ns_44ns_93_5_1 RTLNAME loop_uhat_sparse_mul_49ns_44ns_93_5_1 BINDTYPE op TYPE mul IMPL auto LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_mul_50ns_50ns_100_5_1 RTLNAME loop_uhat_sparse_mul_50ns_50ns_100_5_1 BINDTYPE op TYPE mul IMPL auto LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_mul_54s_6ns_54_5_1 RTLNAME loop_uhat_sparse_mul_54s_6ns_54_5_1 BINDTYPE op TYPE mul IMPL auto LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_mul_73ns_6ns_79_5_1 RTLNAME loop_uhat_sparse_mul_73ns_6ns_79_5_1 BINDTYPE op TYPE mul IMPL auto LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_mul_77ns_6ns_83_5_1 RTLNAME loop_uhat_sparse_mul_77ns_6ns_83_5_1 BINDTYPE op TYPE mul IMPL auto LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_mul_77s_54s_130_5_1 RTLNAME loop_uhat_sparse_mul_77s_54s_130_5_1 BINDTYPE op TYPE mul IMPL auto LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_mul_82ns_6ns_88_5_1 RTLNAME loop_uhat_sparse_mul_82ns_6ns_88_5_1 BINDTYPE op TYPE mul IMPL auto LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_mul_83ns_6ns_89_5_1 RTLNAME loop_uhat_sparse_mul_83ns_6ns_89_5_1 BINDTYPE op TYPE mul IMPL auto LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_mul_87ns_6ns_93_5_1 RTLNAME loop_uhat_sparse_mul_87ns_6ns_93_5_1 BINDTYPE op TYPE mul IMPL auto LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_mul_92ns_6ns_98_5_1 RTLNAME loop_uhat_sparse_mul_92ns_6ns_98_5_1 BINDTYPE op TYPE mul IMPL auto LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_mul_71ns_4ns_75_5_1 RTLNAME loop_uhat_sparse_mul_71ns_4ns_75_5_1 BINDTYPE op TYPE mul IMPL auto LATENCY 4 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_mac_muladd_16s_15ns_19s_31_4_1 RTLNAME loop_uhat_sparse_mac_muladd_16s_15ns_19s_31_4_1 BINDTYPE op TYPE all IMPL dsp_slice LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log_inverse_lut_table_powbkb RTLNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log_inverse_lut_table_powbkb BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log0_lut_table_array_ROM_cud RTLNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log0_lut_table_array_ROM_cud BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_4_dEe RTLNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_4_dEe BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_7_eOg RTLNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_7_eOg BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_12fYi RTLNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_12fYi BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_17g8j RTLNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_17g8j BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_22hbi RTLNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_22hbi BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_27ibs RTLNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_27ibs BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_32jbC RTLNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_log_lut_table_ap_fixed_32jbC BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_arkbM RTLNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_table_exp_Z1_ap_ufixed_arkbM BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_arralbW RTLNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_table_f_Z3_ap_ufixed_arralbW BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_arramb6 RTLNAME loop_uhat_sparse_pow_generic_double_s_pow_reduce_anonymous_namespace_table_f_Z2_ap_ufixed_arramb6 BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME loop_uhat_sparse_Pipeline_VITIS_LOOP_70_3 MODELNAME loop_uhat_sparse_Pipeline_VITIS_LOOP_70_3 RTLNAME loop_uhat_sparse_loop_uhat_sparse_Pipeline_VITIS_LOOP_70_3}
  {SRCNAME loop_uhat_sparse_Pipeline_VITIS_LOOP_83_5 MODELNAME loop_uhat_sparse_Pipeline_VITIS_LOOP_83_5 RTLNAME loop_uhat_sparse_loop_uhat_sparse_Pipeline_VITIS_LOOP_83_5}
  {SRCNAME loop_uhat_sparse_Pipeline_VITIS_LOOP_96_6 MODELNAME loop_uhat_sparse_Pipeline_VITIS_LOOP_96_6 RTLNAME loop_uhat_sparse_loop_uhat_sparse_Pipeline_VITIS_LOOP_96_6}
  {SRCNAME loop_uhat_sparse MODELNAME loop_uhat_sparse RTLNAME loop_uhat_sparse IS_TOP 1
    SUBMODULES {
      {MODELNAME loop_uhat_sparse_dadddsub_64ns_64ns_64_7_full_dsp_1 RTLNAME loop_uhat_sparse_dadddsub_64ns_64ns_64_7_full_dsp_1 BINDTYPE op TYPE dadd IMPL fulldsp LATENCY 6 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_dmul_64ns_64ns_64_7_max_dsp_1 RTLNAME loop_uhat_sparse_dmul_64ns_64ns_64_7_max_dsp_1 BINDTYPE op TYPE dmul IMPL maxdsp LATENCY 6 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_dcmp_64ns_64ns_1_2_no_dsp_1 RTLNAME loop_uhat_sparse_dcmp_64ns_64ns_1_2_no_dsp_1 BINDTYPE op TYPE dcmp IMPL auto LATENCY 1 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_input_data_rowStart_RAM_AUTO_1R1W RTLNAME loop_uhat_sparse_input_data_rowStart_RAM_AUTO_1R1W BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_input_data_colIndex_RAM_AUTO_1R1W RTLNAME loop_uhat_sparse_input_data_colIndex_RAM_AUTO_1R1W BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_input_data_value_RAM_AUTO_1R1W RTLNAME loop_uhat_sparse_input_data_value_RAM_AUTO_1R1W BINDTYPE storage TYPE ram IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME loop_uhat_sparse_CTRL_BUS_s_axi RTLNAME loop_uhat_sparse_CTRL_BUS_s_axi BINDTYPE interface TYPE interface_s_axilite}
      {MODELNAME loop_uhat_sparse_regslice_both RTLNAME loop_uhat_sparse_regslice_both BINDTYPE interface TYPE interface_regslice INSTNAME loop_uhat_sparse_regslice_both_U}
    }
  }
}
