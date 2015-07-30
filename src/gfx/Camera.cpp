# include "Standard.h"

Entity *player;
vec4 positionLast;

void Camera::init() {
    player = Level::getPlayer();

    positionLast = player->position;
}

void Camera::tick() {
    vec4 positionDelta = positionLast - player->position;

    glTranslatef(positionDelta.x, positionDelta.y, positionLast.z);

    positionLast = player->position;
}

void Camera::render() {

}
