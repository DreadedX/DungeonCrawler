#include "Standard.h"

namespace Log {

    void print(std::string msg, int type) {

	std::string prefix = "";
	std::string color = "\033[0m";

	switch (type) {
	    case DEBUG:
#if DEBUG_MODE
		prefix = "DEBUG";
		color = "\033[37m";
#else
		return;
#endif
		break;
	    case INFO:
		prefix = "INFO";
		break;
	    case WARNING:
		prefix = "WARNING";
		color = "\033[33m";
		break;
	    case ERROR:
		prefix = "ERROR";
		color = "\033[31m";
#if !PRINT_TO_TERMINAL
		std::cout << color << "[" << prefix << "] " << msg << "\u001B[0m" << std::endl;
#endif
		break;
	    default:
		prefix = "Unknown";
		break;
	}

#if PRINT_TO_TERMINAL
	std::cout << color << "[" << prefix << "] " << msg << "\u001B[0m" << std::endl;
#endif
	Console::log(String::format("[%s] %s", prefix.c_str(), msg.c_str()));
    }
}
