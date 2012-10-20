#ifndef TESTS_H_
#define TESTS_H_

#include <assert.h>
#include "Include.h"
#include "InvolvedCellsSeeker.h"

class TestRunner {
public:
	TestRunner(void) {};
	~TestRunner(void) {};

	void run();
private:
	void testInvolvedCellsSeeker();
	void testCellHash();
	template <class T> int assertVectorsSame(std::vector<T> actual, std::vector<T> expected);
};

#endif //TESTS_H_