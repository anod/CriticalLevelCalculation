/*
 * Profiler.h
 *
 *      Author: Alex
 */

#ifndef PROFILER_H_
#define PROFILER_H_

#include <vector>
#include <time.h>
#include <sstream>
#include "RuntimeException.h"

/**
 * Class to profile execution time of several parts of the application
 * Singleton
 */
class Profiler
{
public:
	~Profiler(void);
	/**
	 * Singleton
	 * @return instance of Profiler
	 */
	static Profiler& getInstance()
	{
		static Profiler instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}
	/**
	 * Start profile part of the code
	 * @param name
	 */
	void start(const char* name);
	/**
	 * Finish previously started profiling
	 */
	void finish();
	/**
	 * @return collected information
	 */
	std::stringstream dump();
	/**
	 * Switch for profiler
	 * @param enabled
	 */
	void setEnabled(bool enabled) { mEnabled = enabled; };
private:
	std::vector<const char *> mNames;
	std::vector<double> mTimes;
	clock_t mClockBegin;
	bool mRunning;
	bool mEnabled;

	//Singleton
	Profiler(void);
	Profiler(Profiler const &);
	void operator=(Profiler const&);
};

#endif //PROFILER_H_
