#ifndef PROJECT_SPACE_BUILDER_H_
#define PROJECT_SPACE_BUILDER_H_

#include "Include.h"
#include "ProjectSpace.h"
#include "IFlightDataReader.h"

class ProjectSpaceBuilder
{
public:
	ProjectSpaceBuilder(const Cell &spaceSize,const Cell &cellSize, IFlightDataReader* reader);
	~ProjectSpaceBuilder(void);

	ProjectSpace build();
	bool nextTime();
private:
	static const int WRONG_TIME_INDEX = -1;

	Cell mSpaceSize;
	Cell mCellSize;

	std::size_t mCurrentTimeIndex;
	std::unordered_map<int,bool> mTimesMap;
	std::vector<int> mTimesCache;
	IFlightDataReader* mFlightDataReader;
};

#endif // PROJECT_SPACE_BUILDER_H_
