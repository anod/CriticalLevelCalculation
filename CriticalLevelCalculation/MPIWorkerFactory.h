/*
 * MPIWorkerFactory.h
 *
 *      Author: Alex
 */

#ifndef MPI_WORKER_FACTORY_H_
#define MPI_WORKER_FACTORY_H_

#include "MPIWorker.h"
#include "MPIWorkerMaster.h"
#include "MPIWorkerSlave.h"

/**
 * Creates MPIWoker instance based on assigned MPI rank
 */
class MPIWorkerFactory {
public:
	/**
	 *
	 * @param mpi
	 * @return worker
	 */
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
