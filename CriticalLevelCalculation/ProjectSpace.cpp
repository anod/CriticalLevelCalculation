#include "ProjectSpace.h"

ProjectSpace::ProjectSpace(const Cell &spaceSize,const Cell &cellSize)
	: mSpaceSize(spaceSize), mCellSize(cellSize), mTime(0)
{
}

ProjectSpace::~ProjectSpace(void)
{
}

void ProjectSpace::addControlPoint( int flight, Cell point )
{
	mControlPoints[point].push_back(flight);
	if (mControlPoints[point].size() == 1) {
		mPointsArray.push_back(point);
	}
}

std::stringstream ProjectSpace::dump()
{
	FlightList::iterator it1;
	std::stringstream ss;
	ss << "Time: " << mTime << "\n";
	ss << "Control Points: ";
	
	std::unordered_map<Cell, std::vector<int>>::iterator it;
	bool first = true;
	for ( it=mControlPoints.begin() ; it != mControlPoints.end(); it++ ) {
		Cell p = (*it).first;
		FlightList flights((*it).second);
		if (!first) {
			ss << ", ";
		}
		ss << "[";
		for (it1 = flights.begin(); it1 != flights.end(); it1++) {
			ss << (*it1) << " ";
		}
		ss << "(" << p.x << "," << p.y << ")]";
		first = false;
	}
	ss << "\n";
	return ss;
}


