#include "Include.h"

#include "MPIManager.h"
#include "MPIWorkerFactory.h"

int main(int argc, char *argv[])
{
	MPIManager mpimanager;
	mpimanager.init(argc,argv);
	MPIWorker* worker = MPIWorkerFactory::create(&mpimanager);
   try {
		worker->run();
	} catch(std::exception& caught){
		std::cout<<" [Exception] "<<caught.what()<<std::endl;
	}

	mpimanager.finalize();

	//system("pause");
	return(0);
}