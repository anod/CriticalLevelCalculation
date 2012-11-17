#include "MPIWorkerMaster.h"


MPIWorkerMaster::MPIWorkerMaster(MPIManager* mpi)
	: MPIWorker(mpi), mSlaveRunningTasks(0)
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

	echo("Load data...");
	reader.readHeader();

	// Read flights data
	Profiler::getInstance().start("Read flights");
	std::vector<Flight> flights = reader.readFlights();
	Profiler::getInstance().finish();

	ProjectInfo projectInfo = reader.getProjectInfo();

	// Init available s;aces with header data
	initSlaves(projectInfo);

	// Build flight paths
	FlightPathBuilder fpBuilder(projectInfo);
	for(size_t i=0; i<flights.size(); i++) {
		std::unordered_map<int,Cell> flightPath = fpBuilder.build(flights[i].getControlPoints());
		flights[i].setFlightPath(flightPath);
	}

	// Calculate Critical Degree

	ProjectSpaceBuilder builder(projectInfo, flights);
	CriticalDegree degree;

	echo("Processing...");
	//TODO init mSlaveQueue
	while(builder.nextTime()) {
		Profiler::getInstance().start("Build project space");
		ProjectSpace projectSpace = builder.build();
		Profiler::getInstance().finish();

		// Have free workers - LoadBalancing
		if (mSlaveQueue.size() > 0) {
			sendTask(projectSpace);
		} else {
			executeTask(projectSpace,degree);
		}

		echo("Collect results");
		collectSlaveResults(degree);

	//	break;
	}

	echo("Collect results from still running slaves");
	while(mSlaveRunningTasks > 0) {
		collectSlaveResults(degree);
	}
	sendSlavesFinishSignal();
	
	printResult(degree);
}

void MPIWorkerMaster::printResult(CriticalDegree& degree) {
	int maxDegreeFlight = degree.getMaxCriticalLevelFlight();
	std::stringstream result;
	result << "Max Critical Degree flight #" << maxDegreeFlight << std::endl;
	FlightList critList = degree.getFlightList(maxDegreeFlight);
	result << "Objects that did not see it - " << critList.size() << " : " << std::endl;
	FlightList::const_iterator it;
	for( it = critList.begin(); it != critList.end(); it++) {
		if (it != critList.begin()) {
			result << ", ";
		}
		result << (*it);
	}
	result << std::endl;

	result << Profiler::getInstance().dump().str();
	echo(result.str());
}

void MPIWorkerMaster::sendTask( ProjectSpace projectSpace )
{
	Profiler::getInstance().start("Serialize project space");
	std::vector<int> serialized = projectSpace.serialize();
	Profiler::getInstance().finish();

	int slaveId = mSlaveQueue.front();
	mSlaveQueue.pop();

	echo(MakeString() << "Send task to #" << slaveId);
	Profiler::getInstance().start("Send task to slave");
	mMpi->sendIntArray(slaveId, serialized);
	Profiler::getInstance().finish();

	mSlaveRunningTasks++;

}

void MPIWorkerMaster::executeTask( ProjectSpace projectSpace, CriticalDegree& degree )
{
	echo(MakeString() << "Execute task " << projectSpace.getTime());

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

void MPIWorkerMaster::collectSlaveResults(CriticalDegree& degree)
{
	if (mMpi->getCommSize() == 1) {
		return;
	}
	while (mMpi->hasIntArrayResult()) {
		std::vector<int> data = mMpi->getIntArray();
		echo(MakeString() << "Data received, size: " << data.size());
		CriticalLevel level = CriticalLevelSerializer::deserialize(data);
		degree.addCriticalLevel(level);
		mSlaveQueue.push(mMpi->getLastResponseSource());
		mSlaveRunningTasks--;
	}
}

void MPIWorkerMaster::initSlaves(ProjectInfo &projectInfo )
{
	int numtasks = mMpi->getCommSize();
	echo(MakeString() << "Number of slaves: " << (numtasks - 1));
	if (numtasks > 1) {

		std::vector<int> initData = projectInfo.serialize();

		for (int id=1; id<numtasks; id++) {
			mMpi->sendIntArray(id, initData);
			mSlaveQueue.push(id);
		}
	}
}

void MPIWorkerMaster::sendSlavesFinishSignal()
{
	int numtasks = mMpi->getCommSize();
	std::vector<int> exitData(1);
	exitData.push_back(EXIT_CODE);
	for (int id=1; id<numtasks; id++) {
		mMpi->sendIntArray(id, exitData);
	}
}
