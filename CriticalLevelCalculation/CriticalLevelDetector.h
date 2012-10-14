#ifndef CRITICAL_LEVEL_DETECTOR_H_
#define CRITICAL_LEVEL_DETECTOR_H_

#include "ProjectSpace.h"

class CriticalLevelDetector
{
public:
	CriticalLevelDetector(const ProjectSpace& projectSpace);
	~CriticalLevelDetector(void);

	void detect();
private:
	ProjectSpace mProjectSpace;
};

#endif //CRITICAL_LEVEL_DETECTOR_H_
