#pragma once
#ifndef RECORD_H
#define RECORD_H

#include <fstream>

using namespace std;

class Record
{
public:

	Record();
	Record(char*);
	~Record();

	void Open(const char*);
	void Write(char* txt);

private:

	ofstream m_stream;
};

#endif