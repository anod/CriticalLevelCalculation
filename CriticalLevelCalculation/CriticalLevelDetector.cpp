#include "CriticalLevelDetector.h"
#include "InvolvedCellsSeeker.h"


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

	std::vector<ControlPoint> const cp = mProjectSpace.getControlPoints();

	std::vector<ControlPoint>::iterator it1;

}
