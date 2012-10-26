#ifndef MPI_WORKER_FACTORY_H_
#define MPI_WORKER_FACTORY_H_

#include "MPIWorker.h"
#include "MPIWorkerMaster.h"
#include "MPIWorkerSlave.h"

class MPIWorkerFactory {
public:
	static MPIWorker* create(MPIManager* mpi, const Cell &spaceSize,const Cell &cellSize);

};

MPIWorker* MPIWorkerFactory::create( MPIManager* mpi, const Cell &spaceSize,const Cell &cellSize )
{
	if (mpi->getCommRank() == MPIManager::MASTER_RANK) {
		return new MPIWorkerMaster(mpi,spaceSize,cellSize);
	} else {
		return new MPIWorkerSlave(mpi,spaceSize,cellSize);
	}
}

#endif //MPI_WORKER_FACTORY_H_