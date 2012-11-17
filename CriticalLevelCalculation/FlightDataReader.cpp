#include "FlightDataReader.h"
#include "RuntimeException.h"


FlightDataReader::FlightDataReader(std::ifstream* stream, std::string fileName)
	: mInputStream(stream), mFileName(fileName), mTimeStart(WRONG_TIME), mTimeFinish(WRONG_TIME)
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

	mSpaceSize = Cell(Utils::coordToCell(spaceA,cellM), Utils::coordToCell(spaceB,cellN));
	mCellSize = Cell(cellM, cellN);
}

std::vector<Flight> FlightDataReader::readFlights()
{
	std::vector<Flight> flights;

	while(readNextFlight()) {
		flights.push_back(mCurrentFlight);
		// Update times
		if (mTimeStart == WRONG_TIME) {
			mTimeStart = mCurrentFlight.getTimeStart();
			mTimeFinish = mCurrentFlight.getTimeFinish();
		} else {
			if (mCurrentFlight.getTimeStart() < mTimeStart) {
				mTimeStart = mCurrentFlight.getTimeStart();
			}
			if (mCurrentFlight.getTimeFinish() > mTimeFinish) {
				mTimeFinish = mCurrentFlight.getTimeFinish();
			}
		}

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
		Cell p =  Cell(x,y);
		mCurrentFlight.addControlPoint(time, p);
	}
	return true;
}

ProjectInfo FlightDataReader::getProjectInfo() const
{
	ProjectInfo info;

	info.spaceSize = mSpaceSize;
	info.cellSize = mCellSize;
	info.timeStep = mTimeStep;
	info.timeStart = mTimeStart;
	info.timeFinish = mTimeFinish;

	return info;
}
