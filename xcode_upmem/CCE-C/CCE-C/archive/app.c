/**
 * app.c
 * Host Application Source File
 *
 */

/*
=================
|1 2 3 4 5 6 7 8|
|9 0 1 2 3 4 5 6|
|7 8 9 0 1 2 3 4|
|5 6 7 8 9 0 1 2|
|3 4 5 6 7 8 9 0|
|1 2 3 4 5 6 7 8|
|9 0 1 2 3 4 5 6|
|7 8 9 0 1 2 3 4|
=================
*/
#include <assert.h>
#include <dpu.h>
#include <dpu_log.h>
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../support/common.h"
#include "../support/params.h"
#include "../support/timer.h"

// MACROS - DPUS
// Define the DPU Binary path as DPU_BINARY here
typedef double real;
#ifndef DPU_BINARY
#define DPU_BINARY "./bin/dpu_code"
#endif

// MACROS - Eco Model (Change multi_mag for matrix size) (Also change in task.c)
#define DPU_TReal real
#define NPOSLAND 17048
#define multi_mag NPOSLAND
#define trmult_reduced_rows multi_mag
#define trmult_reduced_cols multi_mag
#define integral_rows multi_mag
#define integral_cols 1
#define IPOSLAND(i, j) ((i) * trmult_reduced_cols + (j))

// Global declarations
DPU_TReal *trmult_reduced; // Input Matrix
DPU_TReal *trmult_host;    // Final matrix for verification
DPU_TReal *integral;       // Input vector
unsigned int *data_per_dpu;
uint32_t total_dpus;
dpu_arguments_t *input_arguments;

// Functions
void read_data(DPU_TReal *trmult_reduced, DPU_TReal *integral) {
  double count = 0;
  int i, j = 0;
  for (i = 0; i < trmult_reduced_rows; i++) {
    integral[i] = count;
    for (j = 0; j < trmult_reduced_cols; j++) {
      trmult_reduced[IPOSLAND(i, j)] = IPOSLAND(i, j);
    }
    count += 1;
  }

  // printf("Total read_data count: %lf, i: %d, j: %d\n", count, i, j);
}

DPU_TReal calculate_trmult_host(DPU_TReal *y, DPU_TReal *x) {

  FILE *MyFile = fopen("expected_output.txt", "w");
  if (MyFile == NULL) {
    perror("Error opening file");
    return 1;
  }

  // x -> trmult_host
  // y -> integral
  DPU_TReal total = 0, prev_total = 0;
  unsigned int i = 0, j = 0;
  for (i = 0; i < trmult_reduced_rows; i++) {
    for (j = 0; j < trmult_reduced_cols; j++) {
      x[IPOSLAND(i, j)] *= y[j];
      total += x[IPOSLAND(i, j)];
    }
    fprintf(MyFile, "Row %d -- %f\n", i, total - prev_total);
    prev_total = total;
  }
  fclose(MyFile);
  return total;
}

unsigned int set_no_of_dpus() {
  return (integral_rows < NR_DPUS) ? integral_rows : NR_DPUS;
}

unsigned int set_matrix_dpu_input_params(unsigned int n, unsigned int m, int printData) {
  const unsigned int input_size = n * m;                                                                                                    // Total input size
  const unsigned int input_size_8bytes = ((input_size * sizeof(DPU_TReal)) % 8) != 0 ? roundup(input_size, 8) : input_size;                 // Total input size, 8-byte aligned
  const unsigned int input_size_dpu = divceil(input_size, total_dpus);                                                                      // Input size per DPU (max.)
  const unsigned int input_size_dpu_8bytes = ((input_size_dpu * sizeof(DPU_TReal)) % 8) != 0 ? roundup(input_size_dpu, 8) : input_size_dpu; // Input size per DPU (max.), 8-byte aligned

  if (printData == 1) {
    printf("\ninput_size: %d, input_size_8bytes(aligned): %d, input_size_dpu: %d, input_size_dpu_8bytes(aligned): %d\n", input_size, input_size_8bytes, input_size_dpu, input_size_dpu_8bytes);
  }
  return input_size_dpu_8bytes;
}

