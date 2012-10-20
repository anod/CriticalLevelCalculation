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
	if (!mDataCached) {
		preloadCache();
	}
	if (mMemoryCacheIndex < mMemoryCache.size()) {
		return true;
	}
	return false;
}

void FlightDataReaderMemCache::preloadCache() {
	open();
	while(mReader->readNextControlPoint()) {
		mMemoryCache.push_back(mReader->getCurrentFlightNumber());
		Cell p = mReader->getCurrentControlPoint();
		mMemoryCache.push_back(p.x);
		mMemoryCache.push_back(p.y);
		mMemoryCache.push_back(mReader->getCurrentTime());
	}
	mDataCached = true;
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
	if (!mDataCached) {
		mReader->open();
	}
}

int FlightDataReaderMemCache::getCurrentTime() const
{
	return mMemoryCache.at(mMemoryCacheIndex+3);
}

Cell FlightDataReaderMemCache::getCurrentControlPoint() const
{
	return Cell(mMemoryCache.at(mMemoryCacheIndex+1),mMemoryCache.at(mMemoryCacheIndex+2));
}

int FlightDataReaderMemCache::getCurrentFlightNumber() const
{
	 return mMemoryCache.at(mMemoryCacheIndex);
}
