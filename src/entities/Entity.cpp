#include "Standard.h"

void Entity::init() {

    tex = loadTexture("entity/player");
}

void Entity::tick() {

    velocity.x *= friction;
    velocity.y *= friction;

    if ((velocity.x > -0.01f) && (velocity.x < 0.01f) && velocity.x != 0) velocity.x = 0;
    if ((velocity.y > -0.01f) && (velocity.y < 0.01f) && velocity.y != 0) velocity.y = 0;

    if (Input::isPressed(Key::UP)) velocity.y -= acceleration;
    if (Input::isPressed(Key::DOWN)) velocity.y += acceleration;
    if (Input::isPressed(Key::LEFT)) velocity.x -= acceleration;
    if (Input::isPressed(Key::RIGHT)) velocity.x += acceleration;

    pos.x += velocity.x;
    pos.y += velocity.y;
}

void Entity::render() {

    Screen::drawTile(pos.x, pos.y, tex);
}
