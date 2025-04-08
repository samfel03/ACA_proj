#pragma once

#include <vector>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include <time.h>
#include <math.h>
#include <cstdint>
#include <chrono>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <sstream>
#include <array>
#include <map>

#ifdef FPGA_MODE
#define CL_HPP_CL_1_2_DEFAULT_BUILD
#define CL_HPP_TARGET_OPENCL_VERSION 120
#define CL_HPP_MINIMUM_OPENCL_VERSION 120
#define CL_HPP_ENABLE_PROGRAM_CONSTRUCTION_FROM_ARRAY_COMPATIBILITY 1
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
// #include "Utilities.h"
#include <CL/cl2.hpp>
#include "xcl2.hpp"
#include "hw.h"
#elif SERIAL_CPU_MODE
//BABA #include "sw.h"
#elif OMPI_MODE
#include "mpi.h"
#include "sw.h"
#endif
#include "init.h"
//#include "definitions.h"
#include "stopwatch.h"
//#include "dev_options.h"
