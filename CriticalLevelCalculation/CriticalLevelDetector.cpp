#include "CriticalLevelDetector.h"
#include "InvolvedCellsSeeker.h"
#include <iostream>
using namespace std;

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

	for (size_t i = 0; i < cp.size() - 1; i++) {
		for(size_t j = i+1; j < cp.size(); j++) {
			printf("[%d (%d,%d),%d (%d,%d)], ",
				i, cp.at(i).coord.x, cp.at(i).coord.y,
				j, cp.at(j).coord.x, cp.at(j).coord.y
			);
			cout.flush();
		}
		printf("\n");
		cout.flush();

	}
}
