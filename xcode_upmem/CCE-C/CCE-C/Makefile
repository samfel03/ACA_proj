# DPU_DIR := dpu
# HOST_DIR := host
# BUILDDIR ?= bin
# NR_DPUS ?= 1
# NR_TASKLETS ?= 1
# BLOCK ?= 10
# TYPE ?= DOUBLE
# TRANSFER ?= PARALLEL
# PRINT ?= 0
# PERF ?= NO
# CC = gcc
# CXX = g++

# # CONF configuration
# define conf_filename
# 	${BUILDDIR}/.NR_DPUS_$(1)_NR_TASKLETS_$(2)_BLOCK_$(3)_TYPE_$(4)_TRANSFER_$(5)_PRINT_$(6)_PERF_$(7).conf
# endef
# CONF := $(call conf_filename,${NR_DPUS},${NR_TASKLETS},${BLOCK},${TYPE},${TRANSFER},${PRINT},${PERF})


# # Target directories
# HOST_TARGET := ${BUILDDIR}/host_code
# DPU_TARGET := ${BUILDDIR}/dpu_code

# # Source directories
# COMMON_INCLUDES := support
# HOST_SOURCES := $(wildcard ${HOST_DIR}/*.c)
# # HOST_SOURCES := $(wildcard ${HOST_DIR}/*.cpp)
# DPU_SOURCES := $(wildcard ${DPU_DIR}/*.c)

# .PHONY: all clean test

# # Building bin
# __dirs := $(shell mkdir -p ${BUILDDIR})

# # Flags for compilation
# COMMON_FLAGS := -Wall -Wextra -g -I${COMMON_INCLUDES}
# HOST_FLAGS := ${COMMON_FLAGS} --std=c++11  `dpu-pkg-config --cflags --libs dpu` -g -DNR_TASKLETS=${NR_TASKLETS} -DNR_DPUS=${NR_DPUS} -DBLOCK=${BLOCK} -D${TYPE} -DPRINT=${PRINT} -D${TRANSFER} -D${PERF}
# DPU_FLAGS := ${COMMON_FLAGS} -O2 -DNR_TASKLETS=${NR_TASKLETS} -DBLOCK=${BLOCK} -D${TYPE} -DPRINT=${PRINT} -D${TRANSFER} -D${PERF}

# # all: ${HOST_TARGET} ${DPU_TARGET}
# all: ${DPU_TARGET}

# ${CONF}:
# 	$(RM) $(call conf_filename,*,*)
# 	touch ${CONF}

# ${HOST_TARGET}: ${HOST_SOURCES} ${COMMON_INCLUDES} ${CONF}
# 	$(CC) -o $@ ${HOST_SOURCES} ${HOST_FLAGS}

# ${DPU_TARGET}: ${DPU_SOURCES} ${COMMON_INCLUDES} ${CONF}
# 	dpu-upmem-dpurte-clang ${DPU_FLAGS} -o $@ ${DPU_SOURCES}

# clean:
# 	$(RM) $(BUILDDIR)/*

# test: all
# 	./${HOST_TARGET}


# Variables for directories and build options
DPU_DIR := dpu
HOST_DIR := host
BUILDDIR ?= bin
NR_DPUS ?= 40
NR_TASKLETS ?= 16
BLOCK ?= 10
TYPE ?= DOUBLE
TRANSFER ?= PARALLEL
PRINT ?= 0
PERF ?= NO
CC = gcc
CXX = g++

# Configuration file naming
define conf_filename
	${BUILDDIR}/.NR_DPUS_$(1)_NR_TASKLETS_$(2)_BLOCK_$(3)_TYPE_$(4)_TRANSFER_$(5)_PRINT_$(6)_PERF_$(7).conf
endef
CONF := $(call conf_filename,${NR_DPUS},${NR_TASKLETS},${BLOCK},${TYPE},${TRANSFER},${PRINT},${PERF})

# Target directories
HOST_TARGET := ${BUILDDIR}/host_code
DPU_TARGET := ${BUILDDIR}/dpu_code

# Source directories
COMMON_INCLUDES := support
HOST_SOURCES := ${HOST_DIR}/app.cpp library/*.o
DPU_SOURCES := $(wildcard ${DPU_DIR}/*.c)

.PHONY: all clean test

# Create bin directory if it doesn't exist
__dirs := $(shell mkdir -p ${BUILDDIR})

# Compilation flags
COMMON_FLAGS := -Wall -Wextra -g -I${COMMON_INCLUDES}

# Host flags
HOST_FLAGS := --std=c++11 `dpu-pkg-config --cflags --libs dpu` -DNR_TASKLETS=${NR_TASKLETS} -DNR_DPUS=${NR_DPUS} -g

# DPU flags
DPU_FLAGS := ${COMMON_FLAGS} -O2 -DNR_TASKLETS=${NR_TASKLETS} -DBLOCK=${BLOCK}  -D${TYPE} -DPRINT=${PRINT} -D${TRANSFER} -D${PERF}

# Build all targets
all: ${DPU_TARGET} ${HOST_TARGET}

# Generate configuration file
${CONF}:
	$(RM) $(call conf_filename,*,*)
	touch ${CONF}

# Host target rule with specified command
${HOST_TARGET}: ${HOST_SOURCES} ${COMMON_INCLUDES} ${CONF}
	$(CXX) -o $@ ${HOST_SOURCES} ${HOST_FLAGS}

# DPU target rule
${DPU_TARGET}: ${DPU_SOURCES} ${COMMON_INCLUDES} ${CONF}
	dpu-upmem-dpurte-clang ${DPU_FLAGS} -o $@ ${DPU_SOURCES}

# Clean build directory
clean:
	$(RM) -r $(BUILDDIR)

# Run test
test: all
	./${HOST_TARGET}
