#include "FlightDataReader.h"
#include "RuntimeException.h"


FlightDataReader::FlightDataReader(std::ifstream& stream, std::string fileName)
	: mCurrentFlightNumber(0), mNumberOfControlPoints(0), mInputStream(stream), mFileName(fileName)
{
}

FlightDataReader::~FlightDataReader(void)
{
}

void FlightDataReader::open()
{
	mInputStream.open(mFileName);
	if (!mInputStream.is_open()) {
		throw RuntimeException("Cannot open file: " + mFileName);
	}
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
			throw RuntimeException("Cannot read current flight number");
		}
		if (!getLine()) {
			throw RuntimeException("Number of control points is missing");
		}
		if (!(std::stringstream(mCurrentLine) >> mNumberOfControlPoints)) {
			throw RuntimeException("Cannot read number of control points");
		}
		if (mNumberOfControlPoints == 0) {
			return readNextControlPoint();
		}
	}
	if (!getLine()) {
		throw RuntimeException("Cannot read next control point");
	}
	int x,y = 0;
	std::string timeStr;
	std::stringstream ss(mCurrentLine);
	ss >> x >> y >> timeStr;
	mCurrentControlPoint = Point(x,y);
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
		throw RuntimeException("Cannot convert hour");
	}
	std::getline(ss,current,':');
	if (!(std::stringstream(current) >> minute)) {
		throw RuntimeException("Cannot convert minute");
	}
	std::getline(ss,current,':');
	if (!(std::stringstream(current) >> seconds)) {
		throw RuntimeException("Cannot convert seconds");
	}
	
	return seconds + (minute * 60) + (hour * 3600);
}

void FlightDataReader::rewind()
{
	mNumberOfControlPoints = 0;
	mInputStream.clear();
	mInputStream.seekg(0, std::ios::beg);
}
