#include "Standard.h"

// NOTE: Because this is a temporary test class it is not commented

static int tex = 0;

const float frictionFloat = pow(0.8f, 1/VT);
const float acceleration = (10.0f/16) / (1 / (1 - frictionFloat)) * VT;
// NOTE: When implementing jump there can be a different friction on the y-axis
const mat4 friction = scale(mat4(IDENTITY), vec3(frictionFloat));
vec4 velocity = vec4(0, 0, 0, 0);

void Entity::init() {

    if (!tex) {
	tex = Texture::load("entity/player");
    }
}

void Entity::tick() {

    // Apply friction
    velocity = friction * velocity;

    // If movement speed is really low set it to 0
    if ((velocity.x > -0.05f) && (velocity.x < 0.05f) && velocity.x != 0) velocity.x = 0;
    if ((velocity.y > -0.05f) && (velocity.y < 0.05f) && velocity.y != 0) velocity.y = 0;

    // Move on given input
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

    // Translate
    mat4 move = translate(IDENTITY, vec3(velocity.x, velocity.y, velocity.z));
    position = move * position;
    //
    // if (position.x+8 > Level::width * 16) {
	// position.x = Level::width * Level::tileScaleInt - 8;
    // }
    // if (position.x-8 < 0) {
	// position.x = 8;
    // }
    // if (position.y + 8 > Level::height * 16) {
	// position.y = Level::height * Level::tileScaleInt - 8;
    // }
    // if (position.y - 8 < 0) {
	// position.y = 8;
    // }
}

void Entity::render() {

    Render::tile(position, tex);
}
