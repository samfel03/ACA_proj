#include "app.h"

using std::array;
using std::map;
using std::vector;

cl::Program load_cl2_binary(cl::Program::Binaries, cl::Device device, cl::Context context);

cl_int err = CL_SUCCESS;

// ------------------------------------------------------------------------------------
// Step 1: get_xil_devices() is a utility API which will find the Xilinx
// ------------------------------------------------------------------------------------ 
auto devices = xcl::get_xil_devices();
auto device_count = devices.size();
int NUM_DEVICES = (int) device_count;

// ------------------------------------------------------------------------------------
// Step 1: One element per device
// ------------------------------------------------------------------------------------
vector<cl::Context> contexts(device_count);
vector<cl::Program> programs(device_count);
vector<cl::CommandQueue> queues(device_count);
vector< vector<cl::Kernel> > kernels(device_count, vector<cl::Kernel>(NUM_KERNELS));
vector<std::string> device_name(device_count);
vector<cl::Program::Binaries> bins(device_count);
vector<cl::Platform> platform;

/* calculate the sizes of all buffers to be initiated*/
const size_t matrix_size_bytes = sizeof(real) * (NPOSLAND * NPOSLAND);
const size_t vector_size_bytes = sizeof(real) * (NPOSLAND);

/*Initialize all buffers */
vector<vector<vector<real>>> hw_uhat_i(NUM_DEVICES, vector< vector<real> >(NUM_KERNELS, vector<real>(NPOSLAND)));

// Create opencl buffers
vector< vector<cl::Buffer> > buffer_trmult_reduced(device_count, vector<cl::Buffer>(NUM_KERNELS));	
vector< vector<cl::Buffer> > buffer_L(device_count, vector<cl::Buffer>(NUM_KERNELS));
vector< vector<cl::Buffer> > buffer_R(device_count, vector<cl::Buffer>(NUM_KERNELS));
vector< vector<cl::Buffer> > buffer_uhat_i(device_count, vector<cl::Buffer>(NUM_KERNELS));

vector< vector< vector<cl::Event> >> memory_read_events(NUM_DEVICES, vector< vector<cl::Event> >(NUM_KERNELS, std::vector<cl::Event>(1)));
vector< vector< vector<cl::Event> >> task_events(NUM_DEVICES, vector< vector<cl::Event> >(NUM_KERNELS, std::vector<cl::Event>(1)));
vector< vector< vector<cl::Event> >> memory_write_events(NUM_DEVICES, vector< vector<cl::Event> >(NUM_KERNELS, std::vector<cl::Event>(1)));

//assumption: same computation is performed across all kernels and devices
int COMP_PER_DEVICE = ceil(N_MODEL/(NUM_DEVICES*NUM_KERNELS));

