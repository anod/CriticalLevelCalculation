#ifndef PROJECT_INFO_H
#define PROJECT_INFO_H

#include "Include.h"
/**
 * Describe general information of the project
 */
class ProjectInfo
{
public:
	ProjectInfo(void);
	~ProjectInfo(void);
	/**
	 * Size of the space in cells
	 */
	Cell spaceSize;
	/**
	 * Size of the cell in meters
	 */
	Cell cellSize;
	/**
	 * time step in seconds
	 */
	int timeStep;
	/**
	 * minimum start time of all the flights
	 */
	int timeStart;
	/**
	 * maximum start time of all the flights
	 */
	int timeFinish;
	/**
	 * Serialize object data into array
	 */
	std::vector<int> serialize();
	/**
	 * Deserialize object data from array
	 */
	void deserialize(std::vector<int> data);
};

#endif //PROJECT_INFO_H

