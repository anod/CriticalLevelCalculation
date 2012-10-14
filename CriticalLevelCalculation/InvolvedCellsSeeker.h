#ifndef INVOLVED_CELLS_SEEKER_H_
#define INVOLVED_CELLS_SEEKER_H_

#include <vector>

#include "Point.h"

class InvolvedCellsSeeker
{
public:
	InvolvedCellsSeeker(Point cellSize);
	~InvolvedCellsSeeker(void);
	std::vector<Point> seek(Point a, Point b);
private:
	Point mCellSize;
	Point mHalfCellSize;
	void seekOnLine(int start, int end, int startMinor, double slope, bool horizontal, std::vector<Point>& result);
	void addResult(int major, int minor, bool horizontal, std::vector<Point>& result);
};

#endif //INVOLVED_CELLS_SEEKER_H_