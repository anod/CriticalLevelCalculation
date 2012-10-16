#ifndef I_FLIGHT_DATA_READER_H_
#define I_FLIGHT_DATA_READER_H_

#include "Point.h"

class IFlightDataReader
{
public:
	// Open file
	virtual void open() = 0;
	// Go to beginning of the file
	virtual void rewind() = 0;
	// Reads next control point for the file
	virtual bool readNextControlPoint() = 0;
	// Get last read flight number
	virtual int getCurrentFlightNumber() = 0;
	// Get last read control point coordinates
	virtual Point getCurrentControlPoint() = 0;
	// Get last read time
	virtual int getCurrentTime() = 0;
	virtual ~IFlightDataReader() {}
};

#endif //I_FLIGHT_DATA_READER_H_

