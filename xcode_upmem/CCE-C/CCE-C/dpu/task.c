/*
 * AXPY with multiple tasklets
 *
 */
#include <stdio.h>

#include <alloc.h>
#include <barrier.h>
#include <defs.h>
#include <mram.h>
#include <perfcounter.h>
#include <stdint.h>

#include <mutex.h>

#include "../library/loop_uhat.h"
#include "../support/common.h"
#include "../support/cyclecount.h"

// MACROS - Eco Model (Change multi_mag for matrix size) (Also change in host.c)
typedef double real;
#define DPU_TReal real
#define NPOSLAND 17048
#define multi_mag 120 // QUANTITY: Change only this value
#define trmult_reduced_rows multi_mag
#define trmult_reduced_cols multi_mag
#define integral_rows multi_mag
#define integral_cols 1
#define IPOSLAND(i, j) ((i) * trmult_reduced_cols + (j))

// Input and output arguments
__host dpu_arguments_t DPU_INPUT_ARGUMENTS;
__host dpu_results_t DPU_RESULTS[NR_TASKLETS];
// __mram DPU_TReal integral[NPOSLAND];

int shared[NR_TASKLETS];
DPU_TReal *p;
fsb_allocator_t allocator;

// Barrier
BARRIER_INIT(my_barrier, NR_TASKLETS);
// MUTEX
MUTEX_INIT(my_mutex);
MUTEX_INIT(sum_mutex);

extern int loop_uhat_kernel(void);
int (*kernels[nr_kernels])(void) = {loop_uhat_kernel};

int main(void) {
  // Kernel
  return kernels[DPU_INPUT_ARGUMENTS.kernel]();
}

static DPU_TReal multiply(DPU_TReal *bufferX, DPU_TReal *bufferY, DPU_TReal total_sum, unsigned int l_size) {
  // bufferX = trmult_reduced
  // bufferY = integral
  DPU_TReal tasklet_multiplication;
  for (unsigned int i = 0; i < l_size; i++) {
    tasklet_multiplication = bufferX[i] * bufferY[i];
    // bufferX[i] *= bufferY[i];
    bufferX[i] = 0;
    total_sum += tasklet_multiplication;
  }
  bufferX[l_size - 1] = total_sum;
  return total_sum;
}

