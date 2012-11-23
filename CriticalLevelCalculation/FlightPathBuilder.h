/*
 * FlightPathBuilder.h
 *
 *      Author: Alex
 */

#ifndef FLIGHT_PATH_BUILDER_H_
#define FLIGHT_PATH_BUILDER_H_

#include "Include.h"

/**
 * Builds flight path for the one flight based on control points of the flight
 */
class FlightPathBuilder
{
public:
	/**
	 * @param projectInfo
	 */
	FlightPathBuilder(const ProjectInfo &projectInfo);
	~FlightPathBuilder(void);
	/**
	 * Flight will be appended with the flight path
	 * @param flight
	 */
	void build( Flight &flight );
private:
	ProjectInfo mProjectInfo;
	/**
	 * Calculates path between two control points
	 * @param cp1 - first control point
	 * @param cp2 - second control point
	 * @param flightPath - flight path to be updated with points
	 */
	void calcFlightLeg(ControlPoint& cp1, ControlPoint& cp2, std::vector<Cell>& flightPath);

};

#endif //FLIGHT_PATH_BUILDER_H_
