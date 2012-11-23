#include "CriticalLevelDetector.h"

CriticalLevelDetector::CriticalLevelDetector(const ProjectSpace& projectSpace)
	: mProjectSpace(projectSpace)
{
}


CriticalLevelDetector::~CriticalLevelDetector(void)
{
}

CriticalLevel CriticalLevelDetector::detectParallel()
{
	CriticalLevel level;
	InvolvedCellsSeeker seeker(mProjectSpace.getSpaceSize(), mProjectSpace.getCellSize());
	std::vector<Cell> pointsArray = mProjectSpace.getPointsArray();
	ControlPointsMap cpoints = mProjectSpace.getControlPoints();
#pragma omp parallel
{
	compareCells(cpoints, pointsArray, seeker, level);
}
	return level;
}

CriticalLevel CriticalLevelDetector::detectSerial()
{
	CriticalLevel level;
	InvolvedCellsSeeker seeker(mProjectSpace.getSpaceSize(), mProjectSpace.getCellSize());
	std::vector<Cell> pointsArray = mProjectSpace.getPointsArray();
	ControlPointsMap cpoints = mProjectSpace.getControlPoints();

	compareCells(cpoints, pointsArray, seeker, level);
	return level;
}


void CriticalLevelDetector::compareCells( ControlPointsMap& cpoints,std::vector<Cell> pointsArray,InvolvedCellsSeeker& seeker, CriticalLevel& level )
{
	Cell a,b;
	std::vector<Cell> list;

	int total = pointsArray.size();

	bool cacheReady = false;
	Cell cacheA;
	Cell cacheB;
	int cacheResult=0;
	#pragma omp for
	for(int i=0; i<total; i++) {
		a = pointsArray[i];
		for(int j=i+1; j<total; j++) {
			b =  pointsArray[j];

			int result = 0;
			if (cacheReady && a == cacheA && b == cacheB) {
				result = cacheResult;
			} else {
				list = seeker.seek(a, b);
				result = checkCriticalSituation(list);

				cacheA = a;
				cacheB = b;
				cacheReady = true;
				cacheResult = result;
			}

			if (result) {
				addCriticalLevel(cpoints[a], cpoints[b], level);
				addCriticalLevel(cpoints[b], cpoints[a], level);
			}
		}
	}

}


void CriticalLevelDetector::addCriticalLevel(FlightList source, FlightList invisible, CriticalLevel& level) {
	FlightList::const_iterator it1,it2;
	for( it1 = source.begin(); it1 != source.end(); it1++) {
		int flight = (*it1);
		for( it2 = invisible.begin(); it2 != invisible.end(); it2++) {
			int invFlight = (*it2);
			#pragma omp critical
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
