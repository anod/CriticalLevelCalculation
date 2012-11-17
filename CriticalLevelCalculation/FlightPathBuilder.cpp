#include "FlightPathBuilder.h"


FlightPathBuilder::FlightPathBuilder(const ProjectInfo &projectInfo)
	: mProjectInfo(projectInfo)
{
}


FlightPathBuilder::~FlightPathBuilder(void)
{
}

void FlightPathBuilder::build( Flight &flight )
{
	std::vector<Cell> flightPath;
	std::vector<ControlPoint>::const_iterator it;

	std::vector<ControlPoint> cpoints = flight.getControlPoints();
	for (it = cpoints.begin(); it != cpoints.end() - 1; it++) {
		ControlPoint cp1 = *it;
		ControlPoint cp2 = *(it+1);

		int timeDiff = cp2.time - cp1.time;
		double speedX = (double)((double)(cp2.coord.x - cp1.coord.x) / (double)timeDiff);
		double speedY = (double)((double)(cp2.coord.y - cp1.coord.y) / (double)timeDiff);

		for (int currentTime = cp1.time; currentTime < cp2.time; currentTime+=mProjectInfo.timeStep) {
			int timeDiff = currentTime - cp1.time;
			int x = cp1.coord.x + (int)(speedX * timeDiff);
			int y = cp1.coord.y + (int)(speedY * timeDiff);
			Cell cell = Utils::convertToCell(x,y, mProjectInfo.cellSize);
			flightPath.push_back(cell);
		}
	}

	flight.setTimeStep(mProjectInfo.timeStep);
	flight.setFlightPath(flightPath);
}
