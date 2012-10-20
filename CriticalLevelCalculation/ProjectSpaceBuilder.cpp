#include "ProjectSpaceBuilder.h"


ProjectSpaceBuilder::ProjectSpaceBuilder(const Cell &spaceSize,const Cell &cellSize, IFlightDataReader* reader)
	: mSpaceSize(spaceSize), mCellSize(cellSize), mCurrentTimeIndex(WRONG_TIME_INDEX), mFlightDataReader(reader)
{

}

ProjectSpaceBuilder::~ProjectSpaceBuilder(void)
{
}

bool ProjectSpaceBuilder::nextTime() {
	if (mCurrentTimeIndex == WRONG_TIME_INDEX) {
		return true;
	}

	mCurrentTimeIndex++;
	if (mCurrentTimeIndex >= mTimesMap.size()) {
		return false;
	}
	return true;
}

ProjectSpace ProjectSpaceBuilder::build()
{
	bool buildTimeCache;
	int currentTime;

	ProjectSpace space(mSpaceSize, mCellSize);

	if (mCurrentTimeIndex == WRONG_TIME_INDEX) {
		mFlightDataReader->open();
		buildTimeCache = true;
		currentTime = -1;
	} else {
		mFlightDataReader->rewind();
		buildTimeCache = false;
		std::vector<int>::iterator it = mTimesCache.begin();
		std::advance(it, mCurrentTimeIndex); // now it is advanced by mCurrentTimeIndex
		currentTime = *it;
	}

	while (mFlightDataReader->readNextControlPoint()) {
		int time = mFlightDataReader->getCurrentTime();
		if (buildTimeCache && !mTimesMap[time]) {
			mTimesMap[time] = true;
			mTimesCache.push_back(time);
		}
		if (currentTime == -1) {
			currentTime = time;
			mCurrentTimeIndex = 0;
		}
		if (time == currentTime) {
			Cell p = mFlightDataReader->getCurrentControlPoint();
			int flight = mFlightDataReader->getCurrentFlightNumber();
			space.addControlPoint(flight, p);
		}
	}

	space.setTime(currentTime);
	return space;
}
