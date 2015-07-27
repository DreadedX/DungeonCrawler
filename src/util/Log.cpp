#include "Standard.h"

void Log::print(int msg) {
    std::cout << "[DEBUG] " << msg << std::endl;
}

void Log::print(std::string msg) {
    Log::print(msg, DEBUG);
}

void Log::print(std::string msg, int type) {

    std::string prefix;

    switch (type) {
	case DEBUG:
	    prefix = "DEBUG";
	    break;
	case INFO:
	    prefix = "INFO";
	    break;
	case WARNING:
	    prefix = "WARNING";
	    break;
	case ERROR:
	    prefix = "ERROR";
	    break;
	default:
	    prefix = "Unknown";
	    break;
    }

    std::cout << "[" << prefix << "] " << msg << std::endl;
}
