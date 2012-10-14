#include "InvolvedCellsSeeker.h"

InvolvedCellsSeeker::InvolvedCellsSeeker( Point cellSize )
	: mCellSize(cellSize)
{
	mHalfCellSize = Point( (int)(cellSize.x / 2), (int)(cellSize.y / 2) );
}


InvolvedCellsSeeker::~InvolvedCellsSeeker(void)
{
}

std::vector<Point> InvolvedCellsSeeker::seek( Point a, Point b )
{
	int x1,y1,x2,y2 = 0;
	std::vector<Point> result;

	if (a.x == b.x && a.y == b.y) {
		return result;
	}

	x1 = ((a.x * mCellSize.x) - mHalfCellSize.x);
	y1 = ((a.y * mCellSize.y) - mHalfCellSize.y);
	x2 = ((b.x * mCellSize.x) - mHalfCellSize.x);
	x2 = ((b.y * mCellSize.y) - mHalfCellSize.y);

	int diffX = x2 - x1;
	int diffY = y2 - y1;

	bool horizontal = (abs(diffX) >= abs(diffY));

	if (horizontal) {
		// y = mx + b
		double m = (double)diffY / (double)diffX;
		//float b = y1 - (m * x1);
		seekOnLine(x1,x2,y1, m, true, result);
	} else {
		// y = mx + b
		double m = (double)diffX / (double)diffY;
		//float b = y1 - (m * x1);
		seekOnLine(y1,y2,x1, m, false, result);
	}


	return result;
}

void InvolvedCellsSeeker::seekOnLine(int start, int end, int startMinor, double slope, bool horizontal, std::vector<Point>& result) {
	int advance = end > start ? 1 : -1;
	double curMinor = startMinor + mHalfCellSize.x + (mHalfCellSize.x * advance * slope);
	for (int curMajor = start + advance; curMajor != end; curMajor += advance)
	{
		addResult(curMajor, (int)floor(curMinor), horizontal, result);

		double newMinor = curMinor + (advance * slope);            
		if (floor(newMinor) != floor(curMinor)) {
			addResult(curMajor, (int)floor(newMinor), horizontal, result);
		}
		curMinor = newMinor;
	}
}

void InvolvedCellsSeeker::addResult(int major, int minor, bool horizontal, std::vector<Point>& result)
{
	if (horizontal) // X is major
		result.push_back(Point(major, minor));
	else // Y is major
		result.push_back(Point(minor, major));
}