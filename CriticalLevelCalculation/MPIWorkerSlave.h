#ifndef MPI_WORKER_SLAVE_H_
#define MPI_WORKER_SLAVE_H_

#include "Include.h"
#include "MPIWorker.h"
#include "ProjectSpace.h"
#include "CriticalLevelDetector.h"
#include "CriticalLevelSerializer.h"

class MPIWorkerSlave : public MPIWorker
{
public:
	MPIWorkerSlave(MPIManager* mpi);
	~MPIWorkerSlave(void);

	void run();

private:
	ProjectInfo mProjectInfo;
	void receiveInitData();
	bool checkExitCode( std::vector<int> spaceData );
	CriticalLevel executeTask( ProjectSpace& projectSpace );
	void sendResult( CriticalLevel& level );
};

#endif //MPI_WORKER_SLAVE_H_