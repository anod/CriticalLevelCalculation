#ifndef MPI_WORKER_FACTORY_H_
#define MPI_WORKER_FACTORY_H_

#include "MPIWorker.h"
#include "MPIWorkerMaster.h"
#include "MPIWorkerSlave.h"

class MPIWorkerFactory {
public:
	static MPIWorker* create(MPIManager* mpi);

};

MPIWorker* MPIWorkerFactory::create(MPIManager* mpi)
{
	if (mpi->getCommRank() == MPIManager::MASTER_RANK) {
		return new MPIWorkerMaster(mpi);
	} else {
		return new MPIWorkerSlave(mpi);
	}
}

#endif //MPI_WORKER_FACTORY_H_