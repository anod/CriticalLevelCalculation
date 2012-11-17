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

	CriticalDegree degree;
	std::ifstream fileStream;
	FlightDataReader reader(&fileStream, "c:\\basic1.txt");

	echo("Load data...");
	reader.open();
	reader.readHeader();

	// Read flights data
	echo("Read flights...");
	Profiler::getInstance().start("Read flights");
	std::vector<Flight> flights = reader.readFlights();
	Profiler::getInstance().finish();

 	ProjectInfo projectInfo = reader.getProjectInfo();

	// Init available slaves with project info
	initSlaves(projectInfo);

	// Build flight paths
	echo("Build flights paths...");
	int flightsCount = flights.size();
	FlightPathBuilder fpBuilder(projectInfo);

	Profiler::getInstance().start("Build flights path");
	#pragma omp parallel for schedule(dynamic)
	for(int i=0; i< flightsCount; i++) {
		fpBuilder.build(flights[i]);
	}
	Profiler::getInstance().finish();

	// Calculate Critical Degree
	ProjectSpaceBuilder builder(projectInfo, flights);

	//TODO init mSlaveQueue
	int numOfTasks = (int)((double)(projectInfo.timeFinish - projectInfo.timeStart)/(double)projectInfo.timeStep);
	echo(MakeString() << "Number of tasks: " << numOfTasks);
	echo("Processing...");
	int progress = 1;
	Profiler::getInstance().start("Process project space");
	while(builder.nextTime()) {
		ProjectSpace projectSpace = builder.build();

		// Have free workers - LoadBalancing
		if (mSlaveQueue.size() > 0) {
			sendTask(projectSpace);
		} else {
			executeTask(projectSpace,degree);
		}

		collectSlaveResults(degree);

		if (progress % 1000 == 0) {
			echo (MakeString() << " Progress: " << progress);
		}
		progress++;
	}
	Profiler::getInstance().finish();

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
	result << "Hidden " << degree.getTotalCount(maxDegreeFlight) << " times by " << critList.size() << " objects : " << std::endl;
	FlightList::const_iterator it;

	std::unordered_map<int, bool> alreadySeen;
	for( it = critList.begin(); it != critList.end(); it++) {
		int flightNum = (*it);
		if (!alreadySeen[flightNum]) {
			if (it != critList.begin()) {
				result << ", ";
			}
			result << (*it);
			alreadySeen[flightNum] = true;
		}
	}
	result << std::endl;

	result << Profiler::getInstance().dump().str();
	echo(result.str());
}

void MPIWorkerMaster::sendTask( ProjectSpace projectSpace )
{
	std::vector<int> serialized = projectSpace.serialize();

	int slaveId = mSlaveQueue.front();
	mSlaveQueue.pop();

	echo(MakeString() << "Send task to #" << slaveId);
	mMpi->sendIntArray(slaveId, serialized);

	mSlaveRunningTasks++;

}

void MPIWorkerMaster::executeTask( ProjectSpace projectSpace, CriticalDegree& degree )
{
	CriticalLevel level1;
	CriticalLevelDetector detector(projectSpace);

	level1 = detector.detectParallel();

//	level1 = detector.detectSerial();

	degree.addCriticalLevel(level1);
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
