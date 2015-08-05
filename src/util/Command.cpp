# include "Standard.h"

namespace Command {

    bool run(std::string command) {

	if(command == commandList[0]) { //test
	    Log::print("Hello world!", DEBUG);
	} else {
	    return false;
	}

	return true;
    }
}