unsigned int set_vector_dpu_input_params(unsigned int n, unsigned int m, int printData) {
  const unsigned int integral_input_size = n * m;                                                                                                               // Total input size
  const unsigned int integral_input_size_8bytes = ((integral_input_size * sizeof(DPU_TReal)) % 8) != 0 ? roundup(integral_input_size, 8) : integral_input_size; // Total input size, 8-byte aligned
  const unsigned int integral_input_size_dpu = integral_input_size;                                                                                             // Input size per DPU (max.)
  const unsigned int integral_input_size_dpu_8bytes = integral_input_size;                                                                                      // Input size per DPU (max.), 8-byte aligned

  if (printData == 1) {
    printf("\nintegral_input_size: %d, integral_input_size_8bytes(aligned): %d, integral_input_size_dpu: %d, integral_input_size_dpu_8bytes(aligned): %d\n\n", integral_input_size, integral_input_size_8bytes, integral_input_size_dpu, integral_input_size_dpu_8bytes);
  }
  return integral_input_size_dpu_8bytes;
}

unsigned int max_capacity_for_one_dpu(unsigned int k) {
  // k -> number of values in a row
  // Check data_design.txt for more information on this equation
  unsigned int n = (8388 * 1000) / (k + 128);
  return n;
}

unsigned int are_dpus_adequate() {
  unsigned int max_capacity = max_capacity_for_one_dpu(integral_rows);
  printf("Max Capacity: %d\n", max_capacity);
  // unsigned int data_per_dpu[total_dpus];
  data_per_dpu = (unsigned int *)malloc(total_dpus * sizeof(unsigned int));

  unsigned int main_partition_rows = integral_rows / total_dpus;
  unsigned int left_over_rows = integral_rows - (total_dpus * main_partition_rows);
  if (main_partition_rows > max_capacity) {
    printf("Increase the number of dpus!\n");
    return 0;
  }

  int i;
  for (i = 0; i < total_dpus; i++) {
    data_per_dpu[i] = main_partition_rows;
  }

  for (int i = 0; i < left_over_rows; i++) {
    if (data_per_dpu[i] + 1 > max_capacity) {
      printf("Increase the number of dpus, leftover do not fit the dpu!\n");
      return 0;
    }
    data_per_dpu[i] += 1; // Give one extra row to each DPU in the first `left_over_rows` positions
  }

  for (i = 0; i < total_dpus; i++) {
    printf("Data per dpu %d: %d\n", i, data_per_dpu[i]);
  }

  return 1;
}

void print_result_arr(DPU_TReal arr[], unsigned int array_size, char *st) {
  int i = 0;
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~Printing %s!\n", st);
  for (i = 0; i < array_size; i++) {
    printf("index: %d, result: %f\n", i, arr[i]);
  }
}

void set_dpu_arguments(int input_size_dpu_8bytes, int integral_input_size_dpu_8bytes) {
  unsigned int kernel = 0;
  int accumulator_index_count = 0;
  unsigned int range_start, range_end;
  printf("Output on:: dpu being adequate: %d\n", are_dpus_adequate());

  // bool limit_reached = false;
  unsigned int total_bytes_to_send, last_byte = (trmult_reduced_rows * trmult_reduced_cols * sizeof(DPU_TReal)); // max capacity is assumed a bit less than 1kb to avoid unknown errors
  unsigned int i = 0;

  for (i = 0; i < total_dpus; i++) {
    total_bytes_to_send = data_per_dpu[i] * integral_rows * sizeof(DPU_TReal);
    input_arguments[i].size = total_bytes_to_send;
    input_arguments[i].transfer_size = total_bytes_to_send;
    input_arguments[i].start_index = (i == 0) ? ((total_bytes_to_send / sizeof(DPU_TReal)) * i) : (input_arguments[i - 1].end_index);
    input_arguments[i].end_index = input_arguments[i].start_index + (total_bytes_to_send / sizeof(DPU_TReal));
    input_arguments[i].kernel = kernel;
    input_arguments[i].accumulator_arr_size = data_per_dpu[i];
  }
}

