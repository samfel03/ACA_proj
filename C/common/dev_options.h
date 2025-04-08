/**
 * Platform / input options
 */
#define CPU_EXEC_CHECK	"./results-checks/"

/**
 * Debug acceleration options
 */
/*
//Set only one of the below 4 to 1. For best performance, set _ACROSS_ECONOMY to 1 and rest 0
#define _BASELINE               0
#define _PIPELINE               0
#define _WITHIN_ECONOMY         0
#define _ACROSS_ECONOMY         1

#if _BASELINE 
#define NUM_KERNELS 			1   // more than 1 only used for fpga 
#define FIXED_ACC				0   // set this to use fixed point for accumulation in egm and ast
#define AST_UNROLL			    0   // set this to 1 for unrolling ast loop
#define NUM_KPRIMES 		    1   //
#define PARTITION_KCROSS	    1   //
#define SMALL_PL				1   // unroll egm_2 by a factor of 1
#define SPREAD_SCALAR_TRICK		0
#elif _PIPELINE
#define NUM_KERNELS 			1   //  more than 1 only used for fpga 
#define FIXED_ACC				1   //  set this to use fixed point for accumulation in egm and ast
#define AST_UNROLL			    0   // set this to 1 for unrolling ast loop
#define PARTITION_KCROSS	    1   //
#define NUM_KPRIMES 		    4   //
#define SMALL_PL				1   //
#define SPREAD_SCALAR_TRICK		0   //
#elif _WITHIN_ECONOMY
#define NUM_KERNELS 			1   // more than 1 only used for fpga 
#define FIXED_ACC				1   // set this to use fixed point for accumulation in egm and ast
#define AST_UNROLL			    1   // set this to 1 for unrolling ast loop
#define PARTITION_KCROSS	    8   // 
#define NUM_KPRIMES 		    8   //
#define SMALL_PL				0   //
#define SPREAD_SCALAR_TRICK		0   //
#elif _ACROSS_ECONOMY
#define NUM_KERNELS 			3   // more than 1 only used for fpga 
#define FIXED_ACC				1   // set this to use fixed point for accumulation in egm and ast
#define AST_UNROLL			    1   //set this to 1 for unrolling ast loop
#define PARTITION_KCROSS	    8   //
#define NUM_KPRIMES 		    8   //
#define SMALL_PL				0   //
#define SPREAD_SCALAR_TRICK		1   //
#endif


#define DETAILED_PERF_METRICS	1 // set to print detailed timing values
#define SHOCKS_FROM_HEADER		1 // Use shocks from consh.h file
#define USE_PREALLOC_VALUES     1 // Use pre-initialized kgrid and km_grid for fpga
*/
/**
 * Usage of HLS library in sw_emu
 */
//#define USE_HLS_LIB				0


/**
 * Experiments
 *	Move to another section when mature
 */
/*
#define IDS_AGG_PACK			0   // If 1, AST_UNROLL must be 1?
#if IDS_AGG_PACK
#define IDS_AGG_X				1   // bytes packed into shock_t
#else
#define IDS_AGG_X				1
#endif
#define NUM_KCROSS				(8 * IDS_AGG_X)
#define PACK_IDS				1       //  set this to pack 8 bytes into each row to be stored in URAM
#define NEW_IDSHOCK_SIZE 		172700  // ceil((10000/8)*(1/8))
*/
/**
 * Paths for storing the results
 */
/*
#define KP_OUT_FILE				"./results/fpga/fixed/final_values/kpo_"
#define KCROSS_OUT_FILE			"./results/fpga/fixed/final_values/kcross_"
#define COEFFS_OUT_FILE			"./results/fpga/fixed/final_values/coeffs_"
#define R2BG_OUT_FILE			"./results/fpga/fixed/final_values/r2bg_"
#define ITER_OUT_FILE			"./results/fpga/fixed/final_values/egm_iter_"

#define CPU_KP_OUT_FILE				"./results/seq_cpu/double/final_values/kpo_"
#define CPU_KCROSS_OUT_FILE			"./results/seq_cpu/double/final_values/kcross_"
#define CPU_COEFFS_OUT_FILE			"./results/seq_cpu/double/final_values/coeffs_"
#define CPU_R2BG_OUT_FILE			"./results/seq_cpu/double/final_values/r2bg_"
#define CPU_ITER_OUT_FILE			"./results/seq_cpu/double/final_values/egm_iter_"
#define CPU_EXEC_OUT_FILE			"./results/seq_cpu/double/exec_time_"

#define OPENMPI_KP_OUT_FILE			"./results/openmpi/double/final_values/kpo_"
#define OPENMPI_KCROSS_OUT_FILE		"./results/openmpi/double/final_values/kcross_"
#define OPENMPI_COEFFS_OUT_FILE		"./results/openmpi/double/final_values/coeffs_"
#define OPENMPI_R2BG_OUT_FILE		"./results/openmpi/double/final_values/r2bg_"
#define OPENMPI_ITER_OUT_FILE		"./results/openmpi/double/final_values/egm_iter_"
#define OPENMPI_EXEC_OUT_FILE		"./results/openmpi/double/exec_time_"
*/