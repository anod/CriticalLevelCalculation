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
	
	std::vector<int> data=mMpi->recvIntArray();
	ProjectSpace space;
	
	//mMpi->hasIntArrayResult();
	
	//receiveTask();
	//executeTask();
	//sendResult();
}
