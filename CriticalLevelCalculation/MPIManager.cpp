/*
 * MPIManager.cpp
 *
 *      Author: Alex
 */
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

void MPIManager::sendInt( int dest, int value) {
	MPI_Send(&value,1,MPI_INT,dest,0, MPI_COMM_WORLD);
}

int MPIManager::recvInt() {
	MPI_Status status;
	int value;
	MPI_Recv(&value, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
	return value;
}

std::vector<int> MPIManager::recvIntArray() {
	MPI_Status status;
	int arrSize;
	MPI_Recv(&arrSize, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);

	int* arr = new int[arrSize];
	//echo(MakeString() << "[recvIntArray] MPI_Recv array, size: " << arrSize << ", source: " << mResponseSource);
	MPI_Recv(arr, arrSize, MPI_INT, status.MPI_SOURCE, 0, MPI_COMM_WORLD, &status);

	std::vector<int> result;
	result.assign(arr, arr + arrSize);

	free(arr);

	return result;
}

void MPIManager::sendIntArray( int dest, std::vector<int> arr )
{
	int size = (int)arr.size();

	//Send array size
	//echo(MakeString() << "[sendIntArray] size: " << size);
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
	MPI_Status status;
	std::vector<int> result;
	result.reserve(mResponseArrSize);

	mRequestSent = false;
	if (mResponseArrSize == 0) {
		return result;
	}

	int* arr = new int[mResponseArrSize];

	//echo(MakeString() << "[getIntArray] MPI_Recv array, size: " << mResponseArrSize << ", source: " << mResponseSource);
	MPI_Recv(arr, mResponseArrSize, MPI_INT, mResponseSource, 0, MPI_COMM_WORLD, &status);
	result.assign(arr, arr + mResponseArrSize);

	free(arr);

	return result;
}

void MPIManager::echo( std::string message )
{
	std::cout << "[" << mCommRank << "] " << message << std::endl;
	std::cout.flush();
}
