#include "MPIWorkerSlave.h"

MPIWorkerSlave::MPIWorkerSlave(MPIManager* mpi)
	: MPIWorker(mpi)
{
}


MPIWorkerSlave::~MPIWorkerSlave(void)
{
}

void MPIWorkerSlave::run()
{
	
	receiveInitData();
	echo("Slave initialized: " + mProjectInfo.dump().str());

	ProjectSpace projectSpace(mProjectInfo.spaceSize, mProjectInfo.cellSize);

	while(true) {
		std::vector<int> spaceData = mMpi->recvIntArray();
		if (checkExitCode(spaceData)) {
			echo("Exit code received.");
			break;
		}
		projectSpace.deserialize(spaceData);
		CriticalLevel level = executeTask(projectSpace);
		sendResult(level);
	}
	echo(Profiler::getInstance().dump().str());
}

void MPIWorkerSlave::receiveInitData()
{
	std::vector<int> initData=mMpi->recvIntArray();
	mProjectInfo.deserialize(initData);
}

bool MPIWorkerSlave::checkExitCode( std::vector<int> spaceData )
{
	return (spaceData.size() == 1 && spaceData[0] == EXIT_CODE);
}

CriticalLevel MPIWorkerSlave::executeTask( ProjectSpace& projectSpace )
{
	echo(MakeString() << "Execute task " << projectSpace.getTime());
	CriticalLevel level;
	CriticalLevelDetector detector(projectSpace);
	Profiler::getInstance().start("Detect critical level - serial");
	level = detector.detectSerial();
	Profiler::getInstance().finish();
	return level;
}

void MPIWorkerSlave::sendResult( CriticalLevel& level )
{
	std::vector<int> serialized = CriticalLevelSerializer::serialize(level);
	std::vector<int>::iterator it;
	mMpi->sendIntArray(MPIManager::MASTER_RANK, serialized);
}
