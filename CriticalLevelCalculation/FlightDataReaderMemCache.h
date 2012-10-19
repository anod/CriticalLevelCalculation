#ifndef FLIGHT_DATA_READER_MEM_CACHE_H_
#define FLIGHT_DATA_READER_MEM_CACHE_H_

#include "Include.h"
#include "IFlightDataReader.h"

class FlightDataReaderMemCache : public IFlightDataReader
{
public:
	FlightDataReaderMemCache(IFlightDataReader* reader);
	~FlightDataReaderMemCache(void);

	void open();
	// Go to beginning of the file
	void rewind();
	// Reads next control point for the file
	bool readNextControlPoint();
	// Get last read flight number
	int getCurrentFlightNumber() const;
	// Get last read control point coordinates
	Point getCurrentControlPoint() const;
	// Get last read time
	int getCurrentTime() const;

private:
	static const size_t INIT_INDEX = -4;

	IFlightDataReader* mReader;
	bool mDataCached;
	std::vector<int> mMemoryCache;
	size_t mMemoryCacheIndex;
};

#endif //FLIGHT_DATA_READER_MEM_CACHE_H_
