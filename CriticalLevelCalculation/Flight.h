#ifndef FLIGHT_H_
#define FLIGHT_H_

#include "Include.h"

class Flight
{
public:
	Flight(void);
	Flight(int flightNum);
	~Flight(void);
	void addControlPoint(int time, Cell point);
private:
	int mFlightNum;
	std::vector<int,Cell> mControlPoints;

};

#endif // FLIGHT_H_