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
		int xDiff = cp2.coord.x - cp1.coord.x;
		int yDiff = cp2.coord.y - cp1.coord.y;

		double speedX = (double)((double)xDiff / (double)timeDiff);
		double speedY = (double)((double)yDiff / (double)timeDiff);

		for (int i = 0; i < timeDiff; i+=mProjectInfo.timeStep) {
			int x = cp1.coord.x + (int)(speedX * i);
			int y = cp1.coord.y + (int)(speedY * i);
			Cell cell = Utils::convertToCell(x, y, mProjectInfo.cellSize);
			flightPath.push_back(cell);
		}
		Cell last = Utils::convertToCell(cp2.coord.x, cp2.coord.y, mProjectInfo.cellSize);
		flightPath.push_back(last);
	}

	flight.setTimeStep(mProjectInfo.timeStep);
	flight.setFlightPath(flightPath);
}
