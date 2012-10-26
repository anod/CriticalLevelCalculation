#ifndef PROJECT_SPACE_H_
#define PROJECT_SPACE_H_

#include "Include.h"

class ProjectSpace
{
public:
	ProjectSpace(const Cell &spaceSize,const Cell &cellSize);
	~ProjectSpace(void);
	Cell getSpaceSize() const { return mSpaceSize; };
	Cell getCellSize() const { return mCellSize; };
	int getTime() const { return mTime; }
	void setTime(long val) { mTime = val; }
	void addControlPoint(int flight, Cell point);
	ControlPointsMap const getControlPoints() { return mControlPoints; };
	std::vector<Cell> const getPointsArray() { return mPointsArray; };

	std::stringstream dump();
	void sortControlPoints();
	std::vector<int> serialize();
	void deserialize(int size, int data[]);
private:
	Cell mSpaceSize;
	Cell mCellSize;
	int mTime;
	ControlPointsMap mControlPoints;
	std::vector<Cell> mPointsArray;
};

#endif // PROJECT_SPACE_H_
