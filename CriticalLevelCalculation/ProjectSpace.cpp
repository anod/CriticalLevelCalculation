#include "ProjectSpace.h"

ProjectSpace::ProjectSpace(const Point &spaceSize,const Point &cellSize)
	: mSpaceSize(spaceSize), mCellSize(cellSize), mTime(0)
{
	mControlPoints.resize(mSpaceSize.x * mSpaceSize.y);
}

ProjectSpace::~ProjectSpace(void)
{
}

void ProjectSpace::addFlightPoint( int flight, int x, int y )
{
	ControlPoint p = { /*.x=*/ x, /*.y=*/ y, /*.flight=*/ flight };
	mControlPoints.push_back(p);
}
