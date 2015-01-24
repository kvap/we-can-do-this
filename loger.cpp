#include "loger.hpp"

Loger::Loger(const string objectName)
{
	this->_objectName = objectName;
}

void Loger::Log(const string info)
{
	time_t t = time(0);
	struct tm * now = localtime(&t);
	ofstream fLogStream;
	fLogStream.open("log.txt", fstream::out);
	fLogStream << "[" << now->tm_mday << "."
		<< now->tm_mon + 1 << "." << now->tm_year + 1900
		<< " " << now->tm_hour << ":" << now->tm_min
		<< ":" << now->tm_sec << "] " << this->_objectName
		<< ": ";
	fLogStream << info << endl;
	fLogStream.close();
	return;
}

