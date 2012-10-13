#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

#include "OpenMP.h"
#include "FlightDataReader.h"
#include "ProjectSpaceBuilder.h"
#include "Point.h"

#define SPACE_SIZE_A 500
#define SPACE_SIZE_B 500
#define SPACE_SIZE_m 10
#define SPACE_SIZE_n 10

void run() 
{
	std::ifstream fileStream;
	FlightDataReader reader(fileStream, "data.txt");
	ProjectSpaceBuilder builder(Point(SPACE_SIZE_A,SPACE_SIZE_B),Point(SPACE_SIZE_m,SPACE_SIZE_n), reader);

	while(builder.nextTime()) {
		ProjectSpace projectSpace = builder.build();
		std::cout << projectSpace.dump().str() << std::endl;
	}

}


int main(int argc, char *argv[])
{

   int TID = omp_get_thread_num();
   printf("Thread ID of the master thread is %d\n",TID);

#pragma omp parallel
{
   int TID = omp_get_thread_num();

   printf("In parallel region - Thread ID is %d\n",TID);
}

///////////
	try {
		run();
	} catch(std::exception& caught){
		std::cout<<" [Exception] "<<caught.what()<<std::endl;
	}
	system("pause");
	return(0);
}