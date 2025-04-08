#include "app.h"
using std::array;
using std::map;
using std::vector;
int main(){
	#if DETAILED_PERF_METRICS
	stopwatch total_time;
	stopwatch write_results_time;
	#endif

	// Start the stopwatch for measuring total time
	#if DETAILED_PERF_METRICS
	total_time.start();
	#endif

    for(int i = 0; i < N_MODEL; i++) { 

		env_t env;
		vars_t vars;
		input_t in;
		out_t out;
		int hw_iter[500] = {0};

		init_all(&env, &in, &vars);

		runOncpu(&env, &vars, in.agshock, in.idshock, &out, hw_iter);
	
	// PRINTING THE RESULTS
	/*
		#if DETAILED_PERF_METRICS
		write_results_time.start();
		#endif 

		FILE *cfile;
		char FileName[512];
		printf("Migrating buffers from kernel\n");
		sprintf(FileName, "%sserial-cpu_nKM%d-nk%d.txt", CPU_KP_OUT_FILE, NKM_GRID, NKGRID);
		cfile = fopen(FileName, "w");
		for(int i=0; i<NSTATES; i++){
			fprintf(cfile, "%.15lf \n", out.kprime[i]);
		}
		fclose(cfile);

		printf("Total EGM iter: %d\n", total_egm_iter);
*/ 

		#if DETAILED_PERF_METRICS
		write_results_time.stop();
		#endif 
       
		// Deallocate Memory
		free_all(&in);
    }
   
	// Free Memory
	#if DETAILED_PERF_METRICS
	total_time.stop();
	#endif

	double tot_time = total_time.latency() * double(1e-9);
//-----------------------------------------------Save results-----------------------------------------------
	// Save total time in .txt file
	std::cout << "Total latency of the loop is: " << total_time.latency()* double(1e-9) << "s." << std::endl;
	std::cout << "Total time to write results is: " << write_results_time.latency()*double(1e-9) << "s." << std::endl;

	/* MODIFY THIS IF YOU NEED TO PRINT STUFF
	FILE *cfile;
	char FileName[512];
	sprintf(FileName, "%snKM%d-nk%d-time-tot.txt", CPU_EXEC_OUT_FILE, NKM_GRID, NKGRID);
	cfile = fopen(FileName, "w");
	fprintf(cfile, "%.15lf \n", tot_time);
	fclose(cfile);
    */
	return 0;
}

