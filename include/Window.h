#ifndef WINDOW_H
#define WINDOW_H

#ifndef SCALE
#define SCALE 1
#endif

const int WIDTH = 608;
const int HEIGHT = (WIDTH / 4 * 3);
const char NAME[] = "Platformer";

const mat4 IDENTITY = mat4(1.0f);

namespace Window {

    void create();
    bool shouldClose();
    void terminate();
    void destroy();
    void swap();
    void poll();
};


#endif
