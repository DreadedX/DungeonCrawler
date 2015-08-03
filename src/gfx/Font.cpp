# include "Standard.h"

namespace Font {
    GLuint tex;

    const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789.,:;'\"!?$%()-=+/*[] ";
    const int charCount = chars.length();

    const float charWidth = 1.0f/charCount;

    float fontScaleFloat = 1.0f;
    mat4 initMatrix = translate(IDENTITY, vec3(0.8f * fontScaleFloat, fontScaleFloat, 0));
    mat4 positionMatrix = translate(IDENTITY, vec3(1.0f, 0, 0));

    void init() {

	tex = Texture::load("font");
    }

    void render(vec4 position, vec4 color, std::string msg) {
	position = initMatrix * position;

	for (uint i = 0; i < msg.length(); i++) {
	    int charIndex = chars.find(msg.at(i));

	    Render::font(position, color, tex, charIndex);

#if DRAW_BOX
	    Render::outlineAbs(position, vec2(8 * fontScaleFloat, 10 * fontScaleFloat));
#endif


	    position = positionMatrix * position;
	}

    }
}
