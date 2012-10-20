#ifndef INVOLVED_CELLS_SEEKER_H_
#define INVOLVED_CELLS_SEEKER_H_

#include "Include.h"

class InvolvedCellsSeeker
{
public:
	InvolvedCellsSeeker(Cell cellSize);
	~InvolvedCellsSeeker(void);
	std::vector<Cell> seek(Cell a, Cell b);
private:
	Cell mCellSize;
	Cell mHalfCellSize;
	Cell mLastCell;
	Cell mStopCell;
	void addResult(int major, int minor, std::vector<Cell>& result);
	int coordToCell(int coord, int size);
	void line(int x1,int y1,int x2,int y2, std::vector<Cell>& result);
};

#endif //INVOLVED_CELLS_SEEKER_H_