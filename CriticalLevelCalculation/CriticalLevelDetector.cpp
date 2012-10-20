#include "CriticalLevelDetector.h"

CriticalLevelDetector::CriticalLevelDetector(const ProjectSpace& projectSpace)
	: mProjectSpace(projectSpace)
{
}


CriticalLevelDetector::~CriticalLevelDetector(void)
{
}

CriticalLevel CriticalLevelDetector::detect()
{
	InvolvedCellsSeeker seeker(mProjectSpace.getCellSize());

	ControlPointsMap::const_iterator it1,it2;
	ControlPointsMap cpoints = mProjectSpace.getControlPoints();

	CriticalLevel level;

	for( it1 = cpoints.begin(); it1 != cpoints.end(); it1++) {
		for(it2 = it1, it2++; it2 != cpoints.end(); it2++) {
			Cell a = (*it1).first;
			Cell b = (*it2).first;
			std::vector<Cell> list = seeker.seek(a, b);
			int result = checkCriticalSituation(list);
			if (result) {
				addCriticalLevel((*it1).second, (*it2).second, level);
				addCriticalLevel((*it2).second, (*it1).second, level);
			}
		}
	}
	return level;
}

void CriticalLevelDetector::addCriticalLevel(FlightList source, FlightList invisible, CriticalLevel& level) {
	FlightList::const_iterator it1,it2;
	for( it1 = source.begin(); it1 != source.end(); it1++) {
		int flight = (*it1);
		for( it2 = invisible.begin(); it2 != invisible.end(); it2++) {
			int invFlight = (*it2);
			level[flight].push_back(invFlight);
		}
	}
}

bool CriticalLevelDetector::checkCriticalSituation(std::vector<Cell> list) {
	std::vector<Cell>::iterator it3;
	ControlPointsMap cpoints = mProjectSpace.getControlPoints();
	ControlPointsMap::const_iterator found;

	FlightList::const_iterator fit;

	for( it3 = list.begin(); it3 != list.end(); it3++) {
		Cell key = (*it3);
		found = cpoints.find(key);
		if (found != cpoints.end()) {
			return true; //
		}
	}

	return false;
}
