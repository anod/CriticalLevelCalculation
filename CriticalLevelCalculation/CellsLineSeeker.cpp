/*
 * CellsLineSeeker.cpp
 *
 *      Author: Alex
 */

#include "CellsLineSeeker.h"

CellsLineSeeker::CellsLineSeeker(const Cell spaceSize,const Cell cellSize)
	: mCellSize(cellSize), mSpaceSize(spaceSize)
{
	mHalfCellSize = Cell( (int)(cellSize.x / 2), (int)(cellSize.y / 2) );
}


CellsLineSeeker::~CellsLineSeeker(void)
{
}

std::vector<Cell> CellsLineSeeker::seek( Cell a, Cell b )
{
	int x1,y1,x2,y2 = 0;
	std::vector<Cell> result;

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

void CellsLineSeeker::line(int x1,int y1,int x2,int y2, std::vector<Cell>& result) {
	int newCellX,newCellY, curX, curY;
	double newCellAccX,newCellAccY;
	Cell lastCell, stopCell;

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
		lastCell = Utils::convertToCell(y1, x1, mCellSize);
		stopCell = Utils::convertToCell(y2, x2, mCellSize);
	} else {
		lastCell = Utils::convertToCell(x1, y1, mCellSize);
		stopCell = Utils::convertToCell(x2, y2, mCellSize); 
	}

	int deltax = x2 - x1;
	int deltay = abs(y2 - y1);
	int error = deltax / 2;
	int y = y1;
	int ystep = (y1 < y2) ? 1 : -1;
	int xstep = (steep) ?  mCellSize.y :  mCellSize.x;
	ystep = (steep) ?  ystep * mCellSize.x : ystep * mCellSize.y;

	for (int x = x1; x <= x2; x=x+xstep) {
		if (steep) {
			curX = y;
			curY = x;
		} else {
			curX = x;
			curY = y;
		}

		newCellX = Utils::coordToCell(curX,mCellSize.x);
		newCellY = Utils::coordToCell(curY,mCellSize.y);

		if (stopCell.x == newCellX && stopCell.y == newCellY) {
			return;
		}
		addResult(newCellX,newCellY,result, lastCell);

		//detect corners
		newCellAccX = Utils::coordToCellAccurate(curX,mCellSize.x);
		newCellAccY = Utils::coordToCellAccurate(curY,mCellSize.y);
		if (isCorner(newCellAccX, newCellAccX, newCellX, newCellY)) {
			if (newCellX - 1 > 0) {
				addResult(newCellX - 1,newCellY,result, lastCell);
			}
			if ((unsigned int)(newCellX + 1) <= mSpaceSize.x) {
				addResult(newCellX + 1,newCellY,result, lastCell);
			}
			if (newCellY - 1 > 0) {
				addResult(newCellX,newCellY - 1,result, lastCell);
			}
			if ((unsigned int)(newCellY + 1) <= mSpaceSize.y) {
				addResult(newCellX,newCellY - 1,result, lastCell);
			}
		}


		error = error - deltay;
		if (error < 0) {
			y = y + ystep;
			error = error + deltax;
		}
	}
}

bool CellsLineSeeker::isCorner(double cellX, double cellY, int exactCellX, int exactCellY) {
	if (abs(exactCellX - cellX) < 0.00001 && abs(exactCellY - cellY) < 0.00001) {
		return true;
	}
	return false;
}

void CellsLineSeeker::addResult(int cellX, int cellY, std::vector<Cell>& result, Cell& lastCell) {
	if (lastCell.x == -1 || cellX != lastCell.x || cellY != lastCell.y) {
		Cell p = Cell(cellX, cellY);
		lastCell = p;
		result.push_back(p);
	}
}
