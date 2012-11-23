/*
 * CriticalDegree.cpp
 *
 *      Author: Alex
 */

#include "CriticalDegree.h"


CriticalDegree::CriticalDegree(void)
	: mMaxCriticalLevel(0), mMaxCriticalLevelFlight(0)
{
}


CriticalDegree::~CriticalDegree(void)
{
}

void CriticalDegree::addCriticalLevel( CriticalLevel level )
{
	CriticalLevel::const_iterator it;
	FlightList::const_iterator it1;

	for(it=level.begin(); it!=level.end(); it++) {
		int currentFlight = it->first;
		FlightList list = it->second;
		mTotalCounter[currentFlight]++;
		for( it1 = list.begin(); it1 != list.end(); it1++) {
			int invFlight = (*it1);
			mTotalLevel[currentFlight].push_back(invFlight);
		}
		int newSize = (int)mTotalLevel[currentFlight].size();
		if (newSize > mMaxCriticalLevel) {
			mMaxCriticalLevel = newSize;
			mMaxCriticalLevelFlight = currentFlight;
		}
	}
}
