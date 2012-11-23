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
	int size = cpoints.size();

	for (int j = 0; j < size - 1; j++) {
		ControlPoint cp1 = cpoints[j];
		ControlPoint cp2 = cpoints[j+1];

		calcFlightLeg(cp1, cp2, flightPath);
	}

	flight.setTimeStep(mProjectInfo.timeStep);
	flight.setFlightPath(flightPath);
}

void FlightPathBuilder::calcFlightLeg(ControlPoint& cp1, ControlPoint& cp2, std::vector<Cell>& flightPath) {
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