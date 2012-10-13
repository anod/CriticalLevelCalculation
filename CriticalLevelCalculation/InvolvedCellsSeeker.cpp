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

	x1 = ((a.x * mCellSize.x) - mHalfCellSize.x);
	y1 = ((a.y * mCellSize.y) - mHalfCellSize.y);
	x2 = ((b.x * mCellSize.x) - mHalfCellSize.x);
	x2 = ((b.y * mCellSize.y) - mHalfCellSize.y);

	// y = mx + b
	float m = abs(y2 - y1) / abs(x2 - x1);
	float b = y1 - (m * x1);

	std::vector<Point> result;


	return result;
}
