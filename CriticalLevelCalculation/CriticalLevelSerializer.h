//
//  CriticalLevelSerializer.h
//  CriticalLevelCalculation
//
//  Created by Alex Gavrishev on 11/5/12.
//
//

#ifndef CRITICAL_LEVEL_SERIALIZER_H_
#define CRITICAL_LEVEL_SERIALIZER_H_

#include "Include.h"

class CriticalLevelSerializer {
public:
	static std::vector<int> serialize(CriticalLevel& level);
	static CriticalLevel deserialize(std::vector<int> data);
};

#endif // CRITICAL_LEVEL_SERIALIZER_H_