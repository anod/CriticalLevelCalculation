#ifndef PROJECT_SPACE_H_
#define PROJECT_SPACE_H_

#include <vector>
#include <sstream>

#include "Point.h"
#include "ControlPoint.h"

class ProjectSpace
{
public:
	ProjectSpace(const Point &spaceSize,const Point &cellSize);
	~ProjectSpace(void);
	Point getSpaceSize() const { return mSpaceSize; };
	Point getCellSize() const { return mCellSize; };
	long getTime() const { return mTime; }
	void setTime(long val) { mTime = val; }
	void addControlPoint(int flight, Point point);
	std::vector<ControlPoint> const getControlPoints() { return mControlPoints; };

	std::stringstream dump();
private:
	Point mSpaceSize;
	Point mCellSize;
	long mTime;
	std::vector<ControlPoint> mControlPoints;
};

#endif // PROJECT_SPACE_H_
