// Using OpemnMP library write a program in which master thread count the total no. of threads created, and others will print their thread numbers.

#include <stdio.h>
#include <omp.h>

int main() {
	int total_threads, thread_id;

	// Start parallel region
	#pragma omp parallel private(thread_id)
	{
    	thread_id = omp_get_thread_num();
    	// Only master thread counts total number of threads
    	#pragma omp master
    	{
        	total_threads = omp_get_num_threads();
        	printf("Total number of threads: %d\n", total_threads);
    	}
    	printf("Thread number: %d\n", thread_id);
	}

	return 0;
}
