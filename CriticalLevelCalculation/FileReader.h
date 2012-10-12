#pragma once
#include <string>
#include <iosfwd>
#include <string>
using namespace std;

class FlightDataReader
{
public:
	FlightDataReader(string filename, int spaceNumber);
	~FlightDataReader(void);
	void open();
	string getline();
private:
	string mFileName;
	ifstream mInputStream;
};

