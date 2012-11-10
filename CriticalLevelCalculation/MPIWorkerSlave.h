#ifndef MPI_WORKER_SLAVE_H_
#define MPI_WORKER_SLAVE_H_

#include "Include.h"
#include "MPIWorker.h"
#include "ProjectSpace.h"

class MPIWorkerSlave : public MPIWorker
{
public:
	MPIWorkerSlave(MPIManager* mpi);
	~MPIWorkerSlave(void);

	void run();
private:
	Cell mSpaceSize;
	Cell mCellSize;
};

#endif //MPI_WORKER_SLAVE_H_