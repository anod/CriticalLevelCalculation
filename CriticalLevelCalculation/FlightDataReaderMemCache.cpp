#include "FlightDataReaderMemCache.h"

FlightDataReaderMemCache::FlightDataReaderMemCache(IFlightDataReader* reader)
	: mReader(reader), mDataCached(false), mMemoryCacheIndex(INIT_INDEX)
{

}


FlightDataReaderMemCache::~FlightDataReaderMemCache( void )
{

}


bool FlightDataReaderMemCache::readNextControlPoint()
{
	mMemoryCacheIndex+=4;
	if (mDataCached) {
		if (mMemoryCacheIndex < mMemoryCache.size()) {
			return true;
		} else {
			return false;
		}
	}
	bool result = mReader->readNextControlPoint();
	if (result != false) {
		mMemoryCache.push_back(mReader->getCurrentFlightNumber());
		Point p = mReader->getCurrentControlPoint();
		mMemoryCache.push_back(p.x);
		mMemoryCache.push_back(p.y);
		mMemoryCache.push_back(mReader->getCurrentTime());
	} else {
		mDataCached = true;
	}
	return result;
}

void FlightDataReaderMemCache::rewind()
{
	if (!mDataCached) {
		mReader->rewind();
	}
	mMemoryCacheIndex = INIT_INDEX;
}


void FlightDataReaderMemCache::open()
{
	mReader->open();
}

int FlightDataReaderMemCache::getCurrentTime() const
{
	return mMemoryCache.at(mMemoryCacheIndex+3);
}

Point FlightDataReaderMemCache::getCurrentControlPoint() const
{
	return Point(mMemoryCache.at(mMemoryCacheIndex+1),mMemoryCache.at(mMemoryCacheIndex+2));
}

int FlightDataReaderMemCache::getCurrentFlightNumber() const
{
	 return mMemoryCache.at(mMemoryCacheIndex);
}
