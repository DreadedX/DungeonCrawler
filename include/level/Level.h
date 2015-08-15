#ifndef LEVEL_H
#define LEVEL_H

namespace Level {

    void init();
    void tick();
    void render();
    void end();

    Entity *getPlayer();

    bool isSolid(vec4 mPosition);

};

#endif

