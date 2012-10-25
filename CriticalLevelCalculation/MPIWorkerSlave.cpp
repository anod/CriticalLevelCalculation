#include "MPIWorkerSlave.h"

MPIWorkerSlave::MPIWorkerSlave(MPIManager* mpi,const Cell &spaceSize,const Cell &cellSize)
	: MPIWorker(mpi,spaceSize,cellSize)
{
}


MPIWorkerSlave::~MPIWorkerSlave(void)
{
}

void MPIWorkerSlave::run()
{

}
