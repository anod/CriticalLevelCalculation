/*
 * Flight.h
 *
 *      Author: Alex
 */

#ifndef FLIGHT_H_
#define FLIGHT_H_

#include "Include.h"

/**
 * Describes flight in the project
 */
class Flight
{
public:
	Flight(void);
	/**
	 * @param flightNum flight number
	 */
	Flight(int flightNum);
	~Flight(void);
	/**
	 * @return flight number
	 */
	int getFlightNum() const { return mFlightNum; };
	/**
	 * @return start time of the flight (by first control point)
	 */
	int getTimeStart() const { return mTimeStart; };
	/**
	 * @return finish time of the flight (by the last control point)
	 */
	int getTimeFinish() const { return mTimeFinish; };
	/**
	 * @param timeStep - seconds - size of time step in the flight path
	 */
	void setTimeStep(int timeStep) { mTimeStep = timeStep; };
	/**
	 * @return flight control points
	 */
	std::vector<ControlPoint> getControlPoints() const { return mControlPoints; };
	/**
	 * Add a new control point to the flight
	 * @param time
	 * @param point
	 */
	void addControlPoint(int time, Cell point);
	/**
	 * @param flightPath set flight path
	 */
	void setFlightPath(std::vector<Cell> flightPath) { mFlightPath = flightPath; };
	/**
	 * Get position of the flight in flight path at specific time
	 * @param time
	 * @return Coordinates in meters
	 */
	Cell getPositionAtTime(int time);
private:
	/**
	 * initial time value
	 */
	static const int TIME_INCORRECT = -1;

	int mFlightNum;
	int mTimeStart;
	int mTimeFinish;
	int mTimeStep;
	std::vector<ControlPoint> mControlPoints;
	std::vector<Cell> mFlightPath;
};

#endif // FLIGHT_H_
