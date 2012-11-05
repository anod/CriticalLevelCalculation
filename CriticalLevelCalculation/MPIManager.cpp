#include "MPIManager.h"


MPIManager::MPIManager(void)
	: mCommRank(MASTER_RANK), mCommSize(1), mRequestSent(false)
{
}


MPIManager::~MPIManager(void)
{
}

void MPIManager::init(int argc,char *argv[])
{
	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&mCommRank);

	MPI_Comm_size(MPI_COMM_WORLD,&mCommSize);	

	int namelen;
	MPI_Get_processor_name(mProcessorName,&namelen);

}

void MPIManager::finalize()
{
	MPI_Finalize();
}

void MPIManager::sendIntArray( int dest, std::vector<int> arr )
{
	int size = (int)arr.size();
	int* a = &arr[0];

	MPI_Send(a,size,MPI_INT,dest,0, MPI_COMM_WORLD);
}

bool MPIManager::hasIntArrayResult() {
	int flag = 0;

	if (mRequestSent) {
		MPI_Status status;
		MPI_Test(&mRequest, &flag, &status);
		return flag;
	}

	MPI_Irecv(&mIntArr, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &mRequest);
	mRequestSent = true;
	
	return flag;
}

std::vector<int> MPIManager::getIntArray()
{
	std::vector<int> result(mIntArr);
	return result;
}