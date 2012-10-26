#include "MPIManager.h"


MPIManager::MPIManager(void)
	: mCommRank(MASTER_RANK), mCommSize(1)
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
	int size = arr.size();
	int* a = &arr[0];

	MPI_Send(a,size,MPI_INT,dest,0, MPI_COMM_WORLD);
}

std::vector<int> MPIManager::recvIntArray()
{
	int size;
	int flag;
	MPI_Request req;
	MPI_Irecv(&size, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &req);

	MPI_Status status;
	MPI_Test(&req, &flag, &status);

}