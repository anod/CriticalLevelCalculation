#ifndef MPI_WORKER_MASTER_H_
#define MPI_WORKER_MASTER_H_

#include "Include.h"

#include "FlightDataReader.h"
#include "ProjectSpaceBuilder.h"
#include "CriticalLevelDetector.h"
#include "FlightDataReaderMemCache.h"
#include "CriticalDegree.h"
#include "CriticalLevelSerializer.h"

#include "MPIWorker.h"

class MPIWorkerMaster : public MPIWorker
{
public:
	MPIWorkerMaster(MPIManager* mpi);
	~MPIWorkerMaster(void);

	void run();
private:
	std::queue<int> mSlaveQueue;
	int mSlaveRunningTasks;
	void printResult(CriticalDegree& degree);
	void sendTask( ProjectSpace projectSpace );
	void executeTask( ProjectSpace projectSpace, CriticalDegree& degree );
	void collectSlaveResults(CriticalDegree& degree);
	void initSlaves(const Cell &spaceSize,const Cell &cellSize);
	void sendSlavesFinishSignal();
};

#endif //MPI_WORKER_MASTER_H_