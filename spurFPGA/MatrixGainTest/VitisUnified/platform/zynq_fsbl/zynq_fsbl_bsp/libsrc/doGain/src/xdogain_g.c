#include "xdogain.h"

XDogain_Config XDogain_ConfigTable[] __attribute__ ((section (".drvcfg_sec"))) = {

	{
		"xlnx,doGain-1.0", /* compatible */
		0x40000000 /* reg */
	},
	 {
		 NULL
	}
};