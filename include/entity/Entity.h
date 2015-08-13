#ifndef ENTITY_H
#define ENTITY_H

class Entity {

    public:

	Entity(vec4 position);
	virtual ~Entity() {}

	vec4 position = vec4(0, 0, 0, 1);

	virtual void init() = 0;
	virtual void tick() = 0;
	virtual void render() = 0;
};

#endif

