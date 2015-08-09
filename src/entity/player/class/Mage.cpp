# include "Standard.h"

void Mage::init() {

    Player::init("entity/player/class/mage");
}

void Mage::attack() {

    Log::print("This is a mage attack", DEBUG);
}
