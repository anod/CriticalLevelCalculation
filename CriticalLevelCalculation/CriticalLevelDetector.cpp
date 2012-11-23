/*
 * CriticalLevelDetector.cpp
 *
 *      Author: Alex
 */
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
	FlightsPointsMap cpoints = mProjectSpace.getFlightsPoints();
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
	FlightsPointsMap cpoints = mProjectSpace.getFlightsPoints();

	compareCells(cpoints, pointsArray, seeker, level);
	return level;
}

/**
 * Function is running in multiple threads when in parallel mode
 * @param cpoints
 * @param pointsArray
 * @param seeker
 * @param level
 */
void CriticalLevelDetector::compareCells( FlightsPointsMap& cpoints,std::vector<Cell> pointsArray,InvolvedCellsSeeker& seeker, CriticalLevel& level )
{
	Cell a,b;
	std::vector<Cell> list;

	int total = pointsArray.size();

	CLCache cache;
	cache.isInitialized = false;

	//Split cell occupied by flights cells
	//between multiple CPU cores
	//dynamic schedule for load balancing
	#pragma omp for schedule(dynamic)
	for(int i=0; i<total; i++) {
		a = pointsArray[i];
		for(int j=i+1; j<total; j++) {
			b =  pointsArray[j];

			int result = 0;
			if (cache.isInitialized && a == cache.a && b == cache.b) {
				result = cache.result;
			} else {
				// find list of the cells on the line between two cells
				list = seeker.seek(a, b);
				// check if one of the cells contain a flight
				result = checkCriticalSituation(list);

				cache.a = a;
				cache.b = b;
				cache.isInitialized = true;
				cache.result = result;
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
			//avoid memory corruption
			#pragma omp critical
			level[flight].push_back(invFlight);
		}
	}
}

bool CriticalLevelDetector::checkCriticalSituation(std::vector<Cell> list) {
	std::vector<Cell>::iterator it3;
	FlightsPointsMap cpoints = mProjectSpace.getFlightsPoints();
	FlightsPointsMap::const_iterator found;

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
