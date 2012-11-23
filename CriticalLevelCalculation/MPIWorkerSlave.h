#ifndef MPI_WORKER_SLAVE_H_
#define MPI_WORKER_SLAVE_H_

#include "Include.h"
#include "MPIWorker.h"

class MPIWorkerSlave : public MPIWorker
{
public:
	MPIWorkerSlave(MPIManager* mpi);
	~MPIWorkerSlave(void);

	void run();

private:
	ProjectInfo mProjectInfo;
	int mProgress;
	void receiveInitData();
	bool checkExitCode( std::vector<int> spaceData );
	void sendResult( CriticalLevel& level );
};

#endif //MPI_WORKER_SLAVE_H_