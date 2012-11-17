#include "ProjectSpaceBuilder.h"


ProjectSpaceBuilder::ProjectSpaceBuilder(const ProjectInfo &projectInfo,std::vector<Flight> flights)
	: mProjectInfo(projectInfo), mFlights(flights), mCurrentTime(projectInfo.timeStart)
{
	mCurrentTime-=mProjectInfo.timeStep;
}

ProjectSpaceBuilder::~ProjectSpaceBuilder(void)
{
}

bool ProjectSpaceBuilder::nextTime() {
	mCurrentTime+=mProjectInfo.timeStep;
	if (mCurrentTime > mProjectInfo.timeFinish) {
		return false;
	}
	return true;
}

ProjectSpace ProjectSpaceBuilder::build()
{
	ProjectSpace space(mProjectInfo.spaceSize, mProjectInfo.spaceSize);

	for(size_t i=0; i<mFlights.size(); i++) {
		if (mCurrentTime >= mFlights[i].getTimeStart() && mCurrentTime <= mFlights[i].getTimeFinish()) {
			int flight = mFlights[i].getFlightNum();
			Cell p = mFlights[i].getPositionAtTime(mCurrentTime);
 			space.addControlPoint(flight, p);
		}
	}

	space.setTime(mCurrentTime);

	return space;
}
