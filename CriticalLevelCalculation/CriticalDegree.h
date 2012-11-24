/*
 * CriticalDegree.h
 *
 *      Author: Alex
 */

#ifndef CRITICAL_DEGREE_H_
#define CRITICAL_DEGREE_H_

#include "Include.h"


/**
 * The sum of all CriticalLevel of the object during its flight
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
	/**
	 * @param flight
	 * @return number of times flight was hidden
	 */
	int getTotalCount(int flight) { return mTotalCounter[flight]; };
private:
	/**
	 * Total Critical Level
	 */
	CriticalLevel mTotalLevel;
	/**
	 * Flight number with maximum CriticalLevel
	 */
	int mMaxCriticalLevelFlight;
	/**
	 *
	 */
	int mMaxCriticalLevel;
	/**
	 * Counter of number of hidden objects per flight
	 */
	std::unordered_map<int,int> mTotalCounter;
};

#endif //CRITICAL_DEGREE_H_
