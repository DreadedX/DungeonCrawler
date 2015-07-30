#ifndef RENDER_H
#define RENDER_H

namespace Render {

    void init();
    void clear();

    void test();
    void tile(vec4 position, GLuint tex);
    void outline(int x1, int y1, int x2, int y2);
};

#endif
