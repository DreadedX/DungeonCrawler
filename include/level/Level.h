#ifndef LEVEL_H
#define LEVEL_H

namespace Level {

    const int width = 64;
    const int height = 48;
    const int tileScaleInt = 16;
    
    void init();
    void tick();
    void render();
    void end();

    Entity* getPlayer();

};

#endif

