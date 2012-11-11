#ifndef CRITICAL_LEVEL_DETECTOR_H_
#define CRITICAL_LEVEL_DETECTOR_H_

#include "Include.h"
#include "ProjectSpace.h"
#include "InvolvedCellsSeeker.h"

/**
 * Utility to detect [Critical Level](@ref CriticalLevel) in [Project Space](@ref ProjectSpace) 
 */
class CriticalLevelDetector
{
public:
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
	 */
	void addCriticalLevel(FlightList source, FlightList invisible, CriticalLevel& level);
	/**
	 * Detect critical level
	 */
	void compareCells(ControlPointsMap& cpoints,std::vector<Cell> pointsArray,Cell& cellSize, CriticalLevel& level);
};

#endif //CRITICAL_LEVEL_DETECTOR_H_
