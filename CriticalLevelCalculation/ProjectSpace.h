/*
 * ProjectSpace.h
 *
 *      Author: Alex
 */

#ifndef PROJECT_SPACE_H_
#define PROJECT_SPACE_H_

#include "Include.h"

/**
 * Class represent Project Space
 */
class ProjectSpace
{
public:
	/**
	 * @param spaceSize
	 * @param cellSize
	 */
	ProjectSpace(const Cell &spaceSize,const Cell &cellSize);
	~ProjectSpace(void);
	/**
	 * @return space size in cells
	 */
	Cell getSpaceSize() const { return mSpaceSize; };
	/**
	 * @return cell size in meters
	 */
	Cell getCellSize() const { return mCellSize; };
	/**
	 * @return time in seconds
	 */
	int getTime() const { return mTime; }
	/**
	 * @param time in seconds
	 */
	void setTime(int time) { mTime = time; }
	/**
	 * Add flight to the ProjectSpace
	 * @param flight
	 * @param point
	 */
	void addFlight(int flight, Cell point);
	/**
	 * @return map of flights to their points in the project space
	 */
	FlightsPointsMap const getFlightsPoints() { return mFlightsPoints; };
	/**
	 * @return list of occupied cells in the project space
	 */
	std::vector<Cell> const getPointsArray() { return mPointsArray; };
	/**
	 * @return dump ProjectSpace data
	 */
	std::stringstream dump();
	/**
	 * Serialize ProjectInfo into flat array
	 * Format:
	 *   { time, cellX, cellY, flightsNum, flight0..flightsNum ... }
	 * @return serialized data
	 */
	std::vector<int> serialize();
	/**
	 * Deserialize data from the flat array
	 * @param data
	 */
	void deserialize(std::vector<int> data);
private:
	Cell mSpaceSize;
	Cell mCellSize;
	int mTime;
	FlightsPointsMap mFlightsPoints;
	std::vector<Cell> mPointsArray;
};

#endif // PROJECT_SPACE_H_
