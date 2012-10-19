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

	if (a == b) {
		return result;
	}

	x1 = ((a.x * mCellSize.x) - mHalfCellSize.x);
	y1 = ((a.y * mCellSize.y) - mHalfCellSize.y);
	x2 = ((b.x * mCellSize.x) - mHalfCellSize.x);
	y2 = ((b.y * mCellSize.y) - mHalfCellSize.y);

	line(x1,y1,x2,y2,result);
	return result;
}

int InvolvedCellsSeeker::coordToCell(int coord, int size) {
	return (int)ceil(((double)coord / (double)size));
}

void InvolvedCellsSeeker::line(int x1,int y1,int x2,int y2, std::vector<Point>& result) {
	int newCellX,newCellY = 0;

	bool steep = abs(y2 - y1) > abs(x2 - x1);
	if (steep) {
		std::swap(x1, y1);
		std::swap(x2, y2);
	}
	if (x1 > x2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	if (steep) {
		mLastCell = Point(coordToCell(y1,mCellSize.x),  coordToCell(x1,mCellSize.y));
		mStopCell = Point(coordToCell(y2,mCellSize.x),  coordToCell(x2,mCellSize.y)); 
	} else {
		mLastCell = Point(coordToCell(x1,mCellSize.x),  coordToCell(y1,mCellSize.y));
		mStopCell = Point(coordToCell(x2,mCellSize.x),  coordToCell(y2,mCellSize.y)); 
	}

	int deltax = x2 - x1;
	int deltay = abs(y2 - y1);
	int error = deltax / 2;
	int y = y1;
	int ystep = (y1 < y2) ? 1 : -1;

	for (int x = x1; x <= x2; x++) {
		if (steep) {
			newCellX = coordToCell(y,mCellSize.x);
			newCellY = coordToCell(x,mCellSize.y);
		} else {
			newCellX = coordToCell(x,mCellSize.x);
			newCellY = coordToCell(y,mCellSize.y);
		}
		if (mStopCell.x == newCellX && mStopCell.y == newCellY) {
			return;
		}
		addResult(newCellX,newCellY,result);

		error = error - deltay;
		if (error < 0) {
			y = y + ystep;
			error = error + deltax;
		}
	}
}

void InvolvedCellsSeeker::addResult(int cellX, int cellY, std::vector<Point>& result) {
	if (mLastCell.x == -1 || cellX != mLastCell.x || cellY != mLastCell.y) {
		Point p = Point(cellX, cellY);
		mLastCell = p;
		result.push_back(p);
	}
}