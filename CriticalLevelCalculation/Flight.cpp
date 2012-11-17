#include "Flight.h"


Flight::Flight(int flightNum)
 : mFlightNum(flightNum), mTimeStart(TIME_INCORRECT), mTimeFinish(TIME_INCORRECT)
{
}

Flight::Flight(void)
{
}


Flight::~Flight(void)
{
}

void Flight::addControlPoint( int time, Cell point )
{
	mControlPoints[time] = point;

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
	return mFlightPath.at(time);
}
