#ifndef MPI_WORKER_MASTER_H_
#define MPI_WORKER_MASTER_H_

#include "Include.h"

#include "FlightDataReader.h"
#include "ProjectSpaceBuilder.h"
#include "CriticalLevelDetector.h"
#include "FlightDataReaderMemCache.h"
#include "CriticalDegree.h"

#include "MPIWorker.h"

class MPIWorkerMaster : public MPIWorker
{
public:
	MPIWorkerMaster(MPIManager* mpi,const Cell &spaceSize,const Cell &cellSize);
	~MPIWorkerMaster(void);

	void run();
private:
	std::queue<int> mSlaveQueue;
	void printResult(CriticalDegree& degree);
	void sendTask( ProjectSpace projectSpace );
	void executeTask( ProjectSpace projectSpace, CriticalDegree& degree );
	void checkQueues();
};

#endif //MPI_WORKER_MASTER_H_