#ifndef TEXT_H
#define TEXT_H

namespace Text {

    // NOTE: This can possibly be replaced with a component
    struct TextObject {

	std::string text;
	glm::ivec4 position;
	GLfloat scale;
	glm::vec4 color;
	float speed;

	float charIndex = 0;
	bool display = true;

	void destroy() {

	    display = false;
	}
    };

    void init(std::string fontName);
    TextObject *add(std::string mText, glm::ivec4 mPosition, GLfloat mScale, glm::vec4 mColor, float mSpeed);
    void tick();
    void render();
    void end();
}

#endif

