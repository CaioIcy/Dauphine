#ifndef INCLUDE_LOGGER_H
#define INCLUDE_LOGGER_H

#include <string>
#include <sstream>
#include <cstdio>

enum LogLevel : uint8_t {
	INFO,
	WARN,
	ERROR,
	DEBUG
};

#define Log(level) Logger().log(level)

/**
* Class used for logging.
*
*/
class Logger {

	public:
		Logger();
		virtual ~Logger();

		std::ostringstream& log(const LogLevel level_);

	private:
		std::string levelToString(const LogLevel level_);

		std::ostringstream os;

};

#endif //INCLUDE_LOGGER_H
