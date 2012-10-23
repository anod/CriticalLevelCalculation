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

	std::cout << "Preload data..." << std::endl;
	Profiler::getInstance().start("Read file");
	readerCached.preloadCache();
	Profiler::getInstance().finish();

	ProjectSpaceBuilder builder(Cell(SPACE_SIZE_A,SPACE_SIZE_B),Cell(SPACE_SIZE_m,SPACE_SIZE_n), &readerCached);
	CriticalDegree degree;

	std::cout << "Processing..." << std::endl;
	while(builder.nextTime()) {
		Profiler::getInstance().start("Build project space");
		ProjectSpace projectSpace = builder.build();
		Profiler::getInstance().finish();

		std::cout << "Processing space " << projectSpace.getTime() << std::endl;

		CriticalLevelDetector detector(projectSpace);

		level = detector.detect();

		Profiler::getInstance().start("Add level to degree");
		degree.addCriticalLevel(level);
		Profiler::getInstance().finish();

		break;
	}

	int maxDegreeFlight = degree.getMaxCriticalLevelFlight();
	std::cout << std::endl << "Max Critical Degree flight #" << maxDegreeFlight << std::endl;
	FlightList critList = degree.getFlightList(maxDegreeFlight);
	std::cout << "Objects that did not see it - " << critList.size() << " : " << std::endl;
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


   try {
		run();
		//tests();
	} catch(std::exception& caught){
		std::cout<<" [Exception] "<<caught.what()<<std::endl;
	}
	system("pause");
	return(0);
}