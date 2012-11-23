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
	//FlightDataReader reader(&fileStream, "c:\\basic1.txt");
	//FlightDataReader reader(&fileStream, "c:\\basic2.txt");
	//FlightDataReader reader(&fileStream, "c:\\big1.txt");
	FlightDataReader reader(&fileStream, "c:\\big2.txt");

	echo(MakeString() << "Load data... (" << reader.getFileName() << ")");
	reader.open();
	reader.readHeader();

	// Read flights data
	Profiler::getInstance().start("Read flights");
	std::vector<Flight> flights = reader.readFlights();
	Profiler::getInstance().finish();

 	ProjectInfo projectInfo = reader.getProjectInfo();
	echo(MakeString() << "Project info: " << projectInfo.dump().str());

	// Init available slaves with project info (mSlaveQueue)
	initSlaves(projectInfo);

	// Build flight paths
	buildFlightsPathsParallel(projectInfo, flights);

	// Calculate Critical Degree
	ProjectSpaceBuilder builder(projectInfo, flights);

	// Caclulate total number of project spacess to be processed
	int numOfTasks = calcNumberOfTasks(projectInfo);

	echo(MakeString() << "Max number of threads: " << omp_get_max_threads());		
	echo(MakeString() << "Total number of tasks: " << numOfTasks);
	echo("Processing...");

	int progress = 1;
	Profiler::getInstance().start("Process project spaces");
	while(builder.nextTime()) {
		ProjectSpace projectSpace = builder.build();

		// LB - Have free workers send more tasks
		if (mSlaveQueue.size() > 0) {
			sendTask(projectSpace);
		} else { 
			CriticalLevel level = executeTask(projectSpace);
			degree.addCriticalLevel(level);
		}

		collectSlaveResults(degree);

		if (progress % 10000 == 0) {
			echo (MakeString() << " Progress: " << progress);
		}
		progress++;
	}
	Profiler::getInstance().finish();

	echo("Collect results from still running slaves.");
	while(mSlaveRunningTasks > 0) {
		collectSlaveResults(degree);
	}
	sendSlavesFinishSignal();
	
	printResult(degree);
}

void MPIWorkerMaster::buildFlightsPathsParallel(ProjectInfo &projectInfo, std::vector<Flight> &flights) {
	int flightsCount = flights.size();
	FlightPathBuilder fpBuilder(projectInfo);

	Profiler::getInstance().start("Build flights paths - parallel");
	#pragma omp parallel for
	for(int i=0; i< flightsCount; i++) {
		fpBuilder.build(flights[i]);
	}
	Profiler::getInstance().finish();
}

int MPIWorkerMaster::calcNumberOfTasks(ProjectInfo &projectInfo) {
	return (int)((double)(projectInfo.timeFinish - projectInfo.timeStart)/(double)projectInfo.timeStep);
}

void MPIWorkerMaster::sendTask( ProjectSpace projectSpace )
{
	std::vector<int> serialized = projectSpace.serialize();

	int slaveId = mSlaveQueue.front();
	mSlaveQueue.pop();

	mMpi->sendIntArray(slaveId, serialized);

	mSlaveRunningTasks++;

}

void MPIWorkerMaster::collectSlaveResults(CriticalDegree& degree)
{
	if (mMpi->getCommSize() == 1) {
		return;
	}
	while (mMpi->hasIntArrayResult()) {
		std::vector<int> data = mMpi->getIntArray();

		CriticalLevel level = CriticalLevelSerializer::deserialize(data);
		degree.addCriticalLevel(level);

		mSlaveQueue.push(mMpi->getLastResponseSource());
		mSlaveRunningTasks--;
	}
}

void MPIWorkerMaster::initSlaves(ProjectInfo projectInfo)
{
	int numworkers = mMpi->getCommSize();
	echo(MakeString() << "Number of slaves: " << (numworkers - 1));
	if (numworkers > 1) {
		std::vector<int> initData = projectInfo.serialize();

		for (int id=1; id<numworkers; id++) {
			mMpi->sendIntArray(id, initData);
			mSlaveQueue.push(id);
		}
	}
}

void MPIWorkerMaster::sendSlavesFinishSignal()
{
	int numtasks = mMpi->getCommSize();
	std::vector<int> exitData;
	exitData.push_back(EXIT_CODE);
	for (int id=1; id<numtasks; id++) {
		mMpi->sendIntArray(id, exitData);
	}
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
