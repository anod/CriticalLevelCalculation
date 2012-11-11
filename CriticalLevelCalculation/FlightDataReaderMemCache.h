#ifndef FLIGHT_DATA_READER_MEM_CACHE_H_
#define FLIGHT_DATA_READER_MEM_CACHE_H_

#include "Include.h"
#include "IFlightDataReader.h"

/**
 * Proxy over [FlightDataReader](@ref FlightDataReader) that loads data into memory for faster processing
 */
class FlightDataReaderMemCache : public IFlightDataReader
{
public:
	/**
	 * @param reader - wrapee
	 */
	FlightDataReaderMemCache(IFlightDataReader* reader);
	~FlightDataReaderMemCache(void);
	/**
	 * Open file
	 */
	void open();
	/**
	* Go to beginning of the file
	*/
	void rewind();
	/**
	 * Reads next control point for the file
	 * @return true if there is more point to read
	 */
	bool readNextControlPoint();
	/**
	 * @return last read flight number
	 */
	int getCurrentFlightNumber() const;
	/**
	 * @return last read control point coordinates
	 */
	Cell getCurrentControlPoint() const;
	/**
	 * @return last read time 
	 */
	int getCurrentTime() const;
	/**
	 * Reads file into memory
	 */
	void preloadCache();
	/**
	 * Read header data
	 */
	void readHeader();
	/**
	 * @return Size of the space
	 */
	Cell getSpaceSize() const;
	/**
	 * @return Size of the cell
	 */
	Cell getCellSize() const;

private:
	static const size_t INIT_INDEX = -4;
	/**
	 * wrapee
	 */
	IFlightDataReader* mReader;
	/**
	 * The file has been cached
	 */
	bool mDataCached;
	/**
	 * cache storage
	 */
	std::vector<int> mMemoryCache;
	/**
	 * Pointer to current position
	 */
	size_t mMemoryCacheIndex;

};

#endif //FLIGHT_DATA_READER_MEM_CACHE_H_
