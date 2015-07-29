#ifndef LEVEL_H
#define LEVEL_H

class Level {
    
    public:
	static void init();
	static void tick();
	static void render();
	static void end();

	static Entity* getPlayer();

};

#endif

