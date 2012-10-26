#include "MPIWorkerMaster.h"


MPIWorkerMaster::MPIWorkerMaster(MPIManager* mpi, const Cell &spaceSize,const Cell &cellSize)
	: MPIWorker(mpi,spaceSize,cellSize)
{
}


MPIWorkerMaster::~MPIWorkerMaster(void)
{
}

void MPIWorkerMaster::run()
{
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

		if (mSlaveQueue.size() > 0) {
			sendTask(projectSpace);
		} else {
			executeTask(projectSpace,degree);
		}

		checkQueues();

		break;
	}

	printResult(degree);
}

void MPIWorkerMaster::printResult(CriticalDegree& degree) {
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

void MPIWorkerMaster::sendTask( ProjectSpace projectSpace )
{
	Profiler::getInstance().start("Serialize project space");
	std::vector<int> serialized = projectSpace.serialize();
	Profiler::getInstance().finish();

	int slaveId = mSlaveQueue.front();
	mSlaveQueue.pop();
	mMpi->sendIntArray(slaveId, serialized);

/*	ProjectSpace newSpace(mSpaceSize, mCellSize);
	Profiler::getInstance().start("Deserialize project space");
	newSpace.deserialize(size,a);
	Profiler::getInstance().finish();
*/
}

void MPIWorkerMaster::executeTask( ProjectSpace projectSpace, CriticalDegree& degree )
{
	CriticalLevelDetector detector(projectSpace);
	CriticalLevel level = detector.detect();

	Profiler::getInstance().start("Add level to degree");
	degree.addCriticalLevel(level);
	Profiler::getInstance().finish();
}

void MPIWorkerMaster::checkQueues()
{

}
