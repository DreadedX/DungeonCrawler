#ifndef ENTITY_H
#define ENTITY_H

class Entity {

    public:
	vec4 position = vec4(0, 0, 0.0f, 1.0f);

	void init();
	void tick();
	void render();
};

#endif
