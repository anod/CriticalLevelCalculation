#ifndef INVOLVED_CELLS_SEEKER_H_
#define INVOLVED_CELLS_SEEKER_H_

#include "Include.h"
/**
 * Utility to search cells between two other cells on direct line
 * Use [Bresenham's line algorithm](http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
 */
class InvolvedCellsSeeker
{
public:
	/**
	 * @param cellSize - size of one cell
	 */
	InvolvedCellsSeeker(const Cell spaceSize,const Cell cellSize);
	~InvolvedCellsSeeker(void);
	/**
	 * @return vector of cells between a and b
	 */
	std::vector<Cell> seek(Cell a, Cell b);
private:
	Cell mSpaceSize;
	Cell mCellSize;
	Cell mHalfCellSize;
	/**
	 * add cell to result
	 * @use mLastCell to remove duplicates
	 */
	void addResult(int major, int minor, std::vector<Cell>& result, Cell& lastCell);
	/**
	 * Check cells on line between x1,y1 and x2,y2
	 */
	void line(int x1,int y1,int x2,int y2, std::vector<Cell>& result);
	/**
	 * Checks if found corner of the cell
	 */
	bool isCorner(double cellX, double cellY, int exactCellX, int exactCellY);
};

#endif //INVOLVED_CELLS_SEEKER_H_