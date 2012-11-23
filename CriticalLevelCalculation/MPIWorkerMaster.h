/*
 * MPIWorkerMaster.h
 *
 *      Author: Alex
 */

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

/**
 * Master MPI Worker
 */
class MPIWorkerMaster : public MPIWorker
{
public:
	/**
	 * @param mpi
	 */
	MPIWorkerMaster(MPIManager* mpi);
	~MPIWorkerMaster(void);

	/**
	 * Run master job
	 */
	void run();
private:
	/**
	 * Rank of the master
	 */
	static const int REQUEST_TASKS_NUM = 10000;

	std::queue<int> mSlaveQueue;
	std::vector<int> mSlaveTasksCount;
	int mSlaveRunningTasks;

	/**
	 * Initialize slaves with ProjectInfo
	 * @param projectInfo
	 */
	void initSlaves(ProjectInfo projectInfo);
	/**
	 * Build flight path
	 * @param projectInfo
	 * @param flights
	 */
	void buildFlightsPathsParallel(ProjectInfo &projectInfo, std::vector<Flight> &flights);
	/**
	 * @param projectInfo
	 * @return total number of project spaces that needs to be calculated
	 */
	int calcNumberOfTasks(ProjectInfo &projectInfo);
	/**
	 * Send task to slave
	 * @param projectSpace
	 */
	void sendTask( ProjectSpace projectSpace );
	/**
	 * Collect results from slaves
	 * @param degree
	 */
	void collectSlaveResults(CriticalDegree &degree);
	/**
	 * Send slaves finish message
	 */
	void sendSlavesFinishSignal();
	/**
	 * Print final result
	 * @param degree
	 */
	void printResult(CriticalDegree &degree);
};

#endif //MPI_WORKER_MASTER_H_
