#ifndef ENEMY_H
#define ENEMY_H

class Enemy: public Entity {

    using Entity::Entity;
    
    public:

	void init();
	void tick();
	void render();
};

#endif

