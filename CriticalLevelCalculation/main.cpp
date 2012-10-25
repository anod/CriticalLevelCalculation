#include "Include.h"

#include "TestRunner.h"
#include "MPIManager.h"

#define SPACE_SIZE_A 500
#define SPACE_SIZE_B 500
#define SPACE_SIZE_m 10
#define SPACE_SIZE_n 10

void tests() {
	TestRunner tests;
	tests.run();
}

int main(int argc, char *argv[])
{
	MPIManager mpimanager;
	mpimanager.init(argc,argv);
	MPIWorker* worker = mpimanager.createWorker(Cell(SPACE_SIZE_A,SPACE_SIZE_B),Cell(SPACE_SIZE_m,SPACE_SIZE_n));
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