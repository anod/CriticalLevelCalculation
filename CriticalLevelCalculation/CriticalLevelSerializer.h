/*
 * CriticalLevelSerializer.h
 *
 *      Author: Alex
 */

#ifndef CRITICAL_LEVEL_SERIALIZER_H_
#define CRITICAL_LEVEL_SERIALIZER_H_

#include "Include.h"

/**
 * Utility to serialize/deserialize CriticalLevel
 * Format: 
 *    { size, srcFlight, invFlight1 ... invFlightN, .., }  
 *
 */
class CriticalLevelSerializer {
public:
	/**
	 * @return serialized CriticalLevel vector
	 */
	static std::vector<int> serialize(CriticalLevel& level);
	/**
	 * @return deserialize data vector into CriticalLevel
	 */
	static CriticalLevel deserialize(std::vector<int> data);
	/**
	 * @return Dumped level representation
	 */
	static std::stringstream CriticalLevelSerializer::dump(CriticalLevel& level);
};

#endif // CRITICAL_LEVEL_SERIALIZER_H_
