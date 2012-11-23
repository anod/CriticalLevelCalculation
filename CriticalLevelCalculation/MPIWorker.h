#ifndef I_MPI_WORKER_H_
#define I_MPI_WORKER_H_

#include "Include.h"
#include "MPIManager.h"
#include "ProjectSpace.h"
#include "CriticalLevelDetector.h"
#include "CriticalLevelSerializer.h"

class MPIWorker
{
public:
	MPIWorker(MPIManager* mpi);
	virtual void run() = 0;
	virtual ~MPIWorker(void) {}
protected:
	static const int EXIT_CODE = -1;
	MPIManager* mMpi;
	void echo(std::string message);
	CriticalLevel executeTask( ProjectSpace& projectSpace );
};

#endif //I_MPI_WORKER_H_