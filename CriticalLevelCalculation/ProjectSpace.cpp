#include "ProjectSpace.h"

ProjectSpace::ProjectSpace(const Point &spaceSize,const Point &cellSize)
	: mSpaceSize(spaceSize), mCellSize(cellSize), mTime(0)
{
}

ProjectSpace::~ProjectSpace(void)
{
}

void ProjectSpace::addFlightPoint( int flight, Point point )
{
	ControlPoint p = { /*.x=*/ point.x, /*.y=*/ point.y, /*.flight=*/ flight };
	mControlPoints.push_back(p);
}

std::stringstream ProjectSpace::dump()
{
	std::stringstream ss;
	ss << "Time: " << mTime << "\n";
	ss << "Control Points: ";
	
	std::vector<ControlPoint>::iterator it;
	bool first = true;
	for ( it=mControlPoints.begin() ; it < mControlPoints.end(); it++ ) {
		ControlPoint p = *it;
		if (!first) {
			ss << ", ";
		}
		ss << "[" << p.flight << " (" << p.x << "," << p.y << ")]";
		first = false;
	}
	ss << "\n";
	return ss;
}
