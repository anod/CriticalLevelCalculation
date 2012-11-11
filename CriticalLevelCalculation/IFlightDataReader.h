#ifndef I_FLIGHT_DATA_READER_H_
#define I_FLIGHT_DATA_READER_H_
	
#include "Include.h"

/**
 * Interface for utility to read flights data
 */
class IFlightDataReader
{
public:
	/**
	 * Open a file
	 */
	virtual void open() = 0;
	/**
	 * Go to beginning of the file
	 */
	virtual void rewind() = 0;
	/**
	 * Read header data
	 */
	virtual void readHeader() = 0;
	/**
	 * Reads next control point for the file
	 * @return true if there is more point to read
	 */
	virtual bool readNextControlPoint() = 0;
	/**
	 * @return last read flight number
	 */
	virtual int getCurrentFlightNumber() const = 0;
	/**
	 * @return last read control point coordinates
	 */
	virtual Cell getCurrentControlPoint() const = 0;
	/**
	 * @return last read time 
	 */
	virtual int getCurrentTime() const = 0;
	/**
	 * @return Size of the space
	 */
	virtual Cell getSpaceSize() const = 0;
	/**
	 * @return Size of the cell
	 */
	virtual Cell getCellSize() const = 0;

	virtual ~IFlightDataReader() {}
};
		
#endif //I_FLIGHT_DATA_READER_H_
