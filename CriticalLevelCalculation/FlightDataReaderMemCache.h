#ifndef FLIGHT_DATA_READER_MEM_CACHE_H_
#define FLIGHT_DATA_READER_MEM_CACHE_H_

#include "FlightDataReader.h"

class FlightDataReaderMemCache : public FlightDataReader
{
public:
	FlightDataReaderMemCache(const FlightDataReader& reader);
	~FlightDataReaderMemCache(void);

	// Go to beginning of the file
	void rewind();
	// Reads next control point for the file
	bool readNextControlPoint();
	// Get last read flight number
	int getCurrentFlightNumber() const { return mMemoryCache.at(mMemoryCacheIndex); }
	// Get last read control point coordinates
	Point getCurrentControlPoint() const { return Point(mMemoryCache.at(mMemoryCacheIndex+1),mMemoryCache.at(mMemoryCacheIndex+2)); }
	// Get last read time
	int getCurrentTime() const { return mMemoryCache.at(mMemoryCacheIndex+3); }

private:
	FlightDataReader mReader;
	bool mDataCached;
	std::vector<int> mMemoryCache;
	size_t mMemoryCacheIndex;
};

#endif //FLIGHT_DATA_READER_MEM_CACHE_H_
