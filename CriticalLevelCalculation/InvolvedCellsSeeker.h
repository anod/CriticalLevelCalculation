#ifndef INVOLVED_CELLS_SEEKER_H_
#define INVOLVED_CELLS_SEEKER_H_

#include "Include.h"

class InvolvedCellsSeeker
{
public:
	InvolvedCellsSeeker(Point cellSize);
	~InvolvedCellsSeeker(void);
	std::vector<Point> seek(Point a, Point b);
private:
	Point mCellSize;
	Point mHalfCellSize;
	Point mLastCell;
	Point mStopCell;
	void addResult(int major, int minor, std::vector<Point>& result);
	int coordToCell(int coord, int size);
	void line(int x1,int y1,int x2,int y2, std::vector<Point>& result);
};

#endif //INVOLVED_CELLS_SEEKER_H_