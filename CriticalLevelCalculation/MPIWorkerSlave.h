#ifndef MPI_WORKER_SLAVE_H_
#define MPI_WORKER_SLAVE_H_

#include "Include.h"
#include "MPIWorker.h"

class MPIWorkerSlave : public MPIWorker
{
public:
	MPIWorkerSlave(MPIManager* mpi);
	~MPIWorkerSlave(void);

	virtual void run();

};

#endif //MPI_WORKER_SLAVE_H_