#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Include.h"
#include "FlightDataReader.h"
#include "ProjectSpaceBuilder.h"
#include "CriticalLevelDetector.h"
#include "FlightDataReaderMemCache.h"
#include "CriticalDegree.h"

#include "TestRunner.h"

#define SPACE_SIZE_A 500
#define SPACE_SIZE_B 500
#define SPACE_SIZE_m 10
#define SPACE_SIZE_n 10

void run() 
{
	CriticalLevel level;
	Profiler::getInstance().setEnabled(true);

	std::ifstream fileStream;
	FlightDataReader reader(&fileStream, "data.txt");
	FlightDataReaderMemCache readerCached(&reader);

	Profiler::getInstance().start("Read file");
	readerCached.preloadCache();
	Profiler::getInstance().finish();

	ProjectSpaceBuilder builder(Cell(SPACE_SIZE_A,SPACE_SIZE_B),Cell(SPACE_SIZE_m,SPACE_SIZE_n), &readerCached);
	CriticalDegree degree;

	while(builder.nextTime()) {
		Profiler::getInstance().start("Build project space");
		ProjectSpace projectSpace = builder.build();
		Profiler::getInstance().finish();

		CriticalLevelDetector detector(projectSpace);

		Profiler::getInstance().start("Detect critical level");
		level = detector.detect();
		Profiler::getInstance().finish();

		Profiler::getInstance().start("Add level to degree");
		degree.addCriticalLevel(level);
		Profiler::getInstance().finish();
	}

	int maxDegreeFlight = degree.getMaxCriticalLevelFlight();
	std::cout << std::endl << "Max Critical Degree fro flight #" << maxDegreeFlight << " : " << std::endl;
	FlightList critList = degree.getFlightList(maxDegreeFlight);
	FlightList::const_iterator it;
	for( it = critList.begin(); it != critList.end(); it++) {
		if (it != critList.begin()) {
			std::cout << ", ";
		}
		std::cout << (*it);
	}
	std::cout << std::endl;

	std::cout << Profiler::getInstance().dump().str();

}

void tests() {
	TestRunner tests;
	tests.run();
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
		//tests();
	} catch(std::exception& caught){
		std::cout<<" [Exception] "<<caught.what()<<std::endl;
	}
	system("pause");
	return(0);
}