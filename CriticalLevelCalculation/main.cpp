#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Include.h"
#include "FlightDataReader.h"
#include "ProjectSpaceBuilder.h"
#include "CriticalLevelDetector.h"
#include "FlightDataReaderMemCache.h"

#define SPACE_SIZE_A 500
#define SPACE_SIZE_B 500
#define SPACE_SIZE_m 10
#define SPACE_SIZE_n 10

void run() 
{
	std::ifstream fileStream;
	FlightDataReader reader(&fileStream, "data.txt");
	FlightDataReaderMemCache readerCached(&reader);
	ProjectSpaceBuilder builder(Point(SPACE_SIZE_A,SPACE_SIZE_B),Point(SPACE_SIZE_m,SPACE_SIZE_n), &readerCached);

	while(builder.nextTime()) {
		//clock_t begin = clock();

		ProjectSpace projectSpace = builder.build();

		//clock_t end = clock();
		//double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		//std::cout << projectSpace.getTime() << ": " << elapsed_secs << std::endl;
		//std::cout << projectSpace.dump().str() << std::endl;
		std::cout.flush();
		CriticalLevelDetector detector(projectSpace);
		detector.detect();
		return;
	}

}

void test() {
	std::cout << "1. Running InvolvedCellsSeeker Test" << std::endl;
	InvolvedCellsSeeker seeker(Point(10,10));
	std::vector<Point> result = seeker.seek(Point(3,4), Point(6,7));


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
		//run();
		test();
	} catch(std::exception& caught){
		std::cout<<" [Exception] "<<caught.what()<<std::endl;
	}
	system("pause");
	return(0);
}