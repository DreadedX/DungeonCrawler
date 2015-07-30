#include "Standard.h"

static int tex = 0;

const float frictionFloat = pow(0.8f, VT);
const float acceleration = 10.0f / (1 / (1 - frictionFloat)) * VT;
const mat4 friction = scale(mat4(IDENTITY), vec3(frictionFloat));
vec4 velocity = vec4(0.0f, 0.0f, 0.0f, 0.0f);

void Entity::init() {

    if (!tex) {
	tex = Texture::load("entity/player");
    }
}

void Entity::tick() {

    // Apply friction
    velocity = friction * velocity;

    // If movement speed is really low set it to 0
    if ((velocity.x > -0.01f) && (velocity.x < 0.01f) && velocity.x != 0) velocity.x = 0;
    if ((velocity.y > -0.01f) && (velocity.y < 0.01f) && velocity.y != 0) velocity.y = 0;

    // Move on given input
    if (Input::isPressed(Key::UP)) velocity.y -= acceleration;
    if (Input::isPressed(Key::DOWN)) velocity.y += acceleration;
    if (Input::isPressed(Key::LEFT)) velocity.x -= acceleration;
    if (Input::isPressed(Key::RIGHT)) velocity.x += acceleration;

    // Translate
    mat4 move = translate(IDENTITY, vec3(velocity.x, velocity.y, velocity.z));
    position = move * position;
}

void Entity::render() {

    Render::tile(position, tex);
}
