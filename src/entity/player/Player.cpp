#include "Standard.h"

const float frictionFloat = pow(0.8f, 1/VT);
float acceleration = (1.5f/16) / (1 / (1 - frictionFloat)) * VT;
const mat4 friction = scale(mat4(IDENTITY), vec3(frictionFloat));
vec4 velocity = vec4(0, 0, 0, 0);

Item *inventory[INVENTORY_SIZE] = {nullptr};
float money = 0;

Player::Player(vec4 position): Entity(position) {

    for (int i = 0; i < INVENTORY_SIZE; i++) {

	inventory[i] = new Item();
    }

}

void Player::init(std::string texture, vec4 scale) {

    tex = Texture::load(texture);
    this->scale = scale;
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

    delete inventory[slot];
    inventory[slot] = nullptr;
    inventory[slot] = new Item;
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
	
	    Log::print(String::format("%i: %s, $%.1f, %.1f (lvl. %i)", i, inventory[i]->getName().c_str(), inventory[i]->getValue(), inventory[i]->getWeight(), inventory[i]->getLevel()), DEBUG);
	}
    }

}

void Player::render() {

    // Render the player texture at it's location
    Render::entity(position, scale/2, tex);
}

Player::~Player() {

    for (int i = 0; i < INVENTORY_SIZE; i++) {

	delete inventory[i];
	inventory[i] = nullptr;
    }
}
