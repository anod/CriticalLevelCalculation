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
	//echo(MakeString() << "Execute task " << projectSpace.getTime());
	//echo(projectSpace.dump().str());
	CriticalLevel level;
	CriticalLevelDetector detector(projectSpace);
	//Profiler::getInstance().start("Detect critical level - parallel");
	level = detector.detectParallel();
	//Profiler::getInstance().finish();
	return level;
}