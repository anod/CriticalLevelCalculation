#include "CriticalLevelDetector.h"

CriticalLevelDetector::CriticalLevelDetector(const ProjectSpace& projectSpace)
	: mProjectSpace(projectSpace)
{
}


CriticalLevelDetector::~CriticalLevelDetector(void)
{
}

void CriticalLevelDetector::detect()
{
	InvolvedCellsSeeker seeker(mProjectSpace.getCellSize());

	ControlPointsMap::iterator it1,it2;
	ControlPointsMap cpoints = mProjectSpace.getControlPoints();

	for( it1 = cpoints.begin(); it1 != cpoints.end(); it1++) {
		for( it2 = it2; it2 != cpoints.end(); it2++) {
			Cell a = (*it1).first;
			Cell b = (*it2).first;
			std::cout << a.dump() << " " << b.dump() << std::endl;
		}
	}
		/*
	for (size_t i = 0; i < cp.size() - 1; i++) {
		for(size_t j = i+1; j < cp.size(); j++) {
			std::vector<Point> result = seeker.seek(cp.at(i).coord, cp.at(j).coord);


		}
	}*/
}

std::vector<ControlPoint> CriticalLevelDetector::checkCriticalSituation(Cell check) {
	std::vector<ControlPoint> result;

	ControlPointsMap cp = mProjectSpace.getControlPoints();
	ControlPointsMap::const_iterator it;

	for( it = cp.begin(); it != cp.end(); it++) {
//		(*it).first
	}
	return result;
}
