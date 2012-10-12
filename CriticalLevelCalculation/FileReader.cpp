#include "FileReader.h"


FileReader::FileReader(string fileName)
{
	mFileName = fileName;
}


FileReader::~FileReader(void)
{
}

void FileReader::open()
{
	ifstream fin(mFileName);
}

string FileReader::getline()
{
	getline();
}

FileReader::close()
{

}
