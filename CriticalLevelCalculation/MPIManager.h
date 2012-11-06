#ifndef MPI_MANAGER_H_
#define MPI_MANAGER_H_

#include "Include.h"
#include <mpi.h>

class MPIManager
{
public:
	static const int MASTER_RANK = 0;
	static const int MAX_ARR_SIZE = 10000;

	MPIManager(void);
	~MPIManager(void);
	void init(int argc,char *argv[]);
	void finalize();
	int getCommSize() const { return mCommSize; }
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
};

#endif //MPI_MANAGER_H_