#include "Standard.h"

namespace Log {

    void print(std::string msg, int type) {

	// Set default values
	std::string prefix = "";
	std::string color  = "\033[0m";

	switch (type) {
	    
	    // Debug message
	    case DEBUG:

#if DEBUG_MODE
		prefix = "DEBUG";
		color = "\033[37m";
#else
		return;
#endif
		break;

	    // Info message
	    case INFO:

		prefix = "INFO";
		break;

	    // Warning message
	    case WARNING:

		prefix = "WARNING";
		color = "\033[33m";
		break;

	    // Error message
	    case ERROR:

		prefix = "ERROR";
		color = "\033[31m";
#if !PRINT_TO_TERMINAL
		// If the printing of message to the terminal has been disabled still print erorrs
		std::cout << color << "[" << prefix << "] " << msg << "\u001B[0m" << std::endl;
#endif
		break;

	    // Unknown message
	    default:

		prefix = "Unknown";
		break;
	}

#if PRINT_TO_TERMINAL
	// Print the message to the terminal
	std::cout << color << "[" << prefix << "] " << msg << "\u001B[0m" << std::endl;
#endif

	// Print the message to the ingame console
	Console::log(String::format("[%s] %s", prefix.c_str(), msg.c_str()));
    }
}
