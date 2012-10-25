#include "MPIWorkerMaster.h"


MPIWorkerMaster::MPIWorkerMaster(const Cell &spaceSize,const Cell &cellSize)
	: MPIWorker(spaceSize,cellSize)
{
}


MPIWorkerMaster::~MPIWorkerMaster(void)
{
}

void MPIWorkerMaster::run()
{
	CriticalLevel level;
	Profiler::getInstance().setEnabled(true);

	std::ifstream fileStream;
	FlightDataReader reader(&fileStream, "c:\\data.txt");
	FlightDataReaderMemCache readerCached(&reader);

	std::cout << "Preload data..." << std::endl;
	Profiler::getInstance().start("Read file");
	readerCached.preloadCache();
	Profiler::getInstance().finish();

	ProjectSpaceBuilder builder(mSpaceSize, mCellSize, &readerCached);
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
