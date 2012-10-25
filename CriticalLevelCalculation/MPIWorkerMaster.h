#ifndef MPI_WORKER_MASTER_H_
#define MPI_WORKER_MASTER_H_

#include "Include.h"
#include "MPIWorker.h"

#include "FlightDataReader.h"
#include "ProjectSpaceBuilder.h"
#include "CriticalLevelDetector.h"
#include "FlightDataReaderMemCache.h"
#include "CriticalDegree.h"


class MPIWorkerMaster : public MPIWorker
{
public:
	MPIWorkerMaster(MPIManager* mpi,const Cell &spaceSize,const Cell &cellSize);
	~MPIWorkerMaster(void);

	void run();

};

#endif //MPI_WORKER_MASTER_H_