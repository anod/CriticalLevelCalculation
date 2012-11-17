#ifndef CRITICAL_DEGREE_H_
#define CRITICAL_DEGREE_H_

#include "Include.h"

/**
 * The sum of all [Critical Levels](@ref CriticalLevel) of the object during its flight
 * (calculated for the given sets of moments: Tstart, Tstart+dT, Tstart+2dT  ... TEnd )
 */
class CriticalDegree
{
public:
	CriticalDegree(void);
	~CriticalDegree(void);
	/**
	 * Add critical level to degree
	 */
	void addCriticalLevel(CriticalLevel level);
	/**
	 * @return flight with max critical level
	 */
	int getMaxCriticalLevelFlight() const { return mMaxCriticalLevelFlight; };
	/**
	 * @return total list of other that in critical situation with the specific flight
	 */
	FlightList getFlightList(int flight) { return mTotalLevel[flight]; };

	int getTotalCount(int flight) { return mTotalCounter[flight]; };
private:
	CriticalLevel mTotalLevel;
	int mMaxCriticalLevelFlight;
	int mMaxCriticalLevel;
	std::unordered_map<int,int> mTotalCounter;
};

#endif //CRITICAL_DEGREE_H_