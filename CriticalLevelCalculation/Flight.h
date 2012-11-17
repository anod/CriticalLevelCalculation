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
	int getTimeStart() const { return mTimeStart; }
	int getTimeFinish() const { return mTimeFinish; }
	void addControlPoint(int time, Cell point);
	std::unordered_map<int,Cell> getControlPoints() const { return mControlPoints; };
	std::unordered_map<int,Cell> getFlightPath() const { return mFlightPath; };
	void setFlightPath(std::unordered_map<int,Cell> flightPath) { mFlightPath = flightPath; };
	Cell getPositionAtTime(int time);
private:
	static const int TIME_INCORRECT = -1;

	int mFlightNum;
	int mTimeStart;
	int mTimeFinish;
	std::unordered_map<int,Cell> mControlPoints;
	std::unordered_map<int,Cell> mFlightPath;
};

#endif // FLIGHT_H_