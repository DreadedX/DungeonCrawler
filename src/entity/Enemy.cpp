# include "Standard.h"

GLuint tex = 0;

void Enemy::init() {

    tex = Texture::load("entity/enemy");
}

void Enemy::tick() {

}

void Enemy::render() {

    Render::entity(position, vec4(21.0f/16.0f, 19.0f/16.0f, 1, 0), tex);
}
