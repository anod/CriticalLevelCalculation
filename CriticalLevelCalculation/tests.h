#ifndef TESTS_H_
#define TESTS_H_

#include <assert.h>
#include "Include.h"
#include "InvolvedCellsSeeker.h"

void testInvolvedCellsSeeker() {
	std::cout << "Running InvolvedCellsSeeker Test" << std::endl;
	InvolvedCellsSeeker seeker(Point(10,10));
	std::vector<Point> result = seeker.seek(Point(3,4), Point(6,7));
}

void runTests() {
	std::cout << "1. ";
	testInvolvedCellsSeeker();

} 

int assertVectorsSame(std::vector<Point> actual, std::vector<Point> expected) {

	assert(("Size is different", actual.size() != expected.size()));

	for(size_t i = 0;i<actual.size();i++) {
		assert(("Elements are not equal", actual.at(i) != expected.at(i)));
	}

	return 1;

}

#endif //TESTS_H_