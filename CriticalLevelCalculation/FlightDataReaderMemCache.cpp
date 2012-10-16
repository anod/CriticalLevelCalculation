#include "FlightDataReaderMemCache.h"


FlightDataReaderMemCache::FlightDataReaderMemCache(const FlightDataReader& reader)
	: mReader(reader)
{

}


FlightDataReaderMemCache::~FlightDataReaderMemCache(void)
{
}

bool FlightDataReaderMemCache::readNextControlPoint()
{

	if (mDataCached) {
		if (mMemoryCacheIndex < mMemoryCache.size()) {
			mMemoryCacheIndex+=4;
			return true;
		} else {
			return false;
		}
	}
	bool result = FlightDataReader::readNextControlPoint();
	if (result != false) {
		mMemoryCache.push_back(FlightDataReader.getCurrentFlightNumber());
		Point p = FlightDataReader.getCurrentControlPoint();
		mMemoryCache.push_back(p.x);
		mMemoryCache.push_back(p.y);
		mMemoryCache.push_back(FlightDataReader.getCurrentTime());
	} else {
		mDataCached = true;
	}
	return result;
}

void FlightDataReaderMemCache::rewind()
{
	if (mDataCached) {
		mMemoryCacheIndex = 0;
	} else {
		FlightDataReader::rewind();
	}
}
