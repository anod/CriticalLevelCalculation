//
//  CriticalLevelSerializer.cpp
//  CriticalLevelCalculation
//
//  Created by Alex Gavrishev on 11/5/12.
//
//

#include "CriticalLevelSerializer.h"

std::vector<int> CriticalLevelSerializer::serialize(CriticalLevel& level) {
	CriticalLevel::const_iterator it;
	FlightList::const_iterator it1;
	std::vector<int> serialized;
	
	for(it=level.begin(); it!=level.end(); it++) {
		int currentFlight = it->first;
		FlightList list = it->second;
		int size = 1 + (int)list.size();
		serialized.push_back(size);
		serialized.push_back(currentFlight);
		for( it1 = list.begin(); it1 != list.end(); it1++) {
			int invFlight = (*it1);
			serialized.push_back(invFlight);
		}
	}
	return serialized;
}

CriticalLevel CriticalLevelSerializer::deserialize(std::vector<int> data) {
	CriticalLevel level;
	std::vector<int>::const_iterator it;
	int size = 0;
	int currentFlight = 0;
	// Format: [size,currentFlight,invFlights...]
	for(size_t i=0; i<data.size(); i++) {
		if (size == 0) {
			currentFlight = 0;
			size = data[i];
		} else {
			if (currentFlight == 0) {
				currentFlight = data[i];
			} else {
				level[currentFlight].push_back(data[i]);
			}
			size--;
		}
		i++;
	}
	return level;
}
