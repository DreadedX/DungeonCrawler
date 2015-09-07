#ifndef RENDER_H
#define RENDER_H

namespace Render {

    void init();
    void clear();
    void move(glm::vec4 toMove);
    glm::vec4 getPosition();

    void startTile();
    void tile(glm::vec4 position, GLuint tex);
    void endTile();

    void map();

    void startEntity();
    void entity(glm::vec4 position, glm::vec4 scale, float mAngle, GLuint tex);
    void endEntity();
}
#endif
