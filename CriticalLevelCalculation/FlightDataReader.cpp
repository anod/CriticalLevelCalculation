#include "FlightDataReader.h"
#include "RuntimeException.h"


FlightDataReader::FlightDataReader(std::ifstream* stream, std::string fileName)
	: mInputStream(stream), mFileName(fileName)
{
}

FlightDataReader::~FlightDataReader(void)
{
}

void FlightDataReader::open()
{
	mInputStream->open(mFileName);
	if (!mInputStream->is_open()) {
		throw RuntimeException("Cannot open file: " + mFileName);
	}

}

int FlightDataReader::timeStringToSeconds()
{
	int hour,minute,seconds = 0;
	std::string current;
	// extract data
	std::getline(*mInputStream,current,':');
	if (!(std::stringstream(current) >> hour)) {
		throw RuntimeException("Cannot convert hour: " + current);
	}
	std::getline(*mInputStream,current,':');
	if (!(std::stringstream(current) >> minute)) {
		throw RuntimeException("Cannot convert minute: "+minute);
	}
	if (!(*mInputStream >> seconds)) {
		throw RuntimeException("Cannot convert seconds: "+seconds);
	}

	return seconds + (minute * 60) + (hour * 3600);
}

void FlightDataReader::rewind()
{
	mInputStream->clear();
	mInputStream->seekg(0, std::ios::beg);
}

void FlightDataReader::readHeader()
{
	int spaceA, spaceB, cellM, cellN;

	*mInputStream >> spaceA;
	*mInputStream >> spaceB;
	*mInputStream >> cellM;
	*mInputStream >> cellN;
	*mInputStream >> mTimeStep;

	mSpaceSize = Cell(spaceA,spaceB);
	mCellSize = Cell(cellM, cellN);
}

std::vector<Flight> FlightDataReader::readFlights()
{
	std::vector<Flight> flights;

	while(readNextFlight()) {
		flights.push_back(mCurrentFlight);
	}

	return flights;
}

bool FlightDataReader::readNextFlight()
{
	int flightNum, numberOfControlPoints, x,y, time;
	if (!(*mInputStream >> flightNum)) {
		return false;
	}
	if (!(*mInputStream >> numberOfControlPoints)) {
		throw RuntimeException("Cannot read number of control points");
	}

	mCurrentFlight = Flight(flightNum);
	for (int i = 0; i< numberOfControlPoints; i++) {
		*mInputStream >> x;
		*mInputStream >> y;
		time = timeStringToSeconds();
		mCurrentFlight.addControlPoint(time, Cell(x,y));
	}
	return true;
}
