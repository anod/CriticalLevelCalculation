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
	long getTime() const { return mTime; }
	void setTime(long val) { mTime = val; }
	void addFlightPoint(int flight, Point point);

	std::stringstream dump();
private:
	Point mSpaceSize;
	Point mCellSize;
	long mTime;
	std::vector<ControlPoint> mControlPoints;
};

#endif // PROJECT_SPACE_H_
