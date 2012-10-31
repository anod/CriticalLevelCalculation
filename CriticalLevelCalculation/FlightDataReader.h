#ifndef FLIGHT_DATA_READER_H_
#define FLIGHT_DATA_READER_H_

#include "Include.h"
#include "IFlightDataReader.h"

class FlightDataReader : public IFlightDataReader
{
public:
	FlightDataReader(void);
	FlightDataReader(std::ifstream* stream, std::string fileName);
	~FlightDataReader(void);
	// Open file
	void open();
	// Go to beginning of the file
	void rewind();
	// Read header data
	void readHeader();
	// Reads next control point for the file
	bool readNextControlPoint();
	// Get last read flight number
	int getCurrentFlightNumber() const { return mCurrentFlightNumber; }
	// Get last read control point coordinates
	Cell getCurrentControlPoint() const { return mCurrentControlPoint; }
	// Get last read time
	int getCurrentTime() const { return mCurrentTime; }
	//
	Cell getSpaceSize() const { return mSpaceSize; }
	//
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

	std::string mFileName;
	std::ifstream* mInputStream;
	std::string mTmpStr;
	int timeStringToSeconds();
	bool readNextControlPointUncached();


};

#endif // FLIGHT_DATA_READER_H_
