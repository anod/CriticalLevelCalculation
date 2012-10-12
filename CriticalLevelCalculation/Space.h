#ifndef SPACE_H_
#define SPACE_H_

#include <vector>
#include "Point.h"
#include "ControlPoint.h"
using namespace std;

class Space
{
public:
	Space(const Point &spaceSize,const Point &cellSize);
	~Space(void);
	long getTime() const { return mTime; }
	void setTime(long val) { mTime = val; }
	void addFlightPoint(int flight, int x, int y);
private:
	Point mSpaceSize;
	Point mCellSize;
	long mTime;
	vector<ControlPoint> mControlPoints;
};

#endif // SPACE_H_
