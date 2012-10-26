#include "MPIWorker.h"

MPIWorker::MPIWorker(MPIManager* mpi, const Cell &spaceSize,const Cell &cellSize )
	: mMpi(mpi), mSpaceSize(spaceSize) , mCellSize(cellSize)
{

}
