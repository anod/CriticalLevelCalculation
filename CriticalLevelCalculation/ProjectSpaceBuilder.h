#ifndef PROJECT_SPACE_BUILDER_H_
#define PROJECT_SPACE_BUILDER_H_

#include "Include.h"
#include "ProjectSpace.h"

class ProjectSpaceBuilder
{
public:
	ProjectSpaceBuilder(const ProjectInfo &projectInfo, std::vector<Flight> flights);
	~ProjectSpaceBuilder(void);

	ProjectSpace build();
	bool nextTime();
private:

	ProjectInfo mProjectInfo;

	int mCurrentTime;
	std::vector<Flight> mFlights;
};

#endif // PROJECT_SPACE_BUILDER_H_
