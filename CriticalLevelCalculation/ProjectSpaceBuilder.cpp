#include "ProjectSpaceBuilder.h"


ProjectSpaceBuilder::ProjectSpaceBuilder(const ProjectInfo &projectInfo,std::vector<Flight> flights)
	: mProjectInfo(projectInfo), mFlights(flights), mCurrentTime(projectInfo.timeStart)
{

}

ProjectSpaceBuilder::~ProjectSpaceBuilder(void)
{
}

bool ProjectSpaceBuilder::nextTime() {
	if (mCurrentTime > mProjectInfo.timeFinish) {
		return false;
	}
	return true;
}

ProjectSpace ProjectSpaceBuilder::build()
{
	ProjectSpace space(mProjectInfo.spaceSize, mProjectInfo.spaceSize);

	for(int i=0; i<mFlights.size(); i++) {
		if (mFlights[i].getTimeStart() >= mCurrentTime && mFlights[i].getTimeFinish() <= mCurrentTime) {
			int flight = mFlights[i].getFlightNum();
			Cell p = mFlights[i].getPositionAtTime(mCurrentTime);
			space.addControlPoint(flight, p);
		}
	}

	space.setTime(mCurrentTime);

	mCurrentTime+=mProjectInfo.timeStep;
	return space;
}
