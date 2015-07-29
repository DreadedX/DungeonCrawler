# include "Standard.h"

v2f pos;
v2f posLast;
v2f dPos;

Entity *player;

void Camera::init() {
    player = Level::getPlayer();

    pos = player->pos;
    posLast = pos;
}

void Camera::tick() {
    pos = player->pos;
    dPos.x = posLast.x - pos.x;
    dPos.y = posLast.y - pos.y;
    
    glTranslatef(dPos.x, dPos.y, 0);
    
    // std::cout << pos.x << " " << posLast.x << " " << pos.y << " " << posLast.y << std::endl;

    posLast = pos;
}

void Camera::render() {

}
