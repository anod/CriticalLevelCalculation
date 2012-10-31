#include "FlightDataReader.h"
#include "RuntimeException.h"


FlightDataReader::FlightDataReader(std::ifstream* stream, std::string fileName)
	: mCurrentFlightNumber(0), mNumberOfControlPoints(0), mInputStream(stream), mFileName(fileName)
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
//	mInputStream->rdbuf()->pubsetbuf(mBuffer, BUFFER_SIZE);
}

bool FlightDataReader::readNextControlPoint()
{
	if (mNumberOfControlPoints == 0) { //New flight
		mCurrentFlightNumber = 0;
		if (!(*mInputStream >> mCurrentFlightNumber)) {
			return false;
		}
		if (!(*mInputStream >> mNumberOfControlPoints)) {
			throw RuntimeException("Cannot read number of control points");
		}
		if (mNumberOfControlPoints == 0) {
			return readNextControlPoint();
		}
	}
	int x,y = 0;
	*mInputStream >> x;
	*mInputStream >> y;
	mCurrentControlPoint = Cell(x,y);
	mCurrentTime = timeStringToSeconds();
	mNumberOfControlPoints--;
	return true;
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
	mNumberOfControlPoints = 0;
	mInputStream->clear();
	mInputStream->seekg(0, std::ios::beg);
}

void FlightDataReader::readHeader()
{
	int tmp, spaceA, spaceB, cellM, cellN, i = 0;

	while ( i < 5 ) {
		*mInputStream >> tmp;
		if (!tmp) {
			continue;
		}
		if ( i == 0 ) {
			spaceA = tmp;
		} else if ( i == 1 ) {
			spaceB = tmp;
		} else if ( i == 2 ) {
			cellM = tmp;
		} else if ( i == 3 ) {
			cellN = tmp;
		}
		// Skip one
		i++;
	}
	mSpaceSize = Cell(spaceA,spaceB);
	mCellSize = Cell(cellM, cellN);
}
