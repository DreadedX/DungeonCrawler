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
	    case DEBUG_I:
#if DEBUG_MODE
		prefix = "DEBUG";
		color = "\033[36m";
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
		break;
	    default:
		prefix = "Unknown";
		break;
	}

	std::cout << color << "[" << prefix << "] " << msg << "\u001B[0m" << std::endl;
    }
}
