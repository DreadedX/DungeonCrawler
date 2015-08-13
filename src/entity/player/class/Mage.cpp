# include "Standard.h"

void Mage::init() {

    Player::init("entity/player/class/mage", vec4(17.0f/16.0f, 20.0f/16.0f, 1, 0));
}

void Mage::attack() {

    Log::print("This is a mage attack", DEBUG);
}
