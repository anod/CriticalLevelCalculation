/*
 * ProjectSpace.cpp
 *
 *      Author: Alex
 */

#include "ProjectSpace.h"

ProjectSpace::ProjectSpace(const Cell &spaceSize,const Cell &cellSize)
	: mSpaceSize(spaceSize), mCellSize(cellSize), mTime(0)
{
}

ProjectSpace::~ProjectSpace(void)
{
}

void ProjectSpace::addFlight( int flight, Cell point )
{
	mFlightsPoints[point].push_back(flight);
	if (mFlightsPoints[point].size() == 1) {
		mPointsArray.push_back(point);
	}
}

std::stringstream ProjectSpace::dump()
{
	FlightList::iterator it1;
	std::stringstream ss;
	ss << mTime;
	ss << " { ";
	
	std::unordered_map<Cell, std::vector<int>>::iterator it;
	bool first = true;
	for ( it=mFlightsPoints.begin() ; it != mFlightsPoints.end(); it++ ) {
		Cell p = (*it).first;
		FlightList flights((*it).second);
		if (!first) {
			ss << ", ";
		}
		ss << "[";
		for (it1 = flights.begin(); it1 != flights.end(); it1++) {
			ss << (*it1) << " ";
		}
		ss << "(" << p.x << "," << p.y << ")]";
		first = false;
	}
	ss << " } ";
	return ss;
}

/**
 * Format:
 *   { time, cellX, cellY, flightsNum, flight0..flightsNum ... }
 *
 * @return
 */
std::vector<int> ProjectSpace::serialize()
{
	FlightList::iterator it1;
	std::unordered_map<Cell, std::vector<int>>::iterator it;
	std::vector<int> arr;
	//arr.reserve(mPointsArray.size() * 4);
	arr.push_back(mTime);
	for ( it=mFlightsPoints.begin() ; it != mFlightsPoints.end(); it++ ) {
		Cell p = (*it).first;
		arr.push_back(p.x);
		arr.push_back(p.y);
		FlightList flights((*it).second);
		arr.push_back((int)flights.size());
		for (it1 = flights.begin(); it1 != flights.end(); it1++) {
			arr.push_back((*it1));
		}
	}

	return arr;
}

void ProjectSpace::deserialize( std::vector<int> data )
{
	int size = data.size();
	mTime = data[0];
	mFlightsPoints.clear();
	mPointsArray.clear();

	int i = 1;
	//mPointsArray.reserve(size);
	while( i < size ) {
		int x = data[i];
		int y = data[i+1];
		Cell p(x,y);
		int flightsNum = data[i+2];
		i+=3;
		for(int j = 0; j<flightsNum; j++) {
			addFlight(data[i+j],p);
		}
		i+=flightsNum;
	}
}
