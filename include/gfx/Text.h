#ifndef TEXT_H
#define TEXT_H

namespace Text {

    void init(std::string fontName);
    void render(std::string text, glm::ivec4 position, GLfloat scale, glm::vec4 color);
}

#endif

