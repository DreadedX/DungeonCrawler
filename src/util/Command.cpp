# include "Standard.h"

namespace Command {

    bool run(std::string command) {

	// If the command is "test"
	if (command == commandList[0]) {

	    // Print hello world message 
	    Log::print("Hello world!", DEBUG);
	// If the command is "give"
	} else if (command == commandList[1]) {

	    while(true) {

		Item item = Randomizer::item();
		if(!Level::getPlayer()->addItem(item)) {
		    break;
		}
	    }

	    // Item item = Randomizer::item();
	    // if (!Level::getPlayer()->addItem(item)) {
	    // // if (!Level::getPlayer()->addItem(&ItemType::BOW, &Modifier::AWESOME, &Enchantment::FLAMING)) {
            //
		// Log::print("Inventory is full", DEBUG);
	    // }
	// If the command is "remove"
	} else if (command == commandList[2]) {

	    Level::getPlayer()->removeItem(0);
	// If the command is "list"
	} else if (command == commandList[3]) {

	    Level::getPlayer()->listInventory();
	// If the command is "sell"
	} else if (command == commandList[4]) {

	    Level::getPlayer()->changeMoney(45.5);
	// If the command is "buy"
	} else if (command == commandList[5]) {

	    if(!Level::getPlayer()->changeMoney(-21.6)) {

		Log::print("Not enough money", DEBUG);
	    }
	} else {

	    // Return false to signify that the command does not exist
	    return false;
	}

	// Return true ti signifu that the command exists
	return true;
    }
}
