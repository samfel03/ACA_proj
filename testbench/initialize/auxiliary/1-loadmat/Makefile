
#######################################################################################
.PHONY: help
help:
	@echo "Makefile Usage:"
	@echo "" ................................................
	@echo "  make cpu "
	@echo "      Command to generate the design for serial execution on CPU."
#######################################################################################
MPICXX := mpic++
CC := /usr/local/Cellar/gcc/11.3.0/bin/gcc-11
INCLUDES := -I./ 
CPU_EXE := main
CPU_CORES := 1 #set the number of CPU cores
SERIAL_CPU_FLAG := -D_SERIAL_CPU_MODE
# Host building global settings
CXXFLAGS :=   $(INCLUDES) -Wall -O3 -g -std=c++11 -lpthread -lstdc++
cpu: $(CPU_EXE)
# Building sequential CPU executable using g++ for EGM until convergence
$(CPU_EXE): 
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