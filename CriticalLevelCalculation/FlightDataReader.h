#ifndef FLIGHT_DATA_READER_H_
#define FLIGHT_DATA_READER_H_

#include "Include.h"

/**
 * Utility to read flights data in format provided by Project Definition:
 * Format:
 * 
 *     <A> - dimensions of the Project Space in meters.
 *     <B>
 *     <m> - the number of Cells in each dimensions.
 *     <n>
 *     <dT> - time interval for hiding checks in seconds.
 *     <Flight Code>
 *     <Number> - The number of Control Points in the Path.
 *     <x> <y> <hh:mm:ss> - Two coordinates (in meters) of each Control Point and Timestamp (hh:mm:ss format).
 *     ...
 */
class FlightDataReader
{
public:
	FlightDataReader(void);
	FlightDataReader(std::ifstream* stream, std::string fileName);
	~FlightDataReader(void);
	/**
	 * Open a file
	 */
	void open();
	/**
	 * Go to beginning of the file
	 */
	void rewind();
	/**
	 * Read header data
	 */
	void readHeader();
	/**
	 * @return list of flights
	 */
	std::vector<Flight> readFlights();
	/**
	 * @return project info
	 */
	ProjectInfo getProjectInfo() const;
private:
	static const int WRONG_TIME = -1;
	/**
	 * Header data
	 */
	Cell mSpaceSize;
	Cell mCellSize;
	int mTimeStep;
	int mTimeStart;
	int mTimeFinish;

	/**
	 * Last read flight
	 */
	Flight mCurrentFlight;

	/**
	 * File name to read from
	 */
	std::string mFileName;
	/**
	 * Input stream to read from
	 */
	std::ifstream* mInputStream;
	/**
	 * Convert time string into integer - number of seconds
	 * @return number of seconds
	 */
	int timeStringToSeconds();
	bool readNextControlPointUncached();
	bool readNextFlight();
};

#endif // FLIGHT_DATA_READER_H_
