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
	Flight(int flightNum);
	~Flight(void);
	int getFlightNum() const { return mFlightNum; };
	int getTimeStart() const { return mTimeStart; };
	int getTimeFinish() const { return mTimeFinish; };
	void setTimeStep(int timeStep) { mTimeStep = timeStep; };
	void addControlPoint(int time, Cell point);
	std::vector<ControlPoint> getControlPoints() const { return mControlPoints; };
	void setFlightPath(std::vector<Cell> flightPath) { mFlightPath = flightPath; };
	Cell getPositionAtTime(int time);
private:
	static const int TIME_INCORRECT = -1;

	int mFlightNum;
	int mTimeStart;
	int mTimeFinish;
	int mTimeStep;
	std::vector<ControlPoint> mControlPoints;
	std::unordered_map<int,bool> mControlPointsTimes;
	std::vector<Cell> mFlightPath;
};

#endif // FLIGHT_H_