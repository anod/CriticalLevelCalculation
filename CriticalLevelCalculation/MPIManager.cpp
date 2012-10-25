#include "MPIManager.h"


MPIManager::MPIManager(void)
	: mCommRank(MASTER_RANK), mCommSize(1)
{
}


MPIManager::~MPIManager(void)
{
}

void MPIManager::init(int argc,char *argv[])
{
	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&mCommRank);

	MPI_Comm_size(MPI_COMM_WORLD,&mCommSize);	

	int namelen;
	MPI_Get_processor_name(mProcessorName,&namelen);

}

void MPIManager::finalize()
{
	MPI_Finalize();
}

MPIWorker* MPIManager::createWorker(const Cell &spaceSize,const Cell &cellSize)
{
	if (mCommRank == MASTER_RANK) {
		return new MPIWorkerMaster(this,spaceSize,cellSize);
	} else {
		return new MPIWorkerSlave(this,spaceSize,cellSize);
	}
}
