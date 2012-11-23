/*
 * MPIManager.h
 *
 *      Author: Alex
 */

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
	/**
	 * Create ne instance of MPI worker
	 * @param mpi
	 */
	MPIWorker(MPIManager* mpi);
	/**
	 * Executes current worker job
	 */
	virtual void run() = 0;
	virtual ~MPIWorker(void) {}
protected:
	/**
	 * Code indicates that worker need to finish its job
	 */
	static const int EXIT_CODE = -1;

	/**
	 * MPI Manager instance
	 */
	MPIManager* mMpi;

	/**
	 * Output message into stdout
	 * @param message
	 */
	void echo(std::string message);

	/**
	 * Executes project space calculation task
	 * @param projectSpace
	 * @return
	 */
	CriticalLevel executeTask( ProjectSpace& projectSpace );
};

#endif //I_MPI_WORKER_H_
