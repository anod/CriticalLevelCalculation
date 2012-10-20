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

	void detect();
private:
	ProjectSpace mProjectSpace;
	std::vector<ControlPoint> checkCriticalSituation(Point check);
};

#endif //CRITICAL_LEVEL_DETECTOR_H_
