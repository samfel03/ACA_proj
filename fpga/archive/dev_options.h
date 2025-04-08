/**
 * Debug acceleration options
 */

//Set only one of the below 4 to 1. For best performance, set _ACROSS_ECONOMY to 1 and rest 0
#define DETAILED_PERF_METRICS	1 // set to print detailed timing values
#define _BASELINE               1
#define _ACROSS_ECONOMY         0

#if _BASELINE 
#define NUM_KERNELS 			1   // more than 1 only used for fpga 
#define FIXED_ACC				0   // set this to use fixed point for accumulation in egm and ast
#define AST_UNROLL			    0   // set this to 1 for unrolling ast loop
#define NUM_KPRIMES 		    1   //
#define PARTITION_KCROSS	    1   //
#define SMALL_PL				1   // unroll egm_2 by a factor of 1
#define SPREAD_SCALAR_TRICK		0
#elif _ACROSS_ECONOMY
#define NUM_KERNELS 			3   // more than 1 only used for fpga 
#define FIXED_ACC				1   // set this to use fixed point for accumulation in egm and ast
#define AST_UNROLL			    1   //set this to 1 for unrolling ast loop
#define PARTITION_KCROSS	    8   //
#define NUM_KPRIMES 		    8   //
#define SMALL_PL				0   //
#define SPREAD_SCALAR_TRICK		1   //
#endif


#define SHOCKS_FROM_HEADER		1 // Use shocks from consh.h file
#define USE_PREALLOC_VALUES     1 // Use pre-initialized kgrid and km_grid for fpga
#define HW_BUFFER_SIZE        300 ///< arbitrary number chosen to represent max iterations
/**
 * Usage of HLS library in sw_emu
 */
#define USE_HLS_LIB				0