#include "Record.h"


Record::Record()
{
}

Record::Record(char* filename)
{
	m_stream.open(filename, fstream::app);
}

void Record::Write(char* txt)
{
	m_stream << txt << endl;
}

Record::~Record()
{
	m_stream.close();
}

// Open the log file for writing
void Record::Open(const char* filename)
{
	m_stream.open(filename, fstream::app);
}