#ifndef I_MPI_WORKER_H_
#define I_MPI_WORKER_H_

#include "Include.h"
#include "MPIManager.h"

class MPIWorker
{
public:
	MPIWorker(MPIManager* mpi);
	virtual void run() = 0;
	virtual ~MPIWorker(void) {}
protected:
	MPIManager* mMpi; 
};

#endif //I_MPI_WORKER_H_