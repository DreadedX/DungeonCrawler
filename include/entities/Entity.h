#ifndef ENTITY_H
#define ENTITY_H

class Entity {

    v2f velocity = {0, 0};
    float friction = 0.8f;
    float acceleration = 10.0f / (1 / (1 - friction));
    int tex;

    bool canJump = false;
    bool canDash = true;

    public:
	v2f pos = {300, 300};

	void init();
	void tick();
	void render();
};

#endif
