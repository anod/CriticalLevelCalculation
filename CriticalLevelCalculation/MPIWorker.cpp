/*
 * MPIManager.cpp
 *
 *      Author: Alex
 */

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

CriticalLevel MPIWorker::executeTask( ProjectSpace& projectSpace )
{
	CriticalLevel level;
	CriticalLevelDetector detector(projectSpace);
	level = detector.detectParallel();
	// level = detector.detctSerial();
	return level;
}
