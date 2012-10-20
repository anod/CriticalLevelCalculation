#ifndef PROFILER_H_
#define PROFILER_H_

#include <vector>
#include <time.h>
#include <sstream>

class Profiler
{
public:
	~Profiler(void);
	static Profiler& getInstance()
	{
		static Profiler instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}
	void start(const char* name);
	void finish();
	std::stringstream dump();
	void setEnabled(bool enabled) { mEnabled = enabled; };
private:
	Profiler(void);
	//Singleton
	Profiler(Profiler const &);
	void operator=(Profiler const&);
	std::vector<const char *> mNames;
	std::vector<double> mTimes;
	bool mRunning;
	clock_t mClockBegin;
	bool mEnabled;

};

#endif //PROFILER_H_