// Main of the Host Application
int main(int argc, char **argv) {

  FILE *fp;
  fp = freopen("logs.txt", "w", stdout);
  // Input parameters
  struct Params p = input_params(argc, argv);

  // Timer declaration
  Timer timer;
#if defined(CYCLES) || defined(INSTRUCTIONS)
  double cc = 0;
  double cc_min = 0;
#endif

  printf("---------- Initialization ----------\n\n");
  // DONE: UPMEM: Allocate DPUs
  struct dpu_set_t dpu_set, dpu;
  total_dpus = NR_DPUS;
  total_dpus = set_no_of_dpus(); // Dynamically set total dpus
  DPU_ASSERT(dpu_alloc(total_dpus, NULL, &dpu_set));
  DPU_ASSERT(dpu_get_nr_dpus(dpu_set, &total_dpus)); // Number of DPUs in the DPU set
  printf("Allocated %d DPU(s)\t", total_dpus);
  printf("NR_TASKLETS\t%d\tBLOCK\t%d\n", NR_TASKLETS, BLOCK);

  // REMOVE: LOGS: Problem Statement Size specifications
  printf("trmult_rows: %d, trmult_cols: %d, integral_rows: %d, integral_cols: %d\n\n", trmult_reduced_rows, trmult_reduced_cols, integral_rows, integral_cols);

  // DONE: QUANTITY: Model initializer (Element based calculation)
  const unsigned int input_size_dpu_8bytes = set_matrix_dpu_input_params(trmult_reduced_rows, trmult_reduced_cols, 1);

  // DONE: QUANTITY: Integral initializer (Element based calculation)
  const unsigned int integral_input_size_dpu_8bytes = set_vector_dpu_input_params(integral_rows, integral_cols, 1);

  // REMOVE: LOGS: Input/output allocation in host main memory (Whole arrays)
  printf("Total trmult_reduced Allocation (bytes): %lu\n\n", input_size_dpu_8bytes * total_dpus * sizeof(DPU_TReal));
  printf("Total integral Allocation (bytes): %lu\n\n", integral_input_size_dpu_8bytes * sizeof(DPU_TReal));

  // DONE: ADDRESS: Setting matrix (trmult_reduced) and vector(integral)
  trmult_reduced = (DPU_TReal *)malloc(input_size_dpu_8bytes * total_dpus * sizeof(DPU_TReal));
  integral = (DPU_TReal *)malloc(integral_input_size_dpu_8bytes * sizeof(DPU_TReal));

  // REMOVE: For verification
  trmult_host = (DPU_TReal *)malloc(input_size_dpu_8bytes * total_dpus * sizeof(DPU_TReal));

  // DONE: ADDRESS: Reading data on matrix and vector
  if (trmult_reduced == NULL || integral == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
  }
  printf("Data Reding begins...\n");
  read_data(trmult_reduced, integral);
  printf("Data Reding complete!\n\n");

  // REMOVE: Setting dummy data for dpu output verification
  printf("Setting Host output checker\n");
  DPU_TReal host_total = 0;
  memcpy(trmult_host, trmult_reduced, input_size_dpu_8bytes * total_dpus * sizeof(DPU_TReal));
  host_total = calculate_trmult_host(integral, trmult_host);
  printf("Host output set...\n\n");

  // DONE: Total space 8 bytes aligned that x needs to store elements
  unsigned int i = 0;

  // ------------------------------------------------------------------------------ uhat_loop specific

  // LOGS:
  FILE *MyFile = fopen("host_output.txt", "w");
  if (MyFile == NULL) {
    perror("Error opening file");
    return 1;
  }

  // DONE: Loop over main kernel
  int rep = 0, rep_count;

  // DONE: FOR LOOPS
  // for (rep = 0; rep < 1; rep++) {

  // Compute output on CPU (verification purposes)
  if (rep >= p.n_warmup)
    start(&timer, 0, rep - p.n_warmup);

  if (rep >= p.n_warmup)
    stop(&timer, 0);

  printf("\n\n---------- Setting and Transferring data ----------\n\n");

  // DONE: MEMORY: Setting Input arguments
  // unsigned int kernel = 0;
  input_arguments = (dpu_arguments_t *)malloc(total_dpus * sizeof(dpu_arguments_t));
  set_dpu_arguments(input_size_dpu_8bytes, integral_input_size_dpu_8bytes);

  // REMOVE: LOGS: Input parameters logs
  for (i = 0; i < total_dpus; i++) {
    printf("size(bytes): %d, transfer size(bytes): %d, start_index: %d, end_index: %d\n", input_arguments[i].size, input_arguments[i].transfer_size, input_arguments[i].start_index, input_arguments[i].end_index);
  }

  // DONE: Accumulation / Index to be set for accumulation arr (integral rows in case of whole row per dpu transfer)
  unsigned int k = 0;
  int accumulator_index_count = integral_rows;

  // MEMORY: Data is read back into this vector
  DPU_TReal *vector_multiplication;
  vector_multiplication = (DPU_TReal *)malloc(accumulator_index_count * sizeof(DPU_TReal));

  // ADVANCED: UPMEM: Load binary
  DPU_ASSERT(dpu_load(dpu_set, DPU_BINARY, NULL));

  // DONE: Setup hash array (Locations on which values are to be extracted from DPU)
  int accumulator_index[accumulator_index_count];
  // accumulator_index[0] = integral_rows;
  for (i = 0; i < accumulator_index_count; i++) {
    accumulator_index[i] = integral_rows * (i + 1);
  }

  // REMOVE: LOGS: Indexes on which we accumulate
  k = 0;
  for (k = 0; k < accumulator_index_count; k++) {
    printf("Hash indexes: %d\n", accumulator_index[k]);
  }

  if (rep >= p.n_warmup)
    start(&timer, 1, rep - p.n_warmup); // Start timer (CPU-DPU transfers)

  // DONE: UPMEM: Transfering input parameters
  printf("\nPARALLEL TRANSFER: Input args transfer starts...\n");
  i = 0;
  DPU_FOREACH(dpu_set, dpu, i) {
    DPU_ASSERT(dpu_prepare_xfer(dpu, &input_arguments[i]));
  }
  DPU_ASSERT(dpu_push_xfer(dpu_set, DPU_XFER_TO_DPU, "DPU_INPUT_ARGUMENTS", 0, sizeof(input_arguments[0]), DPU_XFER_DEFAULT));
  printf("Input args transfer ends...\n\n");

  // SERIAL CPU-DPU TRANSFER HERE
  // Params(dpu reference, Base pointer MRAM, offset within MRAM, Pointer to main memory, total data sent)
  printf("SERIAL TRANSFER: Data transfer for trmult_reduced starts...\n");
  unsigned int mem_address = 0;
  DPU_FOREACH(dpu_set, dpu, i) {
    // PARAMS(dpu reference, Base pointer in MRAM, offset withing MRAM, Pointer on main memory, Total data to be sent)
    dpu_copy_to(dpu, DPU_MRAM_HEAP_POINTER_NAME, integral_rows * sizeof(DPU_TReal), trmult_reduced + mem_address, data_per_dpu[i] * integral_rows * sizeof(DPU_TReal));
    mem_address += data_per_dpu[i] * integral_rows;
  }
  printf("Data transfer for trmult_reduced ends!\n\n");

  // PARALLEL CPU-DPU TRANSFER HERE
  // DONE: UPMEM: Parallel trmult_reduced transfer
  // printf("PARALLEL TRANSFER: Data transfer for trmult_reduced starts...\n");
  // i = 0;
  // mem_address = 0;
  // DPU_FOREACH(dpu_set, dpu, i) {
  //   // Params(Reference to dpu, pointer to main-memory)
  //   DPU_ASSERT(dpu_prepare_xfer(dpu, trmult_reduced + mem_address * integral_rows));
  //   mem_address += data_per_dpu[i];
  // }
  // // Params(Reference to dpu set, Direction of transfer, Start Address, Offset, )
  // DPU_ASSERT(dpu_push_xfer(dpu_set, DPU_XFER_TO_DPU, DPU_MRAM_HEAP_POINTER_NAME, 0, input_size_dpu_8bytes * sizeof(DPU_TReal), DPU_XFER_DEFAULT));
  // printf("Data transfer for trmult_reduced ends!\n\n");

  // DONE: UPMEM: Broadcasting Integral Array
  // TODO:
  printf("Broadcasting integral begins...\n");
  // PARAMS(reference to dpu, Base pointer within MRAM, Offset within MRAM, Pointer to main memory, total data to be sent)
  DPU_ASSERT(dpu_broadcast_to(dpu_set, DPU_MRAM_HEAP_POINTER_NAME, 0, integral, integral_rows * integral_cols * sizeof(DPU_TReal), DPU_XFER_DEFAULT));
  printf("Broadcasting integral ends!\n");

  if (rep >= p.n_warmup) {
    stop(&timer, 1); // Stop timer (CPU-DPU transfers)
  }

  if (rep >= p.n_warmup) {
    start(&timer, 2, rep - p.n_warmup); // Start timer (DPU kernel)
  }

  // ADVANCED: UPMEM: DPU Launch
  printf("\n\n---------- Launching DPU ----------\n\n");
  DPU_ASSERT(dpu_launch(dpu_set, DPU_SYNCHRONOUS));
  if (rep >= p.n_warmup) {
    stop(&timer, 2); // Stop timer (DPU kernel)
  }
  printf("Dpu Processing ends!\n\n");

  printf("\n\n---------- Running DPU Logs ----------\n\n");

  // DONE: UPMEM: LOGS: DPU Output Logs
  printf("Beginning DPU output...\n\n");
  DPU_FOREACH(dpu_set, dpu) {
    DPU_ASSERT(dpu_log_read(dpu, stdout));
  }
  printf("Ending DPU output!\n\n");

#if PRINT
  {
    unsigned int each_dpu = 0;
    printf("Display DPU Logs\n");
    DPU_FOREACH(dpu_set, dpu) {
      printf("DPU#%d:\n", each_dpu);
      DPU_ASSERT(dpulog_read_for_dpu(dpu.dpu, stdout));
      each_dpu++;
    }
  }
#endif

  if (rep >= p.n_warmup)
    start(&timer, 3, rep - p.n_warmup); // Start timer (DPU-CPU transfers)

  i = 0;
  printf("\n\n----------Reading data back from DPU----------\n\n");

  // PARALLEL DPU-CPU Transfer
  // DONE: UPMEM: Reading data back from DPU
  printf("Vector multiplication data reading back started...\n");
  // DPU_FOREACH(dpu_set, dpu, i) {
  //   DPU_ASSERT(dpu_copy_from(dpu, DPU_MRAM_HEAP_POINTER_NAME, input_size_dpu_8bytes * sizeof(DPU_TReal), vector_multiplication + input_arguments[i].accumulator_arr_size * i, input_arguments[i].accumulator_arr_size * sizeof(DPU_TReal)));
  // }
  mem_address = 0;
  DPU_FOREACH(dpu_set, dpu, i) {
    printf("Collecting for i: %d\n", i);
    // PARAMS(reference to dpu, Base pointer MRAM, offset within MRAM, Pointer to the main memory, Total elements to gather)
    // TODO: offset is sus
    DPU_ASSERT(dpu_copy_from(dpu, DPU_MRAM_HEAP_POINTER_NAME, (integral_rows + data_per_dpu[i] * integral_rows) * sizeof(DPU_TReal), vector_multiplication + mem_address, input_arguments[i].accumulator_arr_size * sizeof(DPU_TReal)));

    printf("Offset: %d, Pointer to main memory: %d, transfer_size: %ld\n", (integral_rows + data_per_dpu[i] * integral_rows) * sizeof(DPU_TReal), mem_address, input_arguments[i].accumulator_arr_size * sizeof(DPU_TReal));
    mem_address += input_arguments[i].accumulator_arr_size;
  }
  printf("Vector multiplication data from DPU recieved back!\n");

  // #endif
  if (rep >= p.n_warmup)
    stop(&timer, 3); // Stop timer (DPU-CPU transfers)

#if defined(CYCLES) || defined(INSTRUCTIONS)
  dpu_results_t results[total_dpus];
  // Parallel transfers
  dpu_results_t *results_retrieve[total_dpus];
  DPU_FOREACH(dpu_set, dpu, i) {
    results_retrieve[i] = (dpu_results_t *)malloc(NR_TASKLETS * sizeof(dpu_results_t));
    DPU_ASSERT(dpu_prepare_xfer(dpu, results_retrieve[i]));
  }
  DPU_ASSERT(dpu_push_xfer(dpu_set, DPU_XFER_FROM_DPU, "DPU_RESULTS", 0, NR_TASKLETS * sizeof(dpu_results_t), DPU_XFER_DEFAULT));
  DPU_FOREACH(dpu_set, dpu, i) {
    results[i].count = 0;
    // Retrieve tasklet count
    for (unsigned int each_tasklet = 0; each_tasklet < NR_TASKLETS; each_tasklet++) {
      if (results_retrieve[i][each_tasklet].count > results[i].count)
        results[i].count = results_retrieve[i][each_tasklet].count;
    }
    free(results_retrieve[i]);
  }

  uint64_t max_count = 0;
  uint64_t min_count = 0xFFFFFFFFFFFFFFFF;
  // Print performance results
  if (rep >= p.n_warmup) {
    i = 0;
    DPU_FOREACH(dpu_set, dpu) {
      if (results[i].count > max_count)
        max_count = results[i].count;
      if (results[i].count < min_count)
        min_count = results[i].count;
      i++;
    }
    cc += (double)max_count;
    cc_min += (double)min_count;
  }
#endif

#ifdef CYCLES
  printf("DPU cycles  = %g\n", cc / p.n_reps);
#elif INSTRUCTIONS
  printf("DPU instructions  = %g\n", cc / p.n_reps);
#endif

  // LOGS: Print timing results
  printf("\n\n---------- Total Time ----------\n\n");
  printf("CPU ");
  print(&timer, 0, p.n_reps);
  printf("CPU-DPU ");
  print(&timer, 1, p.n_reps);
  printf("DPU Kernel ");
  print(&timer, 2, p.n_reps);
  printf("DPU-CPU ");
  print(&timer, 3, p.n_reps);

  // LOGS: Total number of rows to be accumulated
  printf("Accumulator size: %d\n", accumulator_index_count);

  // MEMORY: Initializing output vector and output verification variable
  DPU_TReal total_sum = 0;
  DPU_TReal arr_result[integral_rows * integral_cols];
  for (int u = 0; u < integral_rows * integral_cols; u++)
    arr_result[u] = 0;

  // LOGS: Printing data gathered from dpu
  print_result_arr(vector_multiplication, accumulator_index_count, "Gathered Data Result");

  // DONE: Extracting values based on each hash
  for (int u = 0; u < accumulator_index_count; u++) {
    printf("Item: %d, Index: %d\n", (accumulator_index[u] - 1), (accumulator_index[u] - 1) / integral_rows);
    arr_result[(accumulator_index[u] - 1) / integral_rows] += vector_multiplication[u];
    total_sum += vector_multiplication[u];
  }

  // LOGS: Printing each value inside the result vector after gathering
  print_result_arr(arr_result, integral_rows, "Integral result");

  // LOGS: Printing the final sum for verification
  printf("Totals: %f ---- %f", host_total, total_sum);
  // }

  fclose(MyFile);

  // Deallocation
  // DPU_TReal *trmult_reduced;
  // DPU_TReal *trmult_host;
  // DPU_TReal *integral;
  free(trmult_reduced);
  free(trmult_host);
  free(integral);
  free(data_per_dpu);
  free(input_arguments);
  free(vector_multiplication);
  DPU_ASSERT(dpu_free(dpu_set)); // Deallocate DPUs
  fclose(fp);
  return 0;
}
