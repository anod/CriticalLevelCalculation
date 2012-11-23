/*
 * Utils.cpp
 *
 *      Author: Alex
 */

#include "Utils.h"

Utils::Utils(void)
{
}

Utils::~Utils(void)
{
}

Cell Utils::convertToCell(int x, int y, Cell cellSize) {
	return Cell(coordToCell(x,cellSize.x),coordToCell(y,cellSize.y));
}

int Utils::coordToCell(int coord, int size) {
	return (int)ceil(coordToCellAccurate(coord, size));
}

double Utils::coordToCellAccurate(int coord, int size) {
	return ((double)coord / (double)size);
}
