#ifndef MPI_WORKER_MASTER_H_
#define MPI_WORKER_MASTER_H_

#include "Include.h"

#include "FlightDataReader.h"
#include "ProjectSpaceBuilder.h"
#include "CriticalLevelDetector.h"
#include "CriticalDegree.h"
#include "CriticalLevelSerializer.h"
#include "FlightPathBuilder.h"

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
	void collectSlaveResults(CriticalDegree& degree);
	void initSlaves(ProjectInfo projectInfo);
	void sendSlavesFinishSignal();
};

#endif //MPI_WORKER_MASTER_H_