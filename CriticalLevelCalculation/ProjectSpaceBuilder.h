#ifndef PROJECT_SPACE_BUILDER_H_
#define PROJECT_SPACE_BUILDER_H_
#include "ProjectSpace.h"
#include "FlightDataReader.h"
#include <unordered_map>

class ProjectSpaceBuilder
{
public:
	ProjectSpaceBuilder(const Point &spaceSize,const Point &cellSize, const FlightDataReader& reader);
	~ProjectSpaceBuilder(void);

	ProjectSpace build();
	bool nextTime();
private:
	static const int WRONG_TIME_INDEX = -1;

	Point mSpaceSize;
	Point mCellSize;

	std::size_t mCurrentTimeIndex;
	std::unordered_map<int,bool> mTimesCache;
	FlightDataReader mFlightDataReader;

};

#endif // PROJECT_SPACE_BUILDER_H_
