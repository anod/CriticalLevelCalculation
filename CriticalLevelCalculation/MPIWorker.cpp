#include "MPIWorker.h"

MPIWorker::MPIWorker(MPIManager* mpi)
	: mMpi(mpi)
{

}

void MPIWorker::echo( std::string message )
{
	std::cout << "[" << mMpi->getCommRank() << "] " << message << std::endl;
	std::cout.flush();
}
