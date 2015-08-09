#include "Standard.h"

int tex = 0;

const float frictionFloat = pow(0.8f, 1/VT);
float acceleration = (3.0f/16) / (1 / (1 - frictionFloat)) * VT;
const mat4 friction = scale(mat4(IDENTITY), vec3(frictionFloat));
vec4 velocity = vec4(0, 0, 0, 0);

Item *inventory[INVENTORY_SIZE];
float money = 0;

Player::Player() {

    for (int i = 0; i < INVENTORY_SIZE; i++) {

	inventory[i] = new Item(&ItemType::NONE, &Modifier::NONE, &Enchantment::NONE);
    }

}

// Called by classes that inherent this class
void Player::init(std::string texture) {

    // Load the appropriate texture
    tex = Texture::load(texture);

    // inventory[0] = new
}

void Player::tick() {
    
    // Apply friction
    velocity = friction * velocity;

    // If movement speed is really low set it to 0
    if ((velocity.x > -0.01f) && (velocity.x < 0.01f) && velocity.x != 0) {

	velocity.x = 0;
    }

    if ((velocity.y > -0.01f) && (velocity.y < 0.01f) && velocity.y != 0) {

	velocity.y = 0;
    }

    // Check keyboard input and move the player on the correct input
    if (Input::isPressed(Key::UP)) {

	velocity.y += acceleration;
    }

    if (Input::isPressed(Key::DOWN)) {

	velocity.y -= acceleration;
    }

    if (Input::isPressed(Key::LEFT)) {

	velocity.x -= acceleration;
    }

    if (Input::isPressed(Key::RIGHT)) {

	velocity.x += acceleration;
    }

    // Check if the attack key has been pressed
    if (Input::isPressed(Key::ATTACK)) {
	
	// Execute attack, devined in inherented classes
	// attack();
	
	inventory[0]->use();
    }

    // Move the player
    mat4 move = translate(IDENTITY, vec3(velocity.x, velocity.y, velocity.z));
    position = move * position;
}

// bool Player::addItem(const ItemTypeData *itemType, const ModifierData *modifier, const EnchanmentData *enchantment) {
//
//     for (int i = 0; i < INVENTORY_SIZE; i++) {
//
// 	if (inventory[i]->getName() == "Empty") {
//
// 	    inventory[i] = new Item(itemType, modifier, enchantment);
// 	    return true;
// 	}
//     }
//
//     return false;
// }

bool Player::addItem(Item item) {

    for (int i = 0; i < INVENTORY_SIZE; i++) {

	if (inventory[i]->getName() == "Empty") {

	    *inventory[i] = item;
	    return true;
	}
    }

    return false;
}

void Player::removeItem(int slot) {

    inventory[slot] = new Item(&ItemType::NONE, &Modifier::NONE, &Enchantment::NONE);
}

bool Player::changeMoney(float change) {

    if (money+change >= 0) {

	money += change;
	return true;
    }

    return false;
}

void Player::listInventory() {

    Log::print("----Inventory----", DEBUG);
    Log::print(String::format("$%.1f", money), DEBUG);

    for (int i = 0; i < INVENTORY_SIZE; i++) {
    	
	if (inventory[i]->getName() != "Empty") {
	    Log::print(String::format("%i: %s, $%.1f, %.1f", i, inventory[i]->getName().c_str(), inventory[i]->getValue(), inventory[i]->getWeight()), DEBUG);
	}
    }

}

void Player::render() {

    // Render the player texture at it's location
    Render::tile(position, tex);
}

Player::~Player() {

    for (int i = 0; i < INVENTORY_SIZE; i++) {
    	
	delete inventory[i];
    }
}
