#ifndef FLIGHT_PATH_BUILDER_H_
#define FLIGHT_PATH_BUILDER_H_

#include "Include.h"

class FlightPathBuilder
{
public:
	FlightPathBuilder(const ProjectInfo &projectInfo);
	~FlightPathBuilder(void);
	void build( Flight &flight );
private:
	ProjectInfo mProjectInfo;
	void calcFlightLeg(ControlPoint& cp1, ControlPoint& cp2, std::vector<Cell>& flightPath);

};

#endif