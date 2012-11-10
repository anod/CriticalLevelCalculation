#include "MPIWorkerMaster.h"


MPIWorkerMaster::MPIWorkerMaster(MPIManager* mpi)
	: MPIWorker(mpi)
{
}


MPIWorkerMaster::~MPIWorkerMaster(void)
{
}

void MPIWorkerMaster::run()
{
	Profiler::getInstance().setEnabled(true);

	std::ifstream fileStream;
	FlightDataReader reader(&fileStream, "c:\\basic1.txt");
	FlightDataReaderMemCache readerCached(&reader);

	std::cout << "Preload data..." << std::endl;
	Profiler::getInstance().start("Read data");
	readerCached.preloadCache();
	Profiler::getInstance().finish();

	//
	initSlaves(readerCached.getSpaceSize(), readerCached.getCellSize());

	ProjectSpaceBuilder builder(readerCached.getSpaceSize(), readerCached.getCellSize(), &readerCached);
	CriticalDegree degree;

	std::cout << "Processing..." << std::endl;
	//TODO init mSlaveQueue
	while(builder.nextTime()) {
		Profiler::getInstance().start("Build project space");
		ProjectSpace projectSpace = builder.build();
		Profiler::getInstance().finish();
		std::cout << "Processing space " << projectSpace.getTime() << std::endl;

		// Have free workers - LoadBalancing
		if (mSlaveQueue.size() > 0) {
			sendTask(projectSpace);
		} else {
			executeTask(projectSpace,degree);
		}

		checkQueues(degree);

	//	break;
	}
	// sendFinishSignal
	
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
	CriticalLevel level1, level2;
	CriticalLevelDetector detector(projectSpace);
	Profiler::getInstance().start("Detect critical level - parallel");
	level1 = detector.detectParallel();
	Profiler::getInstance().finish();

	Profiler::getInstance().start("Detect critical level - serial");
	level2 = detector.detectSerial();
	Profiler::getInstance().finish();

	Profiler::getInstance().start("Add level to degree");
	degree.addCriticalLevel(level1);
	Profiler::getInstance().finish();
}

void MPIWorkerMaster::checkQueues(CriticalDegree& degree)
{
	while (mMpi->hasIntArrayResult()) {
		std::vector<int> data = mMpi->getIntArray();
		CriticalLevel level = CriticalLevelSerializer::deserialize(data);
		degree.addCriticalLevel(level);
		mSlaveQueue.push(mMpi->getLastResponseSource());
	}
}

void MPIWorkerMaster::initSlaves(const Cell &spaceSize,const Cell &cellSize)
{
	int numtasks = mMpi->getCommSize();
	std::cout << "Number of slaves: " << (numtasks - 1) << std::endl;
	if (numtasks > 1) {

		std::vector<int> initData;
		initData.push_back(spaceSize.x);
		initData.push_back(spaceSize.y);
		initData.push_back(cellSize.x);
		initData.push_back(cellSize.y);

		for (int id=1; id<numtasks; id++) {
			mMpi->sendIntArray(id, initData);
			mSlaveQueue.push(id);
		}
	}
}
