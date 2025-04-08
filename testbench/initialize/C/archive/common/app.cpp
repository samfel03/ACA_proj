#define SERIAL_CPU_MODE 1
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
		int hw_iter[500] = {0};
		init_all(&env);
	
		#if DETAILED_PERF_METRICS
		write_results_time.stop();
		#endif 
       
		// Deallocate Memory
		free_all(&env);
    }
   
   //printf("hw_iter=%d\n",hw_iter[0]);
	// Free Memory
	#if DETAILED_PERF_METRICS
	total_time.stop();
	double tot_time = total_time.latency() * double(1e-9);
//-----------------------------------------------Save results-----------------------------------------------
	// Save total time in .txt file
	std::cout << "Total latency of the loop is: " << total_time.latency()* double(1e-9) << "s." << std::endl;
	std::cout << "Total time to write results is: " << write_results_time.latency()*double(1e-9) << "s." << std::endl;
	#endif


	return 0;
}

