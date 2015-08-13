#ifndef RENDER_H
#define RENDER_H

namespace Render {

    void init();
    void clear();
    void move(vec4 toMove);
    vec4 getPosition();

    void startTile();
    void tile(vec4 position, GLuint tex);
    void endTile();

    void map();

    void startEntity();
    void entity(vec4 position, vec4 scale, GLuint tex);
    void endEntity();
}
#endif
