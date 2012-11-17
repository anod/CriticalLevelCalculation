#include "FlightPathBuilder.h"


FlightPathBuilder::FlightPathBuilder(const ProjectInfo &projectInfo)
	: mProjectInfo(projectInfo)
{
}


FlightPathBuilder::~FlightPathBuilder(void)
{
}

std::unordered_map<int,Cell> FlightPathBuilder::build( std::unordered_map<int,Cell> controlPoints )
{
	std::unordered_map<int,Cell> flightPath;
	return flightPath;
}
