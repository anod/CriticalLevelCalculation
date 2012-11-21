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
	void sendIntArray(int dest, std::vector<int> arr);
	std::vector<int> recvIntArray();
	bool hasIntArrayResult();
	std::vector<int> getIntArray();
	int getLastResponseSource();
private:
	int mCommRank;
	int mCommSize;
	bool mRequestSent;
	MPI_Request mRequest;
	int mResponseArrSize;
	int mResponseSource;
	char mProcessorName[MPI_MAX_PROCESSOR_NAME];
	void echo( std::string message );
};

#endif //MPI_MANAGER_H_