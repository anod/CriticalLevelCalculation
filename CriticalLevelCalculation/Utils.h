/*
 * Utils.h
 *
 *      Author: Alex
 */

#ifndef UTILS_H_
#define UTILS_H_

#include "Include.h"

class Utils
{
public:
	Utils(void);
	~Utils(void);
	/**
	 * Convert coordinates into cell
	 */
	static Cell Utils::convertToCell(int x, int y, Cell cellSize);
	/**
	 * Convert coordinate into cell
	 */
	static int Utils::coordToCell(int coord, int size);
	/**
	 * Convert coordinate into cell
	 */
	static double Utils::coordToCellAccurate(int coord, int size);
};

#endif //UTILS_H_
