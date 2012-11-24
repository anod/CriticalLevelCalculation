/*
 * ProjectSpaceBuilder.h
 *
 *      Author: Alex
 */

#ifndef PROJECT_SPACE_BUILDER_H_
#define PROJECT_SPACE_BUILDER_H_

#include "Include.h"
#include "ProjectSpace.h"

/**
 * Builds project space from Flight Path
 */
class ProjectSpaceBuilder
{
public:
	/**
	 *
	 * @param projectInfo project info
	 * @param flights list of flights with Flights Paths
	 */
	ProjectSpaceBuilder(const ProjectInfo &projectInfo, std::vector<Flight> flights);
	~ProjectSpaceBuilder(void);

	/**
	 * Build ProjectSpace for current time
	 * @return
	 */
	ProjectSpace build();
	/**
	 * Iterate to the next time
	 * @return true if there is more ProjectSpaces to build
	 */
	bool nextTime();
private:
	ProjectInfo mProjectInfo;

	/**
	 * seconds
	 */
	int mCurrentTime;
	std::vector<Flight> mFlights;
};

#endif // PROJECT_SPACE_BUILDER_H_
