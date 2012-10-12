#include "Space.h"

Space::Space(const Point &spaceSize,const Point &cellSize)
	: mSpaceSize(spaceSize), mCellSize(cellSize), mTime(0)
{
	mControlPoints.resize(mSpaceSize.x * mSpaceSize.y);
}

Space::~Space(void)
{
}

void Space::addFlightPoint( int flight, int x, int y )
{
	ControlPoint p = { /*.x=*/ x, /*.y=*/ y, /*.flight=*/ flight };
	mControlPoints.push_back(p);
}
