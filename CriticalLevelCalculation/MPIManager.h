#ifndef MPI_MANAGER_H_
#define MPI_MANAGER_H_

#include "Include.h"
#include <mpi.h>

class MPIManager
{
public:
	MPIManager(void);
	~MPIManager(void);
	void init(int argc,char *argv[]);
};

#endif //MPI_MANAGER_H_