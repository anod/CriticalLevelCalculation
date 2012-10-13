#include <stdio.h>
#include <stdlib.h>

#include "OpenMP.h"
#include "FlightDataReader.h"
#include <iostream>
#include "ProjectSpace.h"

#define SPACE_SIZE_A 500
#define SPACE_SIZE_B 500
#define SPACE_SIZE_m 10
#define SPACE_SIZE_n 10

void run() 
{
	ProjectSpace projectSpace(Point(SPACE_SIZE_A,SPACE_SIZE_B),Point(SPACE_SIZE_m,SPACE_SIZE_n));

	FlightDataReader reader("data.txt");
	reader.open();
	while (reader.readNextControlPoint()) {
		Point p = reader.getCurrentControlPoint();
		int time = reader.getCurrentTime();

		std::cout << reader.getCurrentFlightNumber() << ": [" << p.x << "," << p.y << "] at " << time << std::endl;

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