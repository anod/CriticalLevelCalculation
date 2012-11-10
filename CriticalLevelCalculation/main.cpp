#include "Include.h"

#include "TestRunner.h"
#include "MPIManager.h"
#include "MPIWorkerFactory.h"

void tests() {
	TestRunner tests;
	tests.run();
}

int main(int argc, char *argv[])
{
	MPIManager mpimanager;
	mpimanager.init(argc,argv);
	MPIWorker* worker = MPIWorkerFactory::create(&mpimanager);
   try {
		worker->run();
		//tests();
	} catch(std::exception& caught){
		std::cout<<" [Exception] "<<caught.what()<<std::endl;
	}

	mpimanager.finalize();

	system("pause");
	return(0);
}