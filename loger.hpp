#ifndef LOGER_HPP
#define LOGER_HPP
#include <ctime>
#include <string.h>
#include <string>
#include <fstream>

using namespace std;

class Loger
{
public:
	Loger(const string objectName);
	void Log() = 0;
	
protected:
	void Log(const string info);
private:
	string _objectName;
};

#endif
