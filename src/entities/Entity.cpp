#include "entities/Entity.h"
#include "Input.h"
#include "gfx/Screen.h"
#include "Defs.h"
#include "Config.h"

i2 pos = {300, 300};
int speed = 6;

void Entity::tick() {
    if (Input::isPressed(Key::UP)) {
	pos.y -= speed;
    }
    if (Input::isPressed(Key::LEFT)) {
	pos.x -= speed;
    }
    if (Input::isPressed(Key::DOWN)) {
	pos.y += speed;
    }
    if (Input::isPressed(Key::RIGHT)) {
	pos.x += speed;
    }
}

void Entity::render() {
    f3 colour {1.0f, 0.5f, 0.2f};
    Screen::drawRectangle(pos.x-100, pos.y-100, pos.x+100, pos.y+100, colour);

}
