/*
 * MPIManager.h
 *
 *      Author: Alex
 */

#ifndef MPI_MANAGER_H_
#define MPI_MANAGER_H_

#include "Include.h"
#include <mpi.h>
/**
 * Class provides an easy API over MPI functions
 */
class MPIManager
{
public:
	/**
	 * Rank of the master
	 */
	static const int MASTER_RANK = 0;

	MPIManager(void);
	~MPIManager(void);
	/**
	 * Init MPI
	 */
	void init(int argc,char *argv[]);
	/**
	 * Call to MPI_Finalize 
	 */
	void finalize();
	/**
	 * Get number of workers
	 */
	int getCommSize() const { return mCommSize; }
	/**
	 * Rank of the current worker
	 */
	int getCommRank() const { return mCommRank; }
	/**
	 * Send one integer
	 * Blocking.
	 * @param dest - id of the MPI worker
	 * @param value
	 */
	void sendInt( int dest, int value);
	/**
	 * Receive one integer
	 * Blocking.
	 * @return value
	 */
	int recvInt();
	/**
	 * Send vector if integer to the destination
	 * Blocking.
	 * @param dest - id of the MPI worker
	 * @param arr - data
	 */
	void sendIntArray(int dest, std::vector<int> arr);
	/**
	 * Receive vector of integers from any source
	 * Blocking.
	 * @return data
	 */
	std::vector<int> recvIntArray();
	/**
	 * Check if there is and integer array to receive from any source
	 * Non-blocking.
	 * Use getIntArray() to receive data itself
	 * @return true in case we have data to receive
	 */
	bool hasIntArrayResult();
	/**
	 * Receive data from the source detected by hasIntArrayResult()
	 * @return dat
	 */
	std::vector<int> getIntArray();
	/**
	 * @return id of the last non blocking response
	 */
	int getLastResponseSource();
private:
	int mCommRank;
	int mCommSize;
	char mProcessorName[MPI_MAX_PROCESSOR_NAME];

	/**
	 * Sent request
	 */
	MPI_Request mRequest;
	bool mRequestSent;

	int mResponseArrSize;
	int mResponseSource;
	/**
	 * @param message print message into stdout
	 */
	void echo( std::string message );
};

#endif //MPI_MANAGER_H_
