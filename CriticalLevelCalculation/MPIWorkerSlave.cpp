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
	
	std::vector<int> initData=mMpi->recvIntArray();
	mSpaceSize.x = initData[0];
	mSpaceSize.y = initData[1];
	mCellSize.x = initData[2];
	mCellSize.y = initData[3];

	std::cout << "[" << mMpi->getCommRank() << "] Slave initialized, Space size: " << mSpaceSize.dump().str() << ", Cell size: " << mCellSize.dump().str() << std::endl;

	ProjectSpace space(mSpaceSize, mCellSize);
	
	std::vector<int> spaceData = mMpi->recvIntArray();
	space.deserialize(spaceData);

	std::cout << "[" << mMpi->getCommRank() << "] Received project space: " << space.dump().str() << std::endl;
	//receiveTask();
	//executeTask();
	//sendResult();
}
