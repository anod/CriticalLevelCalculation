#include "CriticalLevelDetector.h"

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

	std::vector<Point>::iterator it;
	std::vector<ControlPoint> const cp = mProjectSpace.getControlPoints();

	for (size_t i = 0; i < cp.size() - 1; i++) {
		for(size_t j = i+1; j < cp.size(); j++) {
			std::vector<Point> result = seeker.seek(cp.at(i).coord, cp.at(j).coord);
			std::cout << "[" << cp.at(i).coord.x << "," << cp.at(i).coord.y << "] --> ";
			for( it = result.begin(); it != result.end(); it++) {
				std::cout << " [" << (*it).x << "," << (*it).y << "] ";
			}
			std::cout << " --> [" << cp.at(j).coord.x << "," << cp.at(j).coord.y << "]\n";
			std::cout.flush();
			return;
		}
	}
}
