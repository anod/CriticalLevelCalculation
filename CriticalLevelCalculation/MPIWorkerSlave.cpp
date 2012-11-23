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

	mProgress = 1;
	while(true) {
		std::vector<int> spaceData = mMpi->recvIntArray();
		if (checkExitCode(spaceData)) {
			echo("Exit code received.");
			break;
		}
		ProjectSpace projectSpace(mProjectInfo.spaceSize, mProjectInfo.cellSize);
		projectSpace.deserialize(spaceData);

		CriticalLevel level = executeTask(projectSpace);
		sendResult(level);
		if (mProgress % 10000 == 0) {
			echo (MakeString() << " Progress: " << mProgress);
		}
		mProgress++;
	}
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


void MPIWorkerSlave::sendResult( CriticalLevel& level )
{
	std::vector<int> serialized = CriticalLevelSerializer::serialize(level);
	mMpi->sendIntArray(MPIManager::MASTER_RANK, serialized);
}
