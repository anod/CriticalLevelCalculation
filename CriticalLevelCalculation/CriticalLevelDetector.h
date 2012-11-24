/*
 * CriticalLevelDetector.h
 *
 *      Author: Alex
 */

#ifndef CRITICAL_LEVEL_DETECTOR_H_
#define CRITICAL_LEVEL_DETECTOR_H_

#include "Include.h"
#include "ProjectSpace.h"
#include "InvolvedCellsSeeker.h"


/**
 * Utility to detect CriticalLevel in [Project Space](@ref ProjectSpace)
 */
class CriticalLevelDetector
{
public:
	/**
	 * @param projectSpace
	 */
	CriticalLevelDetector(const ProjectSpace& projectSpace);
	~CriticalLevelDetector(void);
	/**
	 * @return detected critical level using multi cores (OpenMP) 
	 */
	CriticalLevel detectParallel();
	/**
	 * @return detected critical level using usual serial mode
	 */
	CriticalLevel detectSerial();
private:
	/**
	 * Working project space
	 */
	ProjectSpace mProjectSpace;
	/**
	 * @param list - list of point in path
	 */
	bool checkCriticalSituation(std::vector<Cell> list);
	/**
	 * Adds for all flights in source list of invisible flights
	 * @param source - list of flights in critical situation
	 * @param invisible - list of flights that not see the source
	 * @param level - level to be updated
	 */
	void addCriticalLevel(FlightList source, FlightList invisible, CriticalLevel& level);
	/**
	 * Detect critical level
	 * The function running in parallel on multiple CPU cores
	 */
	void compareCells(FlightsPointsMap& cpoints,std::vector<Cell> pointsArray,InvolvedCellsSeeker& seeker, CriticalLevel& level);
};

/**
 * Helper struct to hold last calculation result
 */
struct CLCache {
	/**
	 * flag indicates if cache was initialized for the first time
	 */
	bool isInitialized;
	/**
	 * first cell
	 */
	Cell a;
	/**
	 * second cell
	 */
	Cell b;
	/**
	 * comparison result
	 */
	int result;
};

#endif //CRITICAL_LEVEL_DETECTOR_H_
