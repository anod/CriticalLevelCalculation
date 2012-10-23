#include "MPIManager.h"


MPIManager::MPIManager(void)
{
}


MPIManager::~MPIManager(void)
{
}

void MPIManager::init(int argc,char *argv[])
{
	int  namelen, numtasks, myrank;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD,&myrank);

	MPI_Comm_size(MPI_COMM_WORLD,&numtasks);	

	MPI_Get_processor_name(processor_name,&namelen);

}
