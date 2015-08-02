#ifndef RENDER_H
#define RENDER_H

namespace Render {

    void init();
    void clear();
    void move(vec4 toMove);

    void test();
    void tile(vec4 position, GLuint tex);

    void outline(vec4 position, vec2 size, vec4 color);
    void outlineAbs(vec4 position, vec2 size, vec4 color);
    void quad(vec4 position, vec2 size, vec4 color);
    void quadAbs(vec4 position, vec2 size, vec4 color);
    void quadTex(vec4 position, vec2 size, GLuint tex, vec4 uv);
    void quadTexAbs(vec4 position, vec2 size, GLuint tex, vec4 uv);
};

#endif
