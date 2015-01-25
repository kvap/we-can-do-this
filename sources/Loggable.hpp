#ifndef LOGER_HPP
#define LOGER_HPP
#include <ctime>
#include <string.h>
#include <string>
#include <fstream>

class Loggable {
	public:
		Loggable(const std::string objectName);
	protected:
		void Log(const std::string info);
	private:
		std::string _objectName;
};

#endif
