# climate_accel
Acceleration of Climate Change Model

# Steps to run the program

## Using sequential execution in CPU

1. In the common/definitions.h, set the number of time the same function is required to run
```
#define N_MODEL 1
```
2. Set the input path in common/definitions.h
```
#define INPUTPATH "/home/centos/climate_accel/input/"
```
3. Compile and execute 
```
make cpu
./app
```

## Use FPGA

### Software Emulation (C Simulation)
The main goal of software emulation (sw_emu) is to ensure functional correctness of the host program and kernels. Software emulation provides a purely functional execution, without any modeling of timing delays, or latency; it does not give any indication of the accelerator performance. Click [here](https://docs.xilinx.com/r/en-US/ug1393-vitis-application-acceleration/Software-Emulation) to know more about this. All the three steps listed below needs to be performed in AWS EC2 instance similar to z1d.2xlarge instance.

1. In the common/definitions.h, set the number of time the same function is required to run
```
#define N_MODEL 1
```
2. Set the input path in common/definitions.h
```
#define INPUTPATH "/home/centos/climate_accel/input/"
```
3. Set the environment variables 
```
source $AWS_FPGA_REPO_DIR/vitis_setup.sh
export PLATFORM_REPO_PATHS=$(dirname $AWS_PLATFORM)
```
4. make 
```
make fpga TARGET=sw_emu
```
5. run
```
source $AWS_FPGA_REPO_DIR/vitis_setup.sh 
source $AWS_FPGA_REPO_DIR/vitis_runtime_setup.sh
export XCL_EMULATION_MODE=sw_emu
./host ./fpga/build/runOnfpga.xclbin
```

### System Hardware Target (hw)
When the build target is the hardware, v++ builds the FPGA binary for the Xilinx device by running Vivado synthesis and implementation on the design. It is normal for this build target to take a longer period of time than generating either the software or hardware emulation targets in the Vitis IDE. However, the final FPGA binary can be loaded into the hardware of the accelerator card, or embedded processor platform, and the application can be run in its actual operating environment. Click [here](https://docs.xilinx.com/r/en-US/ug1393-vitis-application-acceleration/System-Hardware-Target) to know more about this.The steps (1-2) listed below needs to be performed in AWS EC2 instance similar to z1d.2xlarge instance.
### Image Generation using EC2 instance
1. In the common/definitions.h, set the number of time the same function is required to run
```
#define N_MODEL 1
```
2. Set the input path in common/definitions.h
```
#define INPUTPATH "/home/centos/climate_accel/input/"
```
3. Set the environment variables 
```
source $AWS_FPGA_REPO_DIR/vitis_setup.sh
export PLATFORM_REPO_PATHS=$(dirname $AWS_PLATFORM)
```
4. Configure AWS. This needs to be done only once to create a s3 bucket to then generate runOnfpga.awsxclbin file from the runOnfpga.xclbin.
```
aws configure
```
5. make 
```
make afi EMAIL=<email address>
```
6. Save the generated outputs. If you are using VS Code, righ click on the "host" and click download. Similarly, download the "runOnfpga.awsxclbin" files. For future reference, you can also download the "fpga/build" folder to observe the reports. 
7. Stop the EC2 instacne

###
### Execution on FPGA using F1.2X instance
1. Connect to your f1.2xlarge and execute the following commands from the terminal for setting up the Xilinx environment and to clone the project
```
git clone https://github.com/aws/aws-fpga.git $AWS_FPGA_REPO_DIR //AWS repo
git clone https://github.com/AleP83/climate_accel.git  //climate accel Project
```
2. Copy the "input" folder that has all the .bin files into the cloned ""climate_accel" repository
3. Verify that the "input" folder path is exactly the same as defined in the "common/definitions.h" file
```
#define INPUTPATH "/home/centos/climate_accel/input/"
```
4. Copy the generated executables "host" and "runOnfpga.awsxclbin" files into the cloned "climate_accel" folder
5. Set the environment inside the climate_accel folder
```
source $AWS_FPGA_REPO_DIR/vitis_setup.sh
source $AWS_FPGA_REPO_DIR/vitis_runtime_setup.sh
export PLATFORM_REPO_PATHS=$(dirname $AWS_PLATFORM)
```
6. Copy the generated output text file and the summary files for later analysis
- uhat_out_from_i0_d0_k0.txt
- xrt.run_summary
- summary.csv
- opencl_trace.csv
- device_trace_0.csv
7. Make sure to terminate your F1 instance! It costs 1.65$/hr.
