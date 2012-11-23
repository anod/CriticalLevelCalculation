/*
 * MPIWorkerSlave.h
 *
 *      Author: Alex
 */

#ifndef MPI_WORKER_SLAVE_H_
#define MPI_WORKER_SLAVE_H_

#include "Include.h"
#include "MPIWorker.h"

/**
 * Slave MPI worker
 */
class MPIWorkerSlave : public MPIWorker
{
public:
	/**
	 * @param mpi
	 */
	MPIWorkerSlave(MPIManager* mpi);
	~MPIWorkerSlave(void);

	/**
	 * Executes slave job
	 */
	void run();

private:
	ProjectInfo mProjectInfo;
	/**
	 * Total number of processed tasks
	 */
	int mProgress;
	/**
	 * Receive ProjectInfo from Master
	 */
	void receiveInitData();
	/**
	 * Checks if master sent exit code
	 * @param spaceData
	 * @return
	 */
	bool checkExitCode( std::vector<int> spaceData );
	/**
	 * Send result of calulation back to master
	 * @param level
	 */
	void sendResult( CriticalLevel& level );
};

#endif //MPI_WORKER_SLAVE_H_
