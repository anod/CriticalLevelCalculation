/*
 * Flight.cpp
 *
 *      Author: Alex
 */

#include "Flight.h"


Flight::Flight(int flightNum)
 : mFlightNum(flightNum), mTimeStart(TIME_INCORRECT), mTimeFinish(TIME_INCORRECT), mTimeStep(1)
{
}

Flight::Flight(void)
 : mFlightNum(0), mTimeStart(TIME_INCORRECT), mTimeFinish(TIME_INCORRECT), mTimeStep(1)
{
}


Flight::~Flight(void)
{
}

void Flight::addControlPoint( int time, Cell point )
{
	ControlPoint cp = { /*.time=*/time, /*.coord=*/point};
	mControlPoints.push_back(cp);

	//update start and finish time
	if (mTimeStart == TIME_INCORRECT) {
		mTimeStart = mTimeFinish = time;
	} else if (time < mTimeStart) {
		mTimeStart = time;
	} else if (time > mTimeFinish) {
		mTimeFinish = time;
	}
}

Cell Flight::getPositionAtTime( int time )
{
	//calculate index of the cell in flight path vector
	int idx = (int)((double)(time - mTimeStart)/(double)mTimeStep);
	Cell p = mFlightPath.at(idx);
	return p;
}
