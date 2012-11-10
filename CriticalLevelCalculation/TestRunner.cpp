#include "TestRunner.h"

void TestRunner::run() {
	std::cout << "1. ";
	testInvolvedCellsSeeker();
	std::cout << "2. ";
	testCriticalLevelDetector();
	std::cout << "3. ";
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
	Cell expectedArr3[] = { Cell(4,4), Cell(5,3) };
	std::vector<Cell> expected3 (expectedArr3, expectedArr3 + sizeof(expectedArr3) / sizeof(expectedArr3[0]) );
	std::vector<Cell> actual3 = seeker.seek(Cell(6,3), Cell(3,4));

	assertVectorsSame(actual3,expected3);
	std::cout << "Ok" << std::endl;

	std::cout << " -- 4: Left,Up ";
	Cell expectedArr4[] = { Cell(6,4), Cell(7,5) };
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

	std::cout << " -- 6: Wiki Example ";
	Cell expectedArr6[] = { Cell(3,2), Cell(4,3), Cell(5,3), Cell(6,4), Cell(7,4), Cell(8,4), Cell(9,5), Cell(10,5), Cell(11,6) };
	std::vector<Cell> expected6 (expectedArr6, expectedArr6 + sizeof(expectedArr6) / sizeof(expectedArr6[0]) );
	std::vector<Cell> actual6 = seeker.seek(Cell(2,2), Cell(12,6));
	assertVectorsSame(actual6,expected6);
	std::cout << "Ok" << std::endl;

	std::cout << " -- 6: Wiki Example Oposite Direction ";
	Cell expectedArr7[] = { Cell(3,2), Cell(4,3), Cell(5,3), Cell(6,4), Cell(7,4), Cell(8,4), Cell(9,5), Cell(10,5), Cell(11,6) };
	std::vector<Cell> expected7 (expectedArr7, expectedArr7 + sizeof(expectedArr7) / sizeof(expectedArr7[0]) );
	std::vector<Cell> actual7 = seeker.seek(Cell(12,6), Cell(2,2));
	assertVectorsSame(actual7,expected7);
	std::cout << "Ok" << std::endl;
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
			test[hash] = true;
		}
	}
	std::cout << "Ok" << std::endl;
}

void TestRunner::testCriticalLevelDetector()
{
	std::cout << "Running CriticalLevelDetector Test" << std::endl;

	int dataArr[27] = { 3600, 2, 2, 1, 1000, 4, 3, 1, 1001, 8, 4, 2, 1002, 1003, 5, 6, 1, 1004, 10, 11, 2, 1005, 1006, 12, 6, 1, 1007 };
	std::vector<int> spaceData1;
	spaceData1.assign(dataArr, dataArr + 27);
	ProjectSpace projectSpace(Cell(100000,100000),Cell(1000,1000));
	projectSpace.deserialize(spaceData1);

	CriticalLevel level1, level2, expected1;

	expected1[1000].push_back(1002);
	expected1[1000].push_back(1003);
	expected1[1000].push_back(1007);

	expected1[1002].push_back(1000);
	expected1[1003].push_back(1000);

	expected1[1007].push_back(1000);

	expected1[1001].push_back(1007);
	expected1[1007].push_back(1001);

	CriticalLevelDetector detector(projectSpace);

	std::cout << " -- 1: Detect Serial ";
	level1 = detector.detectSerial();
	assertCriticalLevelSame(level1, expected1);
	std::cout << "Ok" << std::endl;

	std::cout << " -- 2: Detect Parallel ";
	level2 = detector.detectParallel();
	assertCriticalLevelSame(level2, expected1);
	std::cout << "Ok" << std::endl;

}

int TestRunner::assertCriticalLevelSame(CriticalLevel actual, CriticalLevel expected) {
	CriticalLevel::const_iterator it1,it2;
	assert(("Size is different", actual.size() == expected.size()));
	for( it1 = actual.begin(); it1 != actual.end(); it1++) {
		int flight = (*it1).first;
		FlightList list = (*it1).second;
		assert(("No key found", expected.find(flight) != expected.end()));
		assertVectorsSame(list, expected[flight]);
	}

	return 1;
}

template <class T>
int TestRunner::assertVectorsSame(std::vector<T> actual, std::vector<T> expected) {

	assert(("Size is different", actual.size() == expected.size()));

	for(size_t i = 0;i<actual.size();i++) {
		assert(("Elements are not equal", actual.at(i) == expected.at(i)));
	}

	return 1;

}