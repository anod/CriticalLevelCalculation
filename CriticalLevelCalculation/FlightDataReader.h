#ifndef FLIGHT_DATA_READER_H_
#define FLIGHT_DATA_READER_H_

#include <string>
#include <fstream>
#include <sstream>
#include "Point.h"

class FlightDataReader
{
public:
	FlightDataReader(std::string filename);
	~FlightDataReader(void);
	void open();
	bool readNextControlPoint();
	int getCurrentFlightNumber() const { return mCurrentFlightNumber; }
	Point getCurrentContorlPoint() const { return mCurrentControlPoint; }
	long getCurrentTime() const { return mCurrentTime; }
private:
	std::string mFileName;
	std::ifstream mInputStream;
	std::string mCurrentLine;
	int mNumberOfControlPoints;
	int mCurrentFlightNumber;
	Point mCurrentControlPoint;
	long mCurrentTime;

	//
	std::istream& getLine();
	int timeStringToSeconds(std::string timeStr);
};

#endif // FLIGHT_DATA_READER_H_
