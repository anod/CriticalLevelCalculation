#ifndef FLIGHT_PATH_BUILDER_H_
#define FLIGHT_PATH_BUILDER_H_

#include "Include.h"

class FlightPathBuilder
{
public:
	FlightPathBuilder(const ProjectInfo &projectInfo);
	~FlightPathBuilder(void);
	std::unordered_map<int,Cell> build(std::unordered_map<int,Cell> controlPoints);
private:
	ProjectInfo mProjectInfo;
};

#endif