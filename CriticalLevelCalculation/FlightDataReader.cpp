#include "FlightDataReader.h"

FlightDataReader::FlightDataReader(std::string fileName)
	: mCurrentFlightNumber(0), mNumberOfControlPoints(0)
{
	mFileName = fileName;
}


FlightDataReader::~FlightDataReader(void)
{
	mInputStream.open(mFileName);
}

std::istream& FlightDataReader::getLine()
{
	return getline(mInputStream, mCurrentLine);
}

bool FlightDataReader::readNextControlPoint()
{
	if (mNumberOfControlPoints == 0) { //New flight
		if (!getLine()) {
			return false;
		}
		mCurrentFlightNumber = 0;
		if (!(std::stringstream(mCurrentLine) >> mCurrentFlightNumber)) {
			throw "Cannot read current flight number";
		}
		if (!getLine()) {
			throw "Number of control points is missing";
		}
		if (!(std::stringstream(mCurrentLine) >> mNumberOfControlPoints)) {
			throw "Cannot read number of control points";
		}
		if (mNumberOfControlPoints == 0) {
			return readNextControlPoint();
		}
	}
	if (!getLine()) {
		throw "Cannot read next control point";
	}
	int x,y = 0;
	std::string timeStr;
	std::stringstream ss(mCurrentLine);
	ss >> x >> y >> timeStr;
	mCurrentTime = timeStringToSeconds(timeStr);
	mNumberOfControlPoints--;
	return true;
}

int FlightDataReader::timeStringToSeconds(std::string timeStr)
{
	int hour,minute,seconds = 0;
	std::stringstream ss(timeStr);
	std::string current;
	// extract data
	std::getline(ss,current,':');
	if (!(std::stringstream(current) >> hour)) {
		throw "Cannot convert hour";
	}
	std::getline(ss,current,':');
	if (!(std::stringstream(current) >> minute)) {
		throw "Cannot convert minute";
	}
	std::getline(ss,current,':');
	if (!(std::stringstream(current) >> seconds)) {
		throw "Cannot convert seconds";
	}
	
	return seconds + (minute * 60) + (hour * 3600);
}