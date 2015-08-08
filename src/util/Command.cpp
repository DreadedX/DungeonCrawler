# include "Standard.h"

namespace Command {

    bool run(std::string command) {

	// If the command is "test"
	if(command == commandList[0]) {

	    // Print hello world message 
	    Log::print("Hello world!", DEBUG);
	} else {

	    // Return false to signify that the command does not exist
	    return false;
	}

	// Return true ti signifu that the command exists
	return true;
    }
}
