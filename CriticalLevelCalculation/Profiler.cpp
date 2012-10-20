#include "Profiler.h"


Profiler::Profiler(void)
	: mRunning(false), mEnabled(false)
{
}


Profiler::~Profiler(void)
{
}

void Profiler::start( const char* name )
{
	if (!mEnabled) {
		return;
	}
	if (mRunning) {
		std::string message = "Profiling already running: '" + std::string(mNames.back()) + "', '" + std::string(name) + "' cannot be started";
		throw std::exception(message.c_str());
	}
	mNames.push_back(name);
	mRunning = true;
	mClockBegin = clock();
}

void Profiler::finish()
{
	clock_t end = clock();
	if (!mEnabled) {
		return;
	}
	if (!mRunning) {
		throw std::exception("Profiling is not running");
	}
	double elapsed_secs = double(end - mClockBegin) / CLOCKS_PER_SEC;
	mTimes.push_back(elapsed_secs);
	mRunning = false;
}

std::stringstream Profiler::dump()
{
	std::stringstream ss;
	if (!mEnabled) {
		return ss;
	}
	ss << std::endl << "Profiler Output: " << std::endl;
	ss << "---------------" << std::endl;
	for( size_t i = 0; i < mNames.size(); i++) {
		ss << mNames.at(i) << ": " << mTimes.at(i) << " sec" << std::endl;
	}
	return ss;
}
