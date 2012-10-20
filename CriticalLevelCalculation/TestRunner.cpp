#include "TestRunner.h"

void TestRunner::run() {
	std::cout << "1. ";
	testInvolvedCellsSeeker();
	std::cout << "2. ";
	testCellHash();
	std::cout << "Done.";
	
} 

void TestRunner::testInvolvedCellsSeeker() {
	std::cout << "Running InvolvedCellsSeeker Test" << std::endl;
	InvolvedCellsSeeker seeker(Cell(10,10));

	std::cout << " -- 1: ";
	Cell expectedArr1[] = { Cell(4,5), Cell(5,6) };
	std::vector<Cell> expected1 (expectedArr1, expectedArr1 + sizeof(expectedArr1) / sizeof(expectedArr1[0]) );
	std::vector<Cell> actual1 = seeker.seek(Cell(3,4), Cell(6,7));
	
	assertVectorsSame(actual1,expected1);
	std::cout << "Ok" << std::endl;

	std::cout << " -- 2: Right ";
	Cell expectedArr2[] = { Cell(4,4), Cell(5,4) };
	std::vector<Cell> expected2 (expectedArr2, expectedArr2 + sizeof(expectedArr2) / sizeof(expectedArr2[0]) );
	std::vector<Cell> actual2 = seeker.seek(Cell(3,4), Cell(6,4));

	assertVectorsSame(actual2,expected2);
	std::cout << "Ok" << std::endl;

	std::cout << " -- 3: Up,Left ";
	Cell expectedArr3[] = { Cell(4,4), Cell(4,3), Cell(5,3) };
	std::vector<Cell> expected3 (expectedArr3, expectedArr3 + sizeof(expectedArr3) / sizeof(expectedArr3[0]) );
	std::vector<Cell> actual3 = seeker.seek(Cell(6,3), Cell(3,4));

	assertVectorsSame(actual3,expected3);
	std::cout << "Ok" << std::endl;

	std::cout << " -- 4: Left,Up ";
	Cell expectedArr4[] = { Cell(6,4), Cell(6,5), Cell(7,5) };
	std::vector<Cell> expected4 (expectedArr4, expectedArr4 + sizeof(expectedArr4) / sizeof(expectedArr4[0]) );
	std::vector<Cell> actual4 = seeker.seek(Cell(7,6), Cell(6,3));

	assertVectorsSame(actual4,expected4);
	std::cout << "Ok" << std::endl;

	std::cout << " -- 5: Up ";
	Cell expectedArr5[] = { Cell(7,4), Cell(7,5) };
	std::vector<Cell> expected5 (expectedArr5, expectedArr5 + sizeof(expectedArr5) / sizeof(expectedArr5[0]) );
	std::vector<Cell> actual5 = seeker.seek(Cell(7,6), Cell(7,3));

	assertVectorsSame(actual5,expected5);
	std::cout << "Ok" << std::endl;

	std::cout << " -- 6: Long Distance ";
	Cell expectedArr6[] = { Cell(2,9), Cell(2,8), Cell(3,8), Cell(3,7), Cell(4,7), Cell(4,6), Cell(5,6), Cell(6,6), Cell(6,5), Cell(7,5), Cell(7,4), Cell(8,4), Cell(8,3), Cell(9,3), Cell(10,3), Cell(10,2), Cell(11,2), Cell(11,1) };
	std::vector<Cell> expected6 (expectedArr6, expectedArr6 + sizeof(expectedArr6) / sizeof(expectedArr6[0]) );
	std::vector<Cell> actual6 = seeker.seek(Cell(12,1), Cell(1,9));

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

void TestRunner::testCellHash()
{
	std::cout << "Running Cell Hash Test" << std::endl;

	std::unordered_map<int, bool> test;
	std::cout << " -- 1: ";
	for (unsigned int i =0 ; i< 500; i++) {
		for (unsigned int j =0 ; j< 500; j++) {
			Cell c(i,j);
			size_t hash = c.hash();
			assert(("Hash already exist", !test[hash]));
		}
	}
	std::cout << "Ok" << std::endl;
}
