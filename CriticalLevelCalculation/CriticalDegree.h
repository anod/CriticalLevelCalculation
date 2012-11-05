#ifndef CRITICAL_DEGREE_H_
#define CRITICAL_DEGREE_H_

#include "Include.h"

class CriticalDegree
{
public:
	CriticalDegree(void);
	~CriticalDegree(void);
	void addCriticalLevel(CriticalLevel level);
	int getMaxCriticalLevelFlight() const { return mMaxCriticalLevelFlight; };
	FlightList getFlightList(int flight) { return mTotalLevel[flight]; };
private:
	CriticalLevel mTotalLevel;
	int mMaxCriticalLevelFlight;
	int mMaxCriticalLevel;
};

#endif //CRITICAL_DEGREE_H_