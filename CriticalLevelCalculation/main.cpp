#include <stdio.h>
#include <stdlib.h>

#ifdef _OPENMP
   #include <omp.h>
   #define TRUE  1
   #define FALSE 0
#else
   #define omp_get_thread_num() 0
#endif

#define LENGTH 1001
#define ITERATIONS 1000

int main(int argc, char *argv[])
{

   int TID = omp_get_thread_num();
   printf("Thread ID of the master thread is %d\n",TID);

#ifdef _OPENMP
   (void) omp_set_dynamic(FALSE);
   if (omp_get_dynamic()) {printf("Warning: dynamic adjustment of threads has been set\n");}
   (void) omp_set_num_threads(4);
#endif

#pragma omp parallel
{
   int TID = omp_get_thread_num();

   printf("In parallel region - Thread ID is %d\n",TID);
} /*-- End of parallel region --*/

	float xi[LENGTH] = {0};
	float gi[LENGTH] = {0};
	xi[0] = gi[0] = 0.5;
	xi[LENGTH-1] = gi[LENGTH-1] = 250;
	bool run = false;

	int iteration = 0;
	do {
		iteration++;
		run = false;
#pragma omp parallel
{
		for (int i=1; i<LENGTH-1; i++) {
			gi[i]=0.5*(xi[i-1]+xi[i+1]);
		}
}
		for (int i=1; i<LENGTH-1; i++) {
			xi[i]=gi[i];
			if (xi[i] < 0.0001) {
				run = true;
			}
		}

	} while(run && iteration < ITERATIONS);

	for (int i=0; i<LENGTH; i++) {
		if (i%11==0) {
			printf("\n");
		}
		printf("%7.3f ",xi[i]);
	}
	printf("\n");

	system("pause");
	return(0);
}