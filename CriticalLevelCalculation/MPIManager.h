#ifndef MPI_MANAGER_H_
#define MPI_MANAGER_H_

#include "Include.h"
#include <mpi.h>
#include "MPIWorker.h"
#include "MPIWorkerMaster.h"
#include "MPIWorkerSlave.h"

class MPIManager
{
public:
	MPIManager(void);
	~MPIManager(void);
	void init(int argc,char *argv[]);
	MPIWorker* createWorker(const Cell &spaceSize,const Cell &cellSize);
	void finalize();
	int getCommSize() const { return mCommSize; }
	int getCommRank() const { return mCommRank; }
private:
	static const int MASTER_RANK = 0;

	int mCommRank;
	int mCommSize;
	char mProcessorName[MPI_MAX_PROCESSOR_NAME];
};

#endif //MPI_MANAGER_H_