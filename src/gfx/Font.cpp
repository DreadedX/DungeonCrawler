# include "Standard.h"

namespace Font {
    GLuint tex;

    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;'\"!?$%()-=+/*[] ";
    const int charCount = chars.length();

    const float charWidth = 1.0f/charCount;

    float fontScaleFloat = 1.0f;
    mat4 initMatrix = translate(IDENTITY, vec3(4 * fontScaleFloat, 5 * fontScaleFloat, 0));
    mat4 positionMatrix = translate(IDENTITY, vec3(8 * fontScaleFloat, 0, 0));

    void init() {

	tex = Texture::load("font");
    }

    void render(vec4 position, vec4 color, std::string msg) {
	position = initMatrix * position;

	for (uint i = 0; i < msg.length(); i++) {
	    int charIndex = chars.find(msg.at(i));

	    glColor4f(color.x, color.y, color.z, color.w);
	    Render::quadTexAbs(position, vec2(8 * fontScaleFloat, 10 * fontScaleFloat), tex, vec4(charWidth * charIndex, 0, charWidth * (charIndex + 1), 1));
	    glColor3f(1, 1, 1);

#if DRAW_BOX
	    Render::outlineAbs(position, vec2(8 * fontScaleFloat, 10 * fontScaleFloat));
#endif


	    position = positionMatrix * position;
	}

    }
}
