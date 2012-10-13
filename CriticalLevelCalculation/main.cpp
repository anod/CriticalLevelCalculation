#include <stdio.h>
#include <stdlib.h>

#include "OpenMP.h"


int main(int argc, char *argv[])
{

   int TID = omp_get_thread_num();
   printf("Thread ID of the master thread is %d\n",TID);

#pragma omp parallel
{
   int TID = omp_get_thread_num();

   printf("In parallel region - Thread ID is %d\n",TID);
}

	system("pause");
	return(0);
}