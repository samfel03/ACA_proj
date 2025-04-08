# This script segment is generated automatically by AutoPilot

set axilite_register_dict [dict create]
set port_CTRL_BUS {
ELEMENTS { 
	dir I
	width 32
	depth 1
	mode ap_none
	offset 16
	offset_end 23
}
tol { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 24
	offset_end 35
}
L_exp { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 36
	offset_end 47
}
R_exp { 
	dir I
	width 64
	depth 1
	mode ap_none
	offset 48
	offset_end 59
}
ap_start { }
ap_done { }
ap_ready { }
ap_idle { }
interrupt {
}
}
dict set axilite_register_dict CTRL_BUS $port_CTRL_BUS


