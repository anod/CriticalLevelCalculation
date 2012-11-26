/*
 * main.cpp
 *
 *      Author: Alex
 *
 * The Project Goal
 * Write an effective parallel program to find an object with the maximum Critical Degree
 * and display id of all other object that did not see it during the Flight.
 *
 * Critical Degree
 * The sum of all Critical Levels of the object during its Flight
 * (calculated for the given sets of moments – Tstart, Tstar+dT, Tstar+2dT, …, TEned. ).
 *
 * Critical Level (CL)of the object at the specific moment
 * The number of objects that do not see this object at the given moment.
 *
 * Requirements and Constraints
 * 1. Use a number of computers to produce an effective parallel program.
 *    Use at least three computers.
 * 2. All computers have to work as optimal as possible (Load Balancing).
 * 3. The data file may be very big (according to the number of objects) and initially is accessible to one computer only.
 * 4. The program has to be based on MPI and OpenMP to implement Effective and Scalable application.
 *    There must not more than one MPI process on each computer.
 *    MPI process is responsible mainly for communications between computers.
 *    Heavy computations are performed with OpenMP.
 *
 */

#include "Include.h"

#include "MPIManager.h"
#include "MPIWorkerFactory.h"

/**
 * Entry point
 * @param argc
 * @param argv
 * @return
 */
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

	return(0);
}