// main_kernel1
int loop_uhat_kernel() {

  unsigned int tasklet_id = me();

#if PRINT
  printf("tasklet_id = %u\n", tasklet_id);
#endif

  if (tasklet_id == 0) {
    mem_reset(); // Reset the heap
#ifdef CYCLES
    perfcounter_config(COUNT_CYCLES, true); // Initialize once the cycle counter
#elif INSTRUCTIONS
    perfcounter_config(COUNT_INSTRUCTIONS, true); // Initialize once the instruction counter
#endif
  }

  // Barrier
  barrier_wait(&my_barrier);

#if defined(CYCLES) || defined(INSTRUCTIONS)
  perfcounter_count count;
  dpu_results_t *result = &DPU_RESULTS[tasklet_id];
  result->count = 0;
  counter_start(&count); // START TIMER
#endif

  // QUANTITY:
  uint32_t input_size_dpu_bytes = DPU_INPUT_ARGUMENTS.size;                        // Input size per DPU in bytes
  uint32_t input_size_dpu_bytes_transfer = DPU_INPUT_ARGUMENTS.transfer_size;      // Transfer input size per DPU in bytes
  uint32_t total_elements_for_this_dpu = input_size_dpu_bytes / sizeof(DPU_TReal); // Total elements to process in this dpu
  uint32_t accumulator_arr_size = DPU_INPUT_ARGUMENTS.accumulator_arr_size;

  // INDEX: Custom parallelism
  uint32_t start_index = DPU_INPUT_ARGUMENTS.start_index;
  uint32_t end_index = DPU_INPUT_ARGUMENTS.end_index;

  uint32_t total_computation_per_thread = (input_size_dpu_bytes) / (sizeof(DPU_TReal) * NR_TASKLETS); // QUANTITY:
  uint32_t thread_start_index = tasklet_id * total_computation_per_thread;                            // INDEX:
  if (tasklet_id == NR_TASKLETS - 1) {
    total_computation_per_thread = total_elements_for_this_dpu - (NR_TASKLETS - 1) * total_computation_per_thread;
  }

  // %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% CRIME SCENE:
  // Shared array sum computation mechanism
  if (tasklet_id == 0) {
    allocator = fsb_alloc(sizeof(DPU_TReal), accumulator_arr_size);
    p = fsb_get(allocator);
    if (p == NULL) {
      printf("Allocation to p failed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    }

    for (int k = 0; k < accumulator_arr_size; k++) {
      p[k] = 0;
    }
  }
  barrier_wait(&my_barrier);

  // printf("DPU_tasklet %d: is_dpu_bytes: %d, input_size_dpu_bytes_transfer: %d, start_index_dpu: %d, end_index: %d, total_elements_for_this_dpu: %d, total_computation_per_thread: %d\n", tasklet_id, input_size_dpu_bytes, input_size_dpu_bytes_transfer, start_index, end_index, total_elements_for_this_dpu, total_computation_per_thread);
  // Address of the current processing block in MRAM
  // BLOCK_SIZE_LOG2 = 8;
  // uint32_t base_tasklet = tasklet_id << BLOCK_SIZE_LOG2;

  // ADDRESS: Cache initiliazation
  uint32_t mram_base_addr_integral = (uint32_t)(DPU_MRAM_HEAP_POINTER);
  uint32_t mram_base_addr_trmult_reduced = (uint32_t)(DPU_MRAM_HEAP_POINTER + integral_rows * sizeof(DPU_TReal));
  uint32_t mram_base_addr_return_arr = (uint32_t)(mram_base_addr_trmult_reduced + input_size_dpu_bytes_transfer);

  // ADDRESS: Initialize a local cache in WRAM to store the MRAM block
  DPU_TReal *cache_trmult_reduced = (DPU_TReal *)mem_alloc(BLOCK_SIZE);
  DPU_TReal *cache_integral = (DPU_TReal *)mem_alloc(BLOCK_SIZE);

  // printf("For loop: base_tasklet: %d, input_size_dpu_bytes: %d, BLOCK_SIZE: %d, BLOCK: %d, NR_TASKLETS: %d\n\n", base_tasklet, input_size_dpu_bytes, BLOCK_SIZE, BLOCK, NR_TASKLETS);

  // INDEX: DPU level addressing
  uint32_t condition = (tasklet_id + 1) * total_computation_per_thread;
  if (end_index - start_index < condition) {
    condition = end_index - start_index;
  }

  // if (tasklet_id == 0) {
  //   printf("DPU End Index: %d\n\n", end_index);
  // }
  // barrier_wait(&my_barrier);
  // printf("id: %d, condition: %d\n", tasklet_id, condition);

  uint32_t actual_trmult_index, actual_integral_index;                 // INDEX:
  uint32_t one_iteration_compute;                                      // QUANTITY:
  uint32_t tasklet_compute, excess_to_compute, optimized_l_size_bytes; // QUANTITY: Special Case variables (Integral accessed on out of bounds)
  uint16_t out_of_bounds_compute = 0;                                  // QUANTITY:
  DPU_TReal tasklet_sum = 0;

  // INDEX: Thread Loop
  for (uint32_t i = thread_start_index; i < condition;) {
    // QUANTITY: How many elements put in the WRAM? (1024 / leftover)
    uint32_t l_size_bytes = (i + BLOCK_SIZE / sizeof(DPU_TReal) < condition) ? BLOCK_SIZE : (condition - i) * sizeof(DPU_TReal);
    one_iteration_compute = l_size_bytes / sizeof(DPU_TReal);

    // INDEX: index that we are processing
    actual_trmult_index = start_index + i;
    actual_integral_index = actual_trmult_index % integral_rows;
    out_of_bounds_compute = 0;

    // Load WRAM with current MRAM block (MRAM-WRAM TRANSFERS HERE)
    // INDEX: BYTES: Offset
    uint32_t byte_trmult_index = i * sizeof(DPU_TReal);
    uint32_t byte_integral_index = actual_integral_index * sizeof(DPU_TReal);
    optimized_l_size_bytes = l_size_bytes; // BYTES:

    // Check if integral out of bounds
    // Transfer less bytes

    if (actual_integral_index + one_iteration_compute > integral_rows) {
      // QUANTITY: one_iteration_compute = (x + y)
      excess_to_compute = (actual_integral_index + one_iteration_compute) % integral_rows; // y
      tasklet_compute = one_iteration_compute - excess_to_compute;                         // x
      optimized_l_size_bytes = tasklet_compute * sizeof(DPU_TReal);
      // printf("SC1 T_%d::\t\ttasklet_compute: %d, excess_to_compute: %d, dpu_memory_loc: %d, transfered bytes: %d\n", tasklet_id, tasklet_compute, excess_to_compute, byte_trmult_index / sizeof(DPU_TReal), optimized_l_size_bytes);
      out_of_bounds_compute = 1;
    } else {
      printf("T_%d::\t\tbyte_trmult offset: %d, dpu_memory_loc: %d, transfered bytes: %d\n", tasklet_id, byte_trmult_index, byte_trmult_index / sizeof(DPU_TReal), optimized_l_size_bytes);
    }

    // READ: MRAM - WRAM Cache
    mram_read((__mram_ptr void const(*))(mram_base_addr_trmult_reduced + byte_trmult_index), cache_trmult_reduced, optimized_l_size_bytes);
    mram_read((__mram_ptr void const(*))(mram_base_addr_integral + byte_integral_index), cache_integral, optimized_l_size_bytes);

    tasklet_sum = multiply(cache_trmult_reduced, cache_integral, tasklet_sum, optimized_l_size_bytes >> DIV);

    mutex_lock(sum_mutex);
    // printf("Updating to: %d, With mod: %d, Main Id: %d, added sum: %f\n", (actual_trmult_index / integral_rows), (actual_trmult_index / integral_rows) % accumulator_arr_size, tasklet_id, tasklet_sum);
    p[(actual_trmult_index / integral_rows) % accumulator_arr_size] += tasklet_sum;
    mutex_unlock(sum_mutex);

    // WRITE: WRAM Cache - MRAM
    mram_write(cache_trmult_reduced, (__mram_ptr void *)(mram_base_addr_trmult_reduced + byte_trmult_index), optimized_l_size_bytes);

    // ------------------ OUT OF BOUNDS COMPUTE (Remaining portion (integral start from 0 here))
    if (out_of_bounds_compute == 1) {
      // excess_to_compute left to compute
      printf("Tasklet_%d\t:: Sum: %f ++--++--\n", tasklet_id, tasklet_sum);
      tasklet_sum = 0;
      byte_trmult_index = byte_trmult_index + (one_iteration_compute - excess_to_compute) * sizeof(DPU_TReal);
      optimized_l_size_bytes = excess_to_compute * sizeof(DPU_TReal);
      printf("SC2 T_%d::\t\ttasklet_compute: %d, excess_to_compute: %d, dpu_memory_loc: %d, transfered bytes: %d\n", tasklet_id, tasklet_compute, excess_to_compute, byte_trmult_index / sizeof(DPU_TReal), optimized_l_size_bytes);

      // READ: MRAM - WRAM Cache
      mram_read((__mram_ptr void const(*))(mram_base_addr_trmult_reduced + byte_trmult_index), cache_trmult_reduced, optimized_l_size_bytes);
      mram_read((__mram_ptr void const(*))(mram_base_addr_integral), cache_integral, optimized_l_size_bytes);

      tasklet_sum += multiply(cache_trmult_reduced, cache_integral, tasklet_sum, optimized_l_size_bytes >> DIV);

      mutex_lock(sum_mutex);
      printf("Updating to: %d, With mod: %d, Id: %d, Added sum: %f\n", ((actual_trmult_index + (one_iteration_compute - excess_to_compute)) / integral_rows), ((actual_trmult_index + (one_iteration_compute - excess_to_compute)) / integral_rows) % accumulator_arr_size, tasklet_id, tasklet_sum);
      p[((actual_trmult_index + (one_iteration_compute - excess_to_compute)) / integral_rows) % accumulator_arr_size] += tasklet_sum;
      mutex_unlock(sum_mutex);

      // WRITE: WRAM Cache - MRAM
      mram_write(cache_trmult_reduced, (__mram_ptr void *)(mram_base_addr_trmult_reduced + byte_trmult_index), optimized_l_size_bytes);
    }
    // i += CHUNK: Interpretation
    i += l_size_bytes / sizeof(DPU_TReal);
  }

  // printf("Tasklet_%d\t:: Sum: %f, start: %d, end: %d\n", tasklet_id, tasklet_sum, thread_start_index, condition);

#if defined(CYCLES) || defined(INSTRUCTIONS)
  result->count += counter_stop(&count); // STOP TIMER
#endif
  barrier_wait(&my_barrier);
  if (tasklet_id == 0) {
    for (int k = 0; k < accumulator_arr_size; k++) {
      printf("Acc Sum: %f::::::::::::::::::::::::::::::::::::::::\n", p[k]);
    }
    mram_write(p, (__mram_ptr void *)(mram_base_addr_integral), accumulator_arr_size * sizeof(DPU_TReal));
  }

  // if (tasklet_id == 0) {

  // DPU_TReal *cache_result = (DPU_TReal *)mem_alloc(BLOCK_SIZE);
  // mram_read((__mram_ptr void const(*))(mram_base_addr_integral), cache_result, accumulator_arr_size * sizeof(DPU_TReal));
  // for (int k = 0; k < accumulator_arr_size; k++) {
  //   printf("Cache Result: %f~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n", cache_result[k]);
  // }
  // }

  fsb_free(allocator, p);
  return 0;
}
