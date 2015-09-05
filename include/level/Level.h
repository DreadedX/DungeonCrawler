#ifndef LEVEL_H
#define LEVEL_H

namespace Level {

    void init();
    Entity &spawn();
    void tick();
    void render();
    void end();

    Entity *getPlayer();

    bool isSolid(glm::vec4 mPosition);

};

#endif

