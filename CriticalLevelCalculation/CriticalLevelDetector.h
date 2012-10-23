#ifndef CRITICAL_LEVEL_DETECTOR_H_
#define CRITICAL_LEVEL_DETECTOR_H_

#include "Include.h"
#include "ProjectSpace.h"
#include "InvolvedCellsSeeker.h"

class CriticalLevelDetector
{
public:
	CriticalLevelDetector(const ProjectSpace& projectSpace);
	~CriticalLevelDetector(void);

	CriticalLevel detect();
private:
	ProjectSpace mProjectSpace;
	bool checkCriticalSituation(std::vector<Cell> list);
	void addCriticalLevel(FlightList source, FlightList invisible, CriticalLevel& level);
	void compareCells(ControlPointsMap& cpoints,std::vector<Cell> pointsArray,InvolvedCellsSeeker& seeker, CriticalLevel& level);
};

#endif //CRITICAL_LEVEL_DETECTOR_H_