void host_to_fpga(real tol,
             real *trmult_reduced, 
             real *L, 
             real L_exp, 
             real *uhat_i, 
             real *R, 
             real R_exp)
{
    
	// debug help: save the inputs to compare with hw.cpp after OpenCL transfer
   #ifdef DEBUG_MODE
        printf("sw Tol: %.16lf\n", tol);
        printf("sw R_exp: %.16lf\n", R_exp);
        printf("sw L_exp: %.16lf\n", L_exp);

        FILE *cfile;
        char FileName[512];
        printf("trmult\n");
        sprintf(FileName, "sw_trmult_reduced.txt");
        cfile = fopen(FileName, "w");
        for(int i=0; i<NPOSLAND; i++){
            fprintf(cfile, "%.15lf \n", trmult_reduced[i]);
        }
        fclose(cfile);

        printf("L\n");
        sprintf(FileName, "sw_L.txt");
        cfile = fopen(FileName, "w");
        for(int i=0; i<NPOSLAND; i++){
            fprintf(cfile, "%.15lf \n", L[i]);
        }
        fclose(cfile);

        printf("R\n");
        sprintf(FileName, "sw_R.txt");
        cfile = fopen(FileName, "w");
        for(int i=0; i<NPOSLAND; i++){
            fprintf(cfile, "%.15lf \n", L[i]);
        }
        fclose(cfile);
    #endif

    printf("Climate Accel app start\n");

	// Step 1: One element per device
    vector<unsigned char> fileBuf[device_count];
	OCL_CHECK(err, err = cl::Platform::get(&platform));

    cl_context_properties props[3] = {CL_CONTEXT_PLATFORM, (cl_context_properties)(platform[0])(), 0};
    std::cout << "Initializing OpenCL objects" << std::endl;

    for (int d = 0; d < (int)device_count; d++) {
		// We create a context for each of the devices
        std::cout << "Creating Context[" << d << "]..." << std::endl;
        OCL_CHECK(err, contexts[d] = cl::Context(devices[d], props, nullptr, nullptr, &err));
        OCL_CHECK(err, queues[d] = cl::CommandQueue(contexts[d], devices[d], CL_QUEUE_PROFILING_ENABLE | CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE, &err));
        OCL_CHECK(err, device_name[d] = devices[d].getInfo<CL_DEVICE_NAME>(&err));

        // read_binary_file() ia a utility API which will load the binaryFile and will return pointer to file buffer.
        fileBuf[d] = xcl::read_binary_file(binaryFile);
        bins[d].push_back({fileBuf[d].data(), fileBuf[d].size()});
        programs[d] = load_cl2_binary(bins[d], devices[d], contexts[d]);
		// programs[d] = load_cl2_binary(bins, devices[d], contexts[d]);

		for (int k = 0; k < NUM_KERNELS; k++) {
			//differentiate each of the kernel name
            if( k% 5 == 0 ){
				OCL_CHECK(err, kernels[d][k] = cl::Kernel(programs[d], "runOnfpga:{runOnfpga_1}", &err));
			}
			if( k% 5 == 1 ){
				OCL_CHECK(err, kernels[d][k] = cl::Kernel(programs[d], "runOnfpga:{runOnfpga_2}", &err));
			}
			if( k% 5 == 2 ){
				OCL_CHECK(err, kernels[d][k] = cl::Kernel(programs[d], "runOnfpga:{runOnfpga_3}", &err));
			}
			// Allocate Buffers in Global Memory
			// Buffers are allocated using CL_MEM_USE_HOST_PTR for efficient memory and Device-to-host communication
			std::cout << "Creating Buffers[" << d << "] [" << k << "]..." << std::endl;
            // [Temporary], need to change this to CL_MEM_USE_HOST_PTR type for efficient memory and Device-to-host communication
			OCL_CHECK(err, buffer_trmult_reduced[d][k] = cl::Buffer(contexts[d], CL_MEM_ALLOC_HOST_PTR | CL_MEM_READ_ONLY, matrix_size_bytes, NULL, &err));
			OCL_CHECK(err, buffer_L[d][k] = cl::Buffer(contexts[d], CL_MEM_ALLOC_HOST_PTR | CL_MEM_READ_ONLY, vector_size_bytes, NULL, &err));
			OCL_CHECK(err, buffer_uhat_i[d][k] = cl::Buffer(contexts[d], CL_MEM_USE_HOST_PTR	| CL_MEM_WRITE_ONLY, vector_size_bytes, hw_uhat_i[d][k].data(), &err));
            OCL_CHECK(err, buffer_R[d][k] = cl::Buffer(contexts[d], CL_MEM_ALLOC_HOST_PTR | CL_MEM_READ_ONLY, vector_size_bytes, NULL, &err));
		}
    }

    //TODO: Avoid creating new arrays and memcpy
    real * trmult_reduced_ptr[NUM_DEVICES][NUM_KERNELS];
	real * L_ptr[NUM_DEVICES][NUM_KERNELS];
    real * R_ptr[NUM_DEVICES][NUM_KERNELS];

    for (int d = 0; d < NUM_DEVICES; d++) {
		for (int k = 0; k < NUM_KERNELS; k++) {
			OCL_CHECK(err, err = kernels[d][k].setArg(0, tol));
			OCL_CHECK(err, err = kernels[d][k].setArg(1, buffer_trmult_reduced[d][k]));
			OCL_CHECK(err, err = kernels[d][k].setArg(2, buffer_L[d][k]));
			OCL_CHECK(err, err = kernels[d][k].setArg(3, L_exp));
			OCL_CHECK(err, err = kernels[d][k].setArg(4, buffer_uhat_i[d][k]));
            OCL_CHECK(err, err = kernels[d][k].setArg(5, buffer_R[d][k]));
            OCL_CHECK(err, err = kernels[d][k].setArg(6, R_exp));
			std::cout << "Comleted Setting Arguments"<< std::endl;
			// L = (real *) queues[d].enqueueMapBuffer(buffer_L[d][k], CL_TRUE, CL_MAP_WRITE, 0, NPOSLAND);
			// R = (real *) queues[d].enqueueMapBuffer(buffer_R[d][k], CL_TRUE, CL_MAP_WRITE, 0, NPOSLAND);
			// trmult_reduced = (real *) queues[d].enqueueMapBuffer(buffer_trmult_reduced[d][k], CL_TRUE, CL_MAP_WRITE, 0, (NPOSLAND * NPOSLAND));
            trmult_reduced_ptr[d][k] = (real *) queues[d].enqueueMapBuffer(buffer_trmult_reduced[d][k], CL_TRUE, CL_MAP_WRITE, 0, (NPOSLAND * NPOSLAND));
            L_ptr[d][k] = (real *) queues[d].enqueueMapBuffer(buffer_L[d][k], CL_TRUE, CL_MAP_WRITE, 0, NPOSLAND);
			R_ptr[d][k] = (real *) queues[d].enqueueMapBuffer(buffer_R[d][k], CL_TRUE, CL_MAP_WRITE, 0, NPOSLAND);
		}
	}

    for(int i=0; i<COMP_PER_DEVICE; i++){	

        /* copy the initialized data to new variables*/
		for(int d=0; d<NUM_DEVICES; d++){
			for (int k = 0; k < NUM_KERNELS; k++) {

            // init_all(&env[d][k], &in[d][k], &vars[d][k]);

            memcpy(trmult_reduced_ptr[d][k], trmult_reduced, matrix_size_bytes);
            memcpy(L_ptr[d][k], L, vector_size_bytes);
            memcpy(R_ptr[d][k], R, vector_size_bytes);

            if(i == 0){
            OCL_CHECK(err,
                err = queues[d].enqueueMigrateMemObjects( {
                    buffer_trmult_reduced[d][k], buffer_L[d][k], buffer_R[d][k] }, 
                    0 /* 0 means from host*/, nullptr, &memory_read_events[d][k][0])); 
            }
            else{
            OCL_CHECK(err,
                err = queues[d].enqueueMigrateMemObjects( {
                    buffer_trmult_reduced[d][k], buffer_L[d][k], buffer_R[d][k]  },  
                0 /* 0 means from host*/, &memory_write_events[d][k], &memory_read_events[d][k][0])); 
            }

            // ----------------------------------------
            // Step 2: Submit Kernels for Execution
            // ----------------------------------------
            printf("Enqueing Task\n");
            OCL_CHECK(err, 
                err = queues[d].enqueueTask(kernels[d][k], &memory_read_events[d][k], 
                &task_events[d][k][0]));
            // --------------------------------------------------
            // Step 2: Copy Results from Device Global Memory to Host
            // --------------------------------------------------
            printf("Migrating buffers from kernel\n");
            OCL_CHECK(err,
                err = queues[d].enqueueMigrateMemObjects( {buffer_uhat_i[d][k]}, 
                CL_MIGRATE_MEM_OBJECT_HOST, &task_events[d][k], &memory_write_events[d][k][0]));
			}
		}

        for (int d = 0; d < NUM_DEVICES; d++) {
			queues[d].finish();    
			// std::cout << "New kernel flush time is: " << new_krnl_flush.latency() * double(1e-9) << "s." << std::endl;
		}

        //copy the results back
		for (int d = 0; d < NUM_DEVICES; d++) {
			for(int k=0; k < NUM_KERNELS; k++){

				FILE *cfile;
				char FileName[512];
				printf("Migrating buffers from kernel\n"); 
                sprintf(FileName, "uhat_out_from_i%d_d%d_k%d.txt", i, d, k);
                cfile = fopen(FileName, "w");
                for(int i=0; i<NPOSLAND; i++){
                    fprintf(cfile, "%.15lf \n", hw_uhat_i[d][k][i]);
                }
                fclose(cfile);    
            }
        }

        // --------------------------------------------------
		// Step 3: Release Allocated Resources
		// --------------------------------------------------
		// for(int d=0; d<NUM_DEVICES; d++){
		// 	for (int k = 0; k < NUM_KERNELS; k++) {
		// 		free_all(&in[d][k]); 
		// 	}
		// }
	}

}

cl::Program load_cl2_binary(cl::Program::Binaries bins, cl::Device device, cl::Context context) {
    cl_int err;
    std::vector<cl::Device> devices(1, device);
    OCL_CHECK(err, cl::Program program(context, devices, bins, nullptr, &err));
    return program;
}
