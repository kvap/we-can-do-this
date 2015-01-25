#ifndef LOGER_HPP
#define LOGER_HPP
#include <ctime>
#include <string.h>
#include <string>
#include <fstream>

using namespace std;

class Loggable
{
public:
	Loggable(const string objectName);
	virtual void Log();
	
protected:
	void Log(const string info);
private:
	string _objectName;
};

#endif
