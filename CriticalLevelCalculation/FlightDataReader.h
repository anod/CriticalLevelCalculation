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
	// Reads next control point for the file
	bool readNextControlPoint();
	// Get last read flight number
	int getCurrentFlightNumber() const { return mCurrentFlightNumber; }
	// Get last read control point coordinates
	Point getCurrentControlPoint() const { return mCurrentControlPoint; }
	// Get last read time
	int getCurrentTime() const { return mCurrentTime; }
private:
	int mNumberOfControlPoints;
	int mCurrentFlightNumber;
	Point mCurrentControlPoint;
	int mCurrentTime;

	std::string mFileName;
	std::ifstream* mInputStream;
	std::string mTmpStr;
	int timeStringToSeconds();
	bool readNextControlPointUncached();


};

#endif // FLIGHT_DATA_READER_H_
