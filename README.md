# SIAM FPGA Accelerator

This project consists of the C++ Implementation, the MATLAB implementation and the embedded implementation (on Zynq7000).

## C Implementation

### Requirements

- Visual Studio Code
- Windows Subsystem for Linux (WSL) or any UNIX OS
- MinGW C/C++ tools for Windows (gcc, gdb, clang)
  - Installation [MinGW installation](https://code.visualstudio.com/docs/cpp/config-mingw)
- CMake and CMake Tools for VSCode


### Replication

1. Clone repo

    `git clone https://github.com/Boulder-Computer-Architecture-Lab/CU-Spur-Sean.git`

2. Navigate to "spurFPGA/CCE-C"
3. Run VSCode command to configure CMake

    `>CMake: Delete Cache and Reconfigure`

4. Change all paths accordingly in target main file

5. Open WSL or UNIX OS and navigate to "spurFPGA\CCE-C\apps" and run

    `make`

6. Run the output "main" file with gdb or gcc
   - NOTE: Must configure CMake in "Debug Mode" to debug with gdb

### Notes

- To change target main file, navigate to "spurFPGA\CCE-C\apps\CMakeLists.txt" and edit line 5.

    `add_executable(main -Insert target here-)`

- To add sources, add source to "spurFPGA\CCE-C\library\src", then navigate to "spurFPGA\CCE-C\library\CMakeLists.txt" and edit line 5, add_library() and add the file for linking.

- To add headers, add header file to "spurFPGA\CCE-C\library\include"

- DO NOT run on Windows as it will Segmentation Fault at NLLS start due to the limit Windows puts on heap and stack size for each Service. Run on WSL or another UNIX OS.

- main.cpp --> Non-sparse implementation
  
  mainAVX.cpp --> Incomplete attempt at using AVX intrinsics (CPU MUST SUPPORT AVX)
  
  mainsparse --> Sparse implementation (edit "TRMULT_REDUCED_THRESHOLD" to change cutoff)

- Debug mode means the program will print outputs

## MATLAB Implementation

### Requirements

- MATLAB

### Replication

1. Open MATLAB and open folder "\matlab-final"
2. Open main_testbench.m and Run or use Debugger

### Notes

- The C program above uses files that are output at the start of the MATLAB program.
  - If numbers are slightly off, check the output paths and make sure the files are updated when the MATLAB program is run.
- The MATLAB implementation is much faster, likely because it takes advantage of CPU intrinsics automatically and is optimized on compile for these applications.

## FPGA Implementation

### In Progress