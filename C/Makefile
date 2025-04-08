
#######################################################################################
.PHONY: help
help:
	@echo "Makefile Usage:"
	@echo "" ................................................
	@echo "  make cpu "
	@echo "      Command to generate the design for serial execution on CPU."
	@echo ""
	@echo "  make openmpi "
	@echo "      Command to generate the design for parallel execution on CPU using OPENMPI."
	@echo ""
	@echo "  make fpga TARGET=<sw_emu|hw>"
	@echo "      Command to generate the design for specified Target and Device."
	@echo ""
	@echo "  make exe "
	@echo "      Command to generate host."
	@echo ""
	@echo "  make xclbin "
	@echo "      Command to generate hardware platform files(xo,xclbin)."
	@echo ""
	@echo "  make clean "
	@echo "      Command to remove the generated files."
	@echo ""
	@echo "  make afi EMAIL=<your email> "
	@echo "      Command to generate the fpga binary to run on AWS."
	@echo ""
	@echo "  make validate "
	@echo "      Command to compare the between files in hw_checks and c_orig->checks"
	@echo ""
	@echo "  make zip "
	@echo "      Command to save the logs, reports and dcp file to a single zip file"
	@echo ""
	@echo "  make power "
	@echo "      Command to log the power consumed"
	@echo ""
	@echo "  make results "
	@echo "      Command to run the host and fpga binaries and save the results"
	@echo ""
#######################################################################################
TARGET := hw
MPICXX := mpic++
CC := g++
INCLUDES := -I./common -I./common/libs -I./cpu -I./fpga -I./ -I$(XILINX_XRT)/include/ -I$(XILINX_VIVADO)/include/
PLATFORM := xilinx_aws-vu9p-f1_shell-v04261818_201920_3
HOST_EXE := host
CPU_EXE := app
OPENMPI_EXE := openmpi_app
XO := ./fpga/build/runOnfpga.xo
XCLBIN := ./fpga/build/runOnfpga.xclbin
S3_BUCKET_NAME := ksfpga-$(shell aws sts get-caller-identity | grep "Account" | tr -dc '0-9')
S3_DCP_DIR := vitis-dcps
S3_LOG_DIR := vitis-logs
EMAIL := 		# enter your email address
SHELL := /bin/bash
CPU_CORES := 1 #set the number of CPU cores
OPENMPI_FLAG := -D_OPENMPI_MODE
FPGA_FLAG := -D_FPGA_MODE
SERIAL_CPU_FLAG := -D_SERIAL_CPU_MODE

# Host building global settings
CXXFLAGS :=   $(INCLUDES) -Wall -O3 -std=c++11 -L$(XILINX_XRT)/lib/ -lpthread -lrt -lstdc++
CXXFLAGS2 := -lOpenCL

# Kernel compiler & linker global settings
KRNL_COMPILE_OPTS := -I./common -t $(TARGET) --config ./fpga/design.cfg --log_dir ./fpga/logs --report_dir ./fpga/reports --save-temps --jobs 8 --optimize 3
KRNL_LINK_OPTS := -I./common -t $(TARGET) --config ./fpga/design.cfg --log_dir ./fpga/logs --report_dir ./fpga/reports --save-temps --jobs 8 --optimize 3

.PHONY: afi
afi: afigen
	source $(AWS_FPGA_REPO_DIR)/hdk_setup.sh
	pip install --user --upgrade boto3
	wait_for_afi.py --afi $(shell cat *afi_id.txt | sed -n '2p' | tr -d '",' | sed 's/.*://') --notify --email $(EMAIL) &

.PHONY: afigen
afigen: fpga
	aws s3 mb s3://$(S3_BUCKET_NAME) --region us-east-1
	aws s3 mb s3://$(S3_BUCKET_NAME)/$(S3_DCP_DIR)
	touch FILES_GO_HERE.txt
	aws s3 cp FILES_GO_HERE.txt s3://$(S3_BUCKET_NAME)/$(S3_DCP_DIR)
	aws s3 mb s3://$(S3_BUCKET_NAME)/$(S3_LOG_DIR)
	touch LOGS_FILES_GO_HERE.txt
	aws s3 cp LOGS_FILES_GO_HERE.txt s3://$(S3_BUCKET_NAME)/$(S3_LOG_DIR)
	rm -rf to_aws
	$(VITIS_DIR)/tools/create_vitis_afi.sh -xclbin=$(XCLBIN) -s3_bucket=$(S3_BUCKET_NAME) -s3_dcp_key=$(S3_DCP_DIR) -s3_logs_key=$(S3_LOG_DIR)

fpga:  $(XO) $(XCLBIN) $(HOST_EXE) emconfig

exe: $(HOST_EXE)

xclbin: $(XO) $(XCLBIN)

cpu: $(CPU_EXE)

openmpi: $(OPENMPI_EXE)

# Building kernel
$(XO): ./fpga/hw.cpp
	v++ -I./common -I./fpga -I./ $(FPGA_FLAG)  $(KRNL_COMPILE_OPTS) -c -k runOnfpga -o'$@' '$<'

$(XCLBIN): $(XO)
	v++ -I./common -I./fpga -I./ $(KRNL_LINK_OPTS) -l  -o'$@' $(+)

# Building fpga Host for EGM until convergence
$(HOST_EXE): ./common/libs/xcl2.cpp ./common/app.cpp ./common/init.cpp
	$(CC) $(FPGA_FLAG)  $(CXXFLAGS) $^ -o $@ $(CXXFLAGS2)

# Building and executing CPU executable using OpenMPI for EGM until convergence
$(OPENMPI_EXE): ./common/init.cpp ./common/app.cpp ./cpu/sw.cpp
	$(MPICXX) $(OPENMPI_FLAG)  $(CXXFLAGS) $^ -o $@
# mpirun -n $(CPU_CORES) ./$@

# Building sequential CPU executable using g++ for EGM until convergence
$(CPU_EXE): ./common/init.cpp ./common/app.cpp ./cpu/sw.cpp
	$(CC) $(SERIAL_CPU_FLAG)  $(CXXFLAGS) -L/usr/local/lib -L/opt/lib -lm -lgsl -lcblas $^ -o $@

.PHONY: emconfig
emconfig:
	emconfigutil --platform $(PLATFORM)

.PHONY: clean
clean:
	$(RM) -rf *.csv *.jou *.run_summary *.dcp to_aws _x *.tar *.bin *.txt *.dSYM *.out 
	$(RM) *.o *~ rm -f $(HOST_EXE) $(CPU_EXE) $(HOST_EXE_FXD) $(CPU_EXE_FXD) $(OPENMPI_EXE) 
	$(RM) -rf $(OPENMPI_EXE_FXD) *.log *.json *.xo .Xil/ .run/ runOnfpga* fpga/logs/ fpga/logs/link/* fpga/reports/* fpga/build/*
	
.PHONY: results_clean
results_clean:
	$(RM) -rf results/*.txt common/sw_checks/float/*.txt common/sw_checks/double/*.txt fpga/hw_checks/float/*.txt fpga/hw_checks/double/*.txt 

.PHONY: validate
validate:
	python3 ./common/util/compare_results.py

.PHONY: zip
zip:
	sh ./common/util/save_results.sh

.PHONY: power
power:
	sh ./common/util/power.sh

.PHONY: results
results:
	sh ./common/util/2run_me.sh

# g++ init.cpp aux_main.cpp -Wall -O3 -std=c++11 -lpthread -lrt -lstdc++ -o aux