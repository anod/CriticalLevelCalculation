#ifndef OPENMP_H_
#define OPENMP_H_

#ifdef _OPENMP
	#include <omp.h>
	#define TRUE  1
	#define FALSE 0
#else
	#define omp_get_thread_num() 0
#endif

#endif // OPENMP_H_