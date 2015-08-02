#if LEGACY
#include "Standard.h"

namespace Render {

    vec4 view = vec4(0, 0, 0, 1);
    mat4 viewMatrix = translate(IDENTITY, vec3(0));

    void init() {
    }

    void test() {
    }

    void clear() {

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void move(vec4 toMove) {

	// glTranslatef(toMove.x, toMove.y, toMove.z);
	view += toMove;
	viewMatrix = translate(IDENTITY, vec3(view.x, view.y, view.z));
    }

    void tile(vec4 position, GLuint tex) {

	quadTex(position, vec2(16, 16), tex, vec4(0, 0, 1, 1));
#if DRAW_BOX
	outline(position, vec2(16, 16));
#endif
    }

    void outline(vec4 position , vec2 size, vec4 color) {

	position = viewMatrix * position;
	outlineAbs(position, size, color);
    }
    void outlineAbs(vec4 position , vec2 size, vec4 color) {

	size /= 2;

	glColor4f(color.x, color.y, color.z, color.w);
	glBegin(GL_LINE_STRIP);
	glVertex2f(position.x-(size.x), position.y-(size.y));
	glVertex2f(position.x+(size.x), position.y-(size.y));
	glVertex2f(position.x+(size.x), position.y+(size.y));
	glVertex2f(position.x-(size.x), position.y+(size.y));
	glVertex2f(position.x-(size.x), position.y-(size.y));
	glEnd();
	glColor3f(1, 1, 1);
    }

    void quad(vec4 position , vec2 size, vec4 color) {

	position = viewMatrix * position;
	quadAbs(position, size, color);
    }
    void quadAbs(vec4 position, vec2 size, vec4 color) {

	size /= 2;

	glColor4f(color.x, color.y, color.z, color.w);
	glBegin(GL_QUADS);
	glVertex2f(position.x-(size.x), position.y-(size.y));
	glVertex2f(position.x+(size.x), position.y-(size.y));
	glVertex2f(position.x+(size.x), position.y+(size.y));
	glVertex2f(position.x-(size.x), position.y+(size.y));
	glEnd();
	glColor3f(1, 1, 1);
    }

    void quadTex(vec4 position, vec2 size, GLuint tex, vec4 uv) {

	position = viewMatrix * position;
	quadTexAbs(position, size, tex, uv);
    }
    void quadTexAbs(vec4 position, vec2 size, GLuint tex, vec4 uv) {

	size /= 2;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);
	glBegin(GL_QUADS);
	glTexCoord2f(uv.x, uv.y);
	glVertex2f(position.x-(size.x), position.y-(size.y));
	glTexCoord2f(uv.z, uv.y);
	glVertex2f(position.x+(size.x), position.y-(size.y));
	glTexCoord2f(uv.z, uv.w);
	glVertex2f(position.x+(size.x), position.y+(size.y));
	glTexCoord2f(uv.x, uv.w);
	glVertex2f(position.x-(size.x), position.y+(size.y));
	glEnd();
	glDisable(GL_TEXTURE_2D);
    }
}
#endif
