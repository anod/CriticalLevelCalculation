#ifndef I_MPI_WORKER_H_
#define I_MPI_WORKER_H_

#include "Include.h"

class MPIManager;

class MPIWorker
{
public:
	MPIWorker(MPIManager* mpi, const Cell &spaceSize,const Cell &cellSize);
	virtual void run() = 0;
	virtual ~MPIWorker(void) {}
protected:
	Cell mSpaceSize;
	Cell mCellSize;
	MPIManager* mMpi; 
};

#endif //I_MPI_WORKER_H_