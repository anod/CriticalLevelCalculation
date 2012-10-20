#include "ProjectSpace.h"

ProjectSpace::ProjectSpace(const Point &spaceSize,const Point &cellSize)
	: mSpaceSize(spaceSize), mCellSize(cellSize), mTime(0)
{
}

ProjectSpace::~ProjectSpace(void)
{
}

void ProjectSpace::addControlPoint( int flight, Point point )
{
	ControlPoint p = { /*.coord=*/ point, /*.flight=*/ flight };
	mControlPoints.push_back(p);
}

void ProjectSpace::sortControlPoints()
{
	std::sort(mControlPoints.begin(),mControlPoints.end());
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
		ss << "[" << p.flight << " (" << p.coord.x << "," << p.coord.y << ")]";
		first = false;
	}
	ss << "\n";
	return ss;
}


