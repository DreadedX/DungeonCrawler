#ifndef RENDER_H
#define RENDER_H

namespace Render {

    void init();
    void clear();
    void move(vec4 toMove);

    void test(vec4 position);
    void tile(vec4 position, GLuint tex);
    void background(vec4 position, GLuint tex);
    void floor(vec4 position, GLuint tex);
    // void font(vec4 position, vec4 color, GLuint tex, int index);
};

#endif
