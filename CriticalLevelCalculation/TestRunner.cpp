#include "TestRunner.h"

void TestRunner::run() {
	std::cout << "1. ";
	testInvolvedCellsSeeker();
} 

void TestRunner::testInvolvedCellsSeeker() {
	std::cout << "Running InvolvedCellsSeeker Test" << std::endl;
	InvolvedCellsSeeker seeker(Point(10,10));

	std::cout << " -- 1: ";
	Point expectedArr1[] = { Point(4,5), Point(5,6) };
	std::vector<Point> expected1 (expectedArr1, expectedArr1 + sizeof(expectedArr1) / sizeof(expectedArr1[0]) );
	std::vector<Point> actual1 = seeker.seek(Point(3,4), Point(6,7));
	
	assertVectorsSame(actual1,expected1);
	std::cout << "Ok" << std::endl;

	std::cout << " -- 2: Right ";
	Point expectedArr2[] = { Point(4,4), Point(5,4) };
	std::vector<Point> expected2 (expectedArr2, expectedArr2 + sizeof(expectedArr2) / sizeof(expectedArr2[0]) );
	std::vector<Point> actual2 = seeker.seek(Point(3,4), Point(6,4));

	assertVectorsSame(actual2,expected2);
	std::cout << "Ok" << std::endl;

	std::cout << " -- 3: Up,Left ";
	Point expectedArr3[] = { Point(4,4), Point(4,3), Point(5,3) };
	std::vector<Point> expected3 (expectedArr3, expectedArr3 + sizeof(expectedArr3) / sizeof(expectedArr3[0]) );
	std::vector<Point> actual3 = seeker.seek(Point(6,3), Point(3,4));

	assertVectorsSame(actual3,expected3);
	std::cout << "Ok" << std::endl;

	std::cout << " -- 4: Left,Up ";
	Point expectedArr4[] = { Point(6,4), Point(6,5), Point(7,5) };
	std::vector<Point> expected4 (expectedArr4, expectedArr4 + sizeof(expectedArr4) / sizeof(expectedArr4[0]) );
	std::vector<Point> actual4 = seeker.seek(Point(7,6), Point(6,3));

	assertVectorsSame(actual4,expected4);
	std::cout << "Ok" << std::endl;

	std::cout << " -- 5: Up ";
	Point expectedArr5[] = { Point(7,4), Point(7,5) };
	std::vector<Point> expected5 (expectedArr5, expectedArr5 + sizeof(expectedArr5) / sizeof(expectedArr5[0]) );
	std::vector<Point> actual5 = seeker.seek(Point(7,6), Point(7,3));

	assertVectorsSame(actual5,expected5);
	std::cout << "Ok" << std::endl;

	std::cout << " -- 6: Long Distance ";
	Point expectedArr6[] = { Point(2,9), Point(2,8), Point(3,8), Point(3,7), Point(4,7), Point(4,6), Point(5,6), Point(6,6), Point(6,5), Point(7,5), Point(7,4), Point(8,4), Point(8,3), Point(9,3), Point(10,3), Point(10,2), Point(11,2), Point(11,1) };
	std::vector<Point> expected6 (expectedArr6, expectedArr6 + sizeof(expectedArr6) / sizeof(expectedArr6[0]) );
	std::vector<Point> actual6 = seeker.seek(Point(12,1), Point(1,9));

	assertVectorsSame(actual6,expected6);
	std::cout << "Ok" << std::endl;
}

template <class T>
int TestRunner::assertVectorsSame(std::vector<T> actual, std::vector<T> expected) {

	assert(("Size is different", actual.size() == expected.size()));

	for(size_t i = 0;i<actual.size();i++) {
		assert(("Elements are not equal", actual.at(i) == expected.at(i)));
	}

	return 1;

}