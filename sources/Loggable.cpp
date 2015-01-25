#include "Loggable.hpp"

Loggable::Loggable(const std::string objectName) {
	this->_objectName = objectName;
}

void Loggable::Log(const std::string info) {
	time_t t = time(0);
	struct tm * now = localtime(&t);
	std::ofstream fLogStream;
	fLogStream.open("log.txt", std::fstream::out);
	fLogStream << "[" << now->tm_mday << "."
		<< now->tm_mon + 1 << "." << now->tm_year + 1900
		<< " " << now->tm_hour << ":" << now->tm_min
		<< ":" << now->tm_sec << "] " << this->_objectName
		<< ": ";
	fLogStream << info << std::endl;
	fLogStream.close();
	return;
}

