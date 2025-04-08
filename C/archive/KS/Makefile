
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
MPICXX := mpic++
CC := /usr/local/Cellar/gcc/11.3.0/bin/gcc-11
INCLUDES := -I./common -I./cpu 
CPU_EXE := app
OPENMPI_EXE := openmpi_app
CPU_CORES := 1 #set the number of CPU cores
OPENMPI_FLAG := -D_OPENMPI_MODE
SERIAL_CPU_FLAG := -D_SERIAL_CPU_MODE

# Host building global settings
CXXFLAGS :=   $(INCLUDES) -Wall -O3 -g -std=c++11 -lpthread -lstdc++

cpu: $(CPU_EXE)

openmpi: $(OPENMPI_EXE)

# Building kernel
# Building and executing CPU executable using OpenMPI for EGM until convergence
$(OPENMPI_EXE): ./common/init.cpp ./common/app.cpp ./cpu/sw.cpp
	$(MPICXX) $(OPENMPI_FLAG)  $(CXXFLAGS) $^ -o $@
# mpirun -n $(CPU_CORES) ./$@

# Building sequential CPU executable using g++ for EGM until convergence
$(CPU_EXE): ./common/init.cpp ./common/app.cpp ./cpu/sw.cpp
	$(CC) $(SERIAL_CPU_FLAG)  $(CXXFLAGS) -L/usr/local/lib -L/usr/local/Cellar/gcc/11.3.0/lib/gcc/11/ -lm -lcblas $^ -o $@

.PHONY: clean
clean:
	$(RM) *.o *~ rm -f $(HOST_EXE) $(CPU_EXE) $(HOST_EXE_FXD) $(CPU_EXE_FXD) $(OPENMPI_EXE) 
	
.PHONY: validate
validate:
	python3 ./common/util/compare_results.py

.PHONY: zip
zip:
	sh ./common/util/save_results.sh