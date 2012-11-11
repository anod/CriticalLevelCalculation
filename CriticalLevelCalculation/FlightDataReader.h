#ifndef FLIGHT_DATA_READER_H_
#define FLIGHT_DATA_READER_H_

#include "Include.h"
#include "IFlightDataReader.h"

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
class FlightDataReader : public IFlightDataReader
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
	 * Reads next control point for the file
	 * @return true if there is more point to read
	 */
	bool readNextControlPoint();
	/**
	 * @return last read flight number
	 */
	int getCurrentFlightNumber() const { return mCurrentFlightNumber; }
	/**
	 * @return last read control point coordinates
	 */
	Cell getCurrentControlPoint() const { return mCurrentControlPoint; }
	/**
	 * @return last read time 
	 */
	int getCurrentTime() const { return mCurrentTime; }
	/**
	 * @return Size of the space
	 */
	Cell getSpaceSize() const { return mSpaceSize; }
	/**
	 * @return Size of the cell
	 */
	Cell getCellSize() const { return mCellSize; }
private:
	static const int BUFFER_SIZE = 16184;
	char mBuffer[BUFFER_SIZE];

	Cell mSpaceSize;
	Cell mCellSize;
	int mNumberOfControlPoints;
	int mCurrentFlightNumber;
	Cell mCurrentControlPoint;
	int mCurrentTime;

	/**
	 * File name to read from
	 */
	std::string mFileName;
	/**
	 * Input stream to read from
	 */
	std::ifstream* mInputStream;
	std::string mTmpStr;
	/**
	 * Convert time string into integer - number of seconds
	 * @return number of seconds
	 */
	int timeStringToSeconds();
	bool readNextControlPointUncached();
};

#endif // FLIGHT_DATA_READER_H_
