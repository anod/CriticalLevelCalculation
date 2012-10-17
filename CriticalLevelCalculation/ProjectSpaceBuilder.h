#ifndef PROJECT_SPACE_BUILDER_H_
#define PROJECT_SPACE_BUILDER_H_

#include "ProjectSpace.h"
#include "IFlightDataReader.h"
#include <unordered_map>
#include <vector>

class ProjectSpaceBuilder
{
public:
	ProjectSpaceBuilder(const Point &spaceSize,const Point &cellSize, IFlightDataReader* reader);
	~ProjectSpaceBuilder(void);

	ProjectSpace build();
	bool nextTime();
private:
	static const int WRONG_TIME_INDEX = -1;

	Point mSpaceSize;
	Point mCellSize;

	std::size_t mCurrentTimeIndex;
	std::unordered_map<int,bool> mTimesMap;
	std::vector<int> mTimesCache;
	IFlightDataReader* mFlightDataReader;
};

#endif // PROJECT_SPACE_BUILDER_H_
