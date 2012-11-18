#include "ProjectInfo.h"


ProjectInfo::ProjectInfo(void)
{
}


ProjectInfo::~ProjectInfo(void)
{
}

std::vector<int> ProjectInfo::serialize()
{
	std::vector<int> serialized;
	serialized.push_back(spaceSize.x);
	serialized.push_back(spaceSize.y);
	serialized.push_back(cellSize.x);
	serialized.push_back(cellSize.y);
	serialized.push_back(timeStep);
	serialized.push_back(timeStart);
	serialized.push_back(timeFinish);
	return serialized;
}

void ProjectInfo::deserialize( std::vector<int> data )
{

	spaceSize.x = data[0];
	spaceSize.y = data[1];
	cellSize.x = data[2];
	cellSize.y = data[3];
	timeStep = data[4];
	timeStart = data[5];
	timeFinish = data[6];
}

std::stringstream ProjectInfo::dump() {
	std::stringstream ss;
	ss << "Cells: " << spaceSize.dump().str() << ", ";
	ss << "Size: " << cellSize.dump().str() << ", ";
	ss << "Step: " << timeStep << " sec, ";
	ss << "Time: " << timeStart << " - " << timeFinish << " ";

	return ss;
};