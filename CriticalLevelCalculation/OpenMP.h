
#ifndef OPENMP_H_
#define OPENMP_H_

/**
 * Provide compatibility for builds without OpenMP
 */

#ifdef _OPENMP
	#include <omp.h>
	#define TRUE  1
	#define FALSE 0
#else
	#define omp_get_max_threads() 1
	#define omp_get_thread_num() 0
	#define omp_get_num_threads() 1
#endif

#endif // OPENMP_H_
