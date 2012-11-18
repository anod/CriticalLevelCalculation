#include "MPIManager.h"


MPIManager::MPIManager(void)
	: mCommRank(MASTER_RANK), mCommSize(1), mRequestSent(false), mResponseSource(0), mResponseArrSize(0)
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

std::vector<int> MPIManager::recvIntArray() {
	MPI_Status status;
	int arrSize;
	MPI_Recv(&arrSize, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

	int arr[MAX_ARR_SIZE];
	MPI_Recv(&arr, arrSize, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD, &status);

	std::vector<int> result(arrSize);
	result.assign(arr, arr + arrSize);
	
	return result;
}

void MPIManager::sendIntArray( int dest, std::vector<int> arr )
{
	int size = (int)arr.size();

	//Send array size
	MPI_Send(&size,1,MPI_INT,dest,0, MPI_COMM_WORLD);
	if (size > 0) {
		int* a = &arr[0];
		//Send array data
		MPI_Send(a,size,MPI_INT,dest,0, MPI_COMM_WORLD);
	}
}

bool MPIManager::hasIntArrayResult() {
	MPI_Status status;
	int flag = 0;

	if (mRequestSent) {
		MPI_Test(&mRequest, &flag, &status);
		mResponseSource = status.MPI_SOURCE;
		return (flag == 1);
	}

	MPI_Irecv(&mResponseArrSize, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &mRequest);
	MPI_Test(&mRequest, &flag, &status);
	mRequestSent = true;
	mResponseSource = status.MPI_SOURCE;
	return (flag == 1);
}

int MPIManager::getLastResponseSource()
{
	return mResponseSource;
}

std::vector<int> MPIManager::getIntArray()
{
	int arr[MAX_ARR_SIZE];
	MPI_Status status;
	std::vector<int> result(mResponseArrSize);
	result.reserve(mResponseArrSize);

	mRequestSent = false;
	if (mResponseArrSize == 0) {
		return result;
	}

	MPI_Recv(&arr, mResponseArrSize, MPI_INT, mResponseSource, 0, MPI_COMM_WORLD, &status);
	result.assign(arr, arr + mResponseArrSize);
	return result;
}