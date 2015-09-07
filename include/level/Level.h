#ifndef LEVEL_H
#define LEVEL_H

namespace Level {

    void init();
    void tick();
    void render();
    void end();

    Manager *getManager();
    Entity *getPlayer();

    bool isSolid(glm::ivec4 mPosition);

};

#endif